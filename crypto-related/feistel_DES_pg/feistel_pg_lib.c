#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <memory.h>
#include <openssl/des.h>
#include <feistel_pg_lib.h>

static uint64_t feistel_enc(uint32_t a, uint32_t b, uint32_t m, uint8_t *key[], uint32_t round);
static uint64_t feistel_dec(uint32_t a, uint32_t b, uint32_t m, uint8_t *key[], uint32_t round);

void discomp_max(uint32_t max, uint32_t *a, uint32_t *b)
{
    *a = (uint32_t)ceil(sqrt(max));
    *b = *a + BINC;
    *a = *a + AINC;
}

uint32_t permute(uint32_t val, uint32_t max, uint32_t a, uint32_t b, uint8_t *key[], uint32_t round)
{
    uint64_t c;

    c = (uint64_t)val;
    do
    {
       c = feistel_enc(a, b, c, key, round);
    }while(c >= (uint64_t)max);

    return c;
}

uint32_t revpermute(uint32_t val, uint32_t max, uint32_t a, uint32_t b, uint8_t *key[], uint32_t round)
{
    uint64_t c;

    c = (uint64_t)val; 
    do
    {
        c = feistel_dec(a, b, c, key, round);
    }while(c >= (uint64_t)max);

    return c;
}

static uint64_t feistel_enc(uint32_t a, uint32_t b, uint32_t m, uint8_t *key[], uint32_t round)
{
    uint64_t L, R;
    uint64_t tmp, nval;
    uint64_t mod;
    uint8_t val[8];
    uint8_t res[8];
    int i;
    DES_cblock ckey;
    DES_key_schedule schd;
    
    L = m % a;
    R = (uint64_t)floor((double)m / (double)a);
    
    memset(val, 0, 8 * sizeof(uint8_t));
    for(i = 0; i < round; i ++)
    {
        memcpy(val, &R, 8 * sizeof(uint8_t));

        memset(&ckey, 0, sizeof(DES_cblock));
        memcpy(&ckey, key[i], PERMKEYLENGTH);
        memset(res, 0, 8 * sizeof(char));
        memset(&schd, 0, sizeof(DES_key_schedule));

        DES_set_odd_parity(&ckey);
        DES_set_key_checked(&ckey, &schd);
        DES_ecb_encrypt((const_DES_cblock *)val, (DES_cblock *)res, 
                         &schd, DES_ENCRYPT);

        nval = *((uint64_t *)res);
        
        mod = ((i & 0x1) == 0) ? a : b;
        tmp = ((L % mod)+ (nval % mod)) % mod;

        L = R;
        R = tmp;

        memset(val, 0, 8 * sizeof(uint8_t));
    }

    if((round & 0x1) == 1)
    {
        return a * L + R;
    }
    else
    {
        return a * R + L;
    }

}

static uint64_t feistel_dec(uint32_t a, uint32_t b, uint32_t m, uint8_t *key[], uint32_t round)
{
    uint64_t L, R;
    uint64_t tmp, nval;
    uint64_t mod;
    uint8_t val[8];
    uint8_t res[8];
    int i;
    DES_cblock ckey;
    DES_key_schedule schd;

    if((round & 0x1) == 1)
    {
        R =  m % a;
        L = (uint64_t)floor((double)m / (double)a);
    }
    else
    {
        L = m % a;
        R = (uint64_t)floor((double)m / (double)a);
    }
    
    memset(val, 0, 8 * sizeof(uint8_t)); 
    for(i = round - 1; i >= 0; i --)
    {
        memcpy(val, &L, 8 * sizeof(uint8_t));

        memset(&ckey, 0, sizeof(DES_cblock));
        memcpy(&ckey, key[i], PERMKEYLENGTH);
        memset(res, 0, 8 * sizeof(char));

        DES_set_odd_parity(&ckey);
        DES_set_key_checked(&ckey, &schd);
        DES_ecb_encrypt((const_DES_cblock *)val, (DES_cblock *)res, 
                         &schd, DES_ENCRYPT);

        nval = *((uint64_t *)res);
        mod = ((i & 0x1) == 0) ? a : b;

        tmp = ((R % mod) + mod - (nval % mod)) % mod;

        R = L;
        L = tmp;
        memset(val, 0, 8 * sizeof(uint8_t));
    }
    
    return a * R + L;
}

