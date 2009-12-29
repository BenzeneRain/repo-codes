#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include "tinyprp.h"

#define GETBIT(val, loc) (((val) >> (loc)) & 0x1U)
#define SETBIT(val, loc, bit) ((bit) == 0 ? (val) &= ~(1U << (loc)) \
                                          : ((val) |= (1U << (loc))))

static inline void MixCells(uint8_t c[4]);
static inline void MixCells_i_32(uint8_t a[4]);
static inline void ShiftCells_i_32(uint8_t r[4]);
static inline void SubBytes_i_32(uint8_t val[4]);
static inline uint8_t xtime(uint8_t x);
static inline uint8_t reverse(uint8_t x);
static inline void p_div_rm(uint32_t r0, uint32_t r1, uint32_t *q, uint32_t *r);
static inline uint32_t calc_aux(uint32_t q, uint32_t a0, uint32_t a1); 
static inline int find_hbit(uint32_t val);

static inline void InvSubBytes_i_32(uint8_t val[4]);
static inline void InvMixCells(uint8_t c[4]);
static inline void InvMixCells_i_32(uint8_t a[4]);
static inline void InvShiftCells_i_32(uint8_t r[4]);

static const uint8_t mod = 0x1B;
static const uint8_t bit7_shift = 7;
static const uint32_t rcon_i_32[RCON_COUNT_32] = {0x01010000, 0x04040202, 0x10100808, 
                                            0x40402020, 0x1B1B8080, 0x6C6C3636};
static const uint8_t c_i_32[] = {0x1, 0x1, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0};
static const uint8_t Invc_i_32[] = {0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0};


static inline void InvSubBytes_i_32(uint8_t val[4])
{
    uint8_t ans;
    uint8_t bit;
    uint8_t rev;
    int i, j;

    for(i = 0; i < 4; i ++)
    {
        ans = 0x0;
        for(j = 0; j < 8; j ++)
        {
            bit = GETBIT(val[i], ((j + 2) % 8)) ^ GETBIT(val[i], ((j + 5) % 8)) ^ 
                  GETBIT(val[i], ((j + 7) % 8)) ^ Invc_i_32[j];
            SETBIT(ans, j, bit);
        }
        if(ans != 0x0)
        {
            rev = reverse(ans);
        }
        else
        {
            rev = 0x0;
        }
        val[i] = rev;
    }

}

static inline void InvMixCells(uint8_t c[4])
{
    uint8_t t[4][3], ta[4];
    
    t[0][0] = xtime(c[0]); 
    t[0][1] = xtime(t[0][0]);
    t[0][2] = xtime(t[0][1]);

    t[1][0] = xtime(c[1]); 
    t[1][1] = xtime(t[1][0]);
    t[1][2] = xtime(t[1][1]);

    t[2][0] = xtime(c[2]); 
    t[2][1] = xtime(t[2][0]);
    t[2][2] = xtime(t[2][1]);

    t[3][0] = xtime(c[3]); 
    t[3][1] = xtime(t[3][0]);
    t[3][2] = xtime(t[3][1]);

    ta[0] = t[0][2] ^ t[0][1] ^ t[0][0] ^ t[1][2] ^ t[1][0] ^ c[1] ^
            t[2][2] ^ t[2][1] ^ c[2]    ^ t[3][2] ^ c[3];
    ta[1] = t[1][2] ^ t[1][1] ^ t[1][0] ^ t[2][2] ^ t[2][0] ^ c[2] ^
            t[3][2] ^ t[3][1] ^ c[3]    ^ t[0][2] ^ c[0];
    ta[2] = t[2][2] ^ t[2][1] ^ t[2][0] ^ t[3][2] ^ t[3][0] ^ c[3] ^
            t[0][2] ^ t[0][1] ^ c[0]    ^ t[1][2] ^ c[1];
    ta[3] = t[3][2] ^ t[3][1] ^ t[3][0] ^ t[0][2] ^ t[0][0] ^ c[0] ^
            t[1][2] ^ t[1][1] ^ c[1]    ^ t[2][2] ^ c[2];

    *((uint32_t *)c) = *((uint32_t *)ta);
}

static inline void InvMixCells_i_32(uint8_t a[4])
{
    uint8_t c[2][4] = 
    {
        {(uint8_t)(a[0] >> 4), (uint8_t)(a[1] >> 4), (uint8_t)(a[2] >> 4), (uint8_t)(a[3] >> 4)},
        {(uint8_t)(a[0] & 0xF), (uint8_t)(a[1] & 0xF), (uint8_t)(a[2] & 0xF), (uint8_t)(a[3] & 0xF)}
    };

    InvMixCells(c[0]);
    InvMixCells(c[1]);

    a[0] = ((c[0][0] << 4) & 0xF0) | (c[1][0] & 0xF);
    a[1] = ((c[0][1] << 4) & 0xF0) | (c[1][1] & 0xF);
    a[2] = ((c[0][2] << 4) & 0xF0) | (c[1][2] & 0xF);
    a[3] = ((c[0][3] << 4) & 0xF0) | (c[1][3] & 0xF);
}

static inline void InvShiftCells_i_32(uint8_t r[4])
{
    uint32_t *ri;

    ri = (uint32_t *)r;
    *ri = *ri << 28 | *ri >> 4;

    r[1] = r[1] << 6 | r[1] >> 2;
    r[2] = r[2] << 4 | r[2] >> 4;
    r[3] = r[3] << 2 | r[3] >> 6;
}



static inline int find_hbit(uint32_t val)
{
    uint32_t tmp = val;
    int count = 0;

    __asm__ ("bsr %1, %0":"=r"(count):"r"(tmp));

    return count;
}

static inline void p_div_rm(uint32_t r0, uint32_t r1, uint32_t *q, uint32_t *r)
{
    int lr0, lr1;
    uint32_t mid_q;
    uint32_t pt;
    uint32_t b_mov;
    uint32_t tr0, tr1;

    lr0 = find_hbit(r0);
    lr1 = find_hbit(r1);
    tr0 = r0;
    mid_q = 0;
    while(lr0 >= lr1)
    {
        pt = lr0 - 1;
        b_mov = lr0 - lr1;
        tr1 = r1;
        tr1 <<= b_mov;
        SETBIT(mid_q, b_mov, 1);
        tr0 ^= tr1;
        lr0 = find_hbit(tr0);
    }

    *q = mid_q;
    *r = tr0;
}

static inline uint32_t calc_aux(uint32_t q, uint32_t a0, uint32_t a1)
{
    uint32_t ans = 0x0;
    uint32_t tmp_q = q;
    uint32_t tmp_a1 = a1;

    while(tmp_a1 > 0)
    {
        if((tmp_a1 & 0x1U) == 0x1)
        {
            ans ^= tmp_q;
        }
        tmp_q <<= 1;
        tmp_a1 >>= 1;
    }

    ans ^= a0;
    return ans;
}

static inline uint8_t reverse(uint8_t x)
{
    uint32_t r0, r1, r;
    uint32_t a0, a1, a;
    uint32_t q;

    r0 = mod | 0x100U;
    r1 = x;
    a  = x;
    a0 = 0;
    a1 = 1;
    while(r1 > 1)
    {
        p_div_rm(r0, r1, &q, &r);
        a = calc_aux(q, a0, a1);
        r0 = r1;
        r1 = r;
        a0 = a1;
        a1 = a;
    }

    return (uint8_t) (a & 0xFF);
}

static inline void SubBytes_i_32(uint8_t val[4])
{
    uint8_t ans;
    uint8_t bit;
    uint8_t rev;
    int i, j;

    for(i = 0; i < 4; i ++)
    {
        if(val[i] != 0x0)
        {
            rev = reverse(val[i]);
        }
        else
        {
            rev = 0x0;
        }
        ans = 0x0;
        for(j = 0; j < 8; j ++)
        {
            bit = GETBIT(rev, j) ^ GETBIT(rev, ((j + 4) % 8)) ^
                  GETBIT(rev, ((j + 5) % 8)) ^ GETBIT(rev, ((j + 6) % 8)) ^
                  GETBIT(rev, ((j + 7) % 8)) ^ c_i_32[j];
            SETBIT(ans, j, bit);
        }
        val[i] = ans;
    }
}

static inline uint8_t xtime(uint8_t x)
{
    if(((x >> bit7_shift) & 0x1U) == 0x1)
    {
        x <<= 1;
        x ^= mod;
    }
    else
    {
        x <<=1;
    }
}

static inline void MixCells(uint8_t c[4])
{
    uint8_t tm;
    uint8_t ta = c[0];
    uint8_t t;

    t  = c[0] ^ c[1] ^ c[2] ^ c[3];
    
    tm = c[0] ^ c[1];
    tm = xtime(tm);
    c[0] ^= tm ^ t;

    tm = c[1] ^ c[2];
    tm = xtime(tm);
    c[1] ^= tm ^ t;

    tm = c[2] ^ c[3];
    tm = xtime(tm);
    c[2] ^= tm ^ t;

    tm = c[3] ^ ta;
    tm = xtime(tm);
    c[3] ^= tm ^ t;
}

static inline void MixCells_i_32(uint8_t a[4])
{
    uint8_t c[2][4] = {(uint8_t)(a[0] >> 4), (uint8_t)(a[1] >> 4), 
                       (uint8_t)(a[2] >> 4), (uint8_t)(a[3] >> 4),
                       (uint8_t)(a[0] & 0xF), (uint8_t)(a[1] & 0xF), 
                       (uint8_t)(a[2] & 0xF), (uint8_t)(a[3] & 0xF)};

    MixCells(c[0]);
    MixCells(c[1]);

    a[0] = ((c[0][0] << 4) & 0xF0) | (c[1][0] & 0xF);
    a[1] = ((c[0][1] << 4) & 0xF0) | (c[1][1] & 0xF);
    a[2] = ((c[0][2] << 4) & 0xF0) | (c[1][2] & 0xF);
    a[3] = ((c[0][3] << 4) & 0xF0) | (c[1][3] & 0xF);
}

static inline void ShiftCells_i_32(uint8_t r[4])
{
    uint32_t *ri = (uint32_t *)r;
    
    r[1] = (r[1] << 2) | (r[1] >> 6);
    r[2] = (r[2] << 4) | (r[2] >> 4);
    r[3] = (r[3] << 6) | (r[3] >> 2);
    
    *ri = ((*ri) << 4) | ((*ri) >> 28);
}

inline void ExpandKey_32(uint32_t key[KEYSIZE_32], uint32_t *expandedKey)
{
    int i, j;

    for(i = 0; i < (KEYSIZE_32 + RCON_COUNT_32); i ++)
    {
        if(i < KEYSIZE_32)
        {
            expandedKey[i] = key[i];
        }
        else
        {
            expandedKey[i] = rcon_i_32[i - KEYSIZE_32];
            for(j = 0; j < i; j ++)
            {
                expandedKey[i] ^= expandedKey[j];
                SubBytes_i_32((uint8_t *)(expandedKey + i));
                ShiftCells_i_32((uint8_t *)(expandedKey + i));
                MixCells_i_32((uint8_t *)(expandedKey + i));
            }
        }
    }
}

void encrypt_32(uint32_t  *expandedKey, uint8_t a[4])
{
    int i;

    *((uint32_t *)a) ^= expandedKey[0];

    for(i = 1; i < (KEYSIZE_32 + RCON_COUNT_32 - 1); i ++)
    {
        SubBytes_i_32(a);
        ShiftCells_i_32(a);
        MixCells_i_32(a);
        *((uint32_t *)a) ^= expandedKey[i];
    }

    SubBytes_i_32(a);
    ShiftCells_i_32(a);
    *((uint32_t *)a) ^= expandedKey[i];
}

void decrypt_32(uint32_t  *expandedKey, uint8_t a[4])
{
    int i;
    
    *((uint32_t *)a) ^= expandedKey[KEYSIZE_32 + RCON_COUNT_32 - 1];
    
    for(i = KEYSIZE_32 + RCON_COUNT_32 - 2; i > 0; i --)
    {
        InvShiftCells_i_32(a);
        InvSubBytes_i_32(a);
        *((uint32_t *)a) ^= expandedKey[i];
        InvMixCells_i_32(a);
    }

    InvShiftCells_i_32(a);
    InvSubBytes_i_32(a);
    *((uint32_t *)a) ^= expandedKey[i];
}

/*
int main(int argc, char *argv[])
{
    uint8_t msg[4];
    uint32_t key[KEYSIZE_32];
    uint32_t expKey[20];
    uint32_t val;
    int i;
    
    printf("Key(4 uint32):");
    for(i = 0; i < KEYSIZE_32; i ++)
    {
        scanf("%u", &key[i]);
    }

    for(i = 0; i < 4; i ++)
    {
        msg[i] = 0x0;
    }
    
    while(scanf("%u", &i) != EOF)
    {
        *((uint32_t *)msg) = i;
        memset(expKey, 0, 20 * sizeof(uint32_t));
        ExpandKey_32(key, expKey);
        decrypt_32(expKey, msg);
        printf("Decrypt Msg: %u\n", *((uint32_t *)msg));
    }

    return 0;
}
*/
