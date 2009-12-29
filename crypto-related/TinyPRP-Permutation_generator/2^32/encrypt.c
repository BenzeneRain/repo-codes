#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <math.h>
#include <signal.h>

#define KEYSIZE  4 /* Count in 32 bits */
#define RCON_COUNT 6 /* See the paper */

#define TIMESCALE 1000000.0

#define GETBIT(val, loc) (((val) >> (loc)) & 0x1U)
#define SETBIT(val, loc, bit) ((bit) == 0 ? (val) &= ~(1U << (loc)) \
                                          : ((val) |= (1U << (loc))))

static inline void MixCells(uint8_t c[4]);
static inline void MixCells_i(uint8_t a[4]);
static inline void ShiftCells_i(uint8_t r[4]);
static inline void SubBytes_i(uint8_t val[4]);
static inline void ExpandKey(uint32_t key[KEYSIZE], uint32_t *expendedKey);
static inline uint8_t xtime(uint8_t x);
static inline uint8_t reverse(uint8_t x);
static inline void p_div_rm(uint32_t r0, uint32_t r1, uint32_t *q, uint32_t *r);
static inline uint32_t calc_aux(uint32_t q, uint32_t a0, uint32_t a1); 
static inline int find_hbit(uint32_t val);
static void sigint_handler(int);

static const uint8_t mod = 0x1B;
static const uint8_t bit7_shift = 7;
static const uint32_t rcon_i[RCON_COUNT] = {0x01010000, 0x04040202, 0x10100808, 
                                            0x40402020, 0x1B1B8080, 0x6C6C3636};
static const uint8_t c_i[] = {0x1, 0x1, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0};

static double cpu_freq;
static int quit;

static void sigint_handler(int signum)
{
    quit = 1;
}

static int timer_init()
{
    double freq;
    FILE *fin;
/*    
    char *line;
    size_t length;
*/
    char line[255];
    fin = fopen("/proc/cpuinfo", "r");
    if(!fin)
    {
        return 1;
    }

//    while(getline(&line, &length, fin) != EOF)
    while(fgets(line, 255, fin) != NULL)
    {
        if(sscanf(line, "cpu MHz\t\t: %lf", &freq) == 1)
        {
            freq *= 1000000ULL;
            break;
        }
    }
    if(fabs(freq - 0) < 1e-9)
    {
        return 1;
    }

    fclose(fin);
    printf("cpu frequency = %lfHz\n", freq);
    cpu_freq = freq;
    return 0;
}

static unsigned long long get_rdtsc()
{
    __asm__ __volatile__ ("rdtsc");
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

static inline void SubBytes_i(uint8_t val[4])
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
                  GETBIT(rev, ((j + 7) % 8)) ^ c_i[j];
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

static inline void MixCells_i(uint8_t a[4])
{
    uint8_t c[2][4] = 
                {
                    {(uint8_t)(a[0] >> 4), (uint8_t)(a[1] >> 4), 
                     (uint8_t)(a[2] >> 4), (uint8_t)(a[3] >> 4)},
                    {(uint8_t)(a[0] & 0xF), (uint8_t)(a[1] & 0xF), 
                     (uint8_t)(a[2] & 0xF), (uint8_t)(a[3] & 0xF)}
                };

    MixCells(c[0]);
    MixCells(c[1]);

    a[0] = ((c[0][0] << 4) & 0xF0) | (c[1][0] & 0xF);
    a[1] = ((c[0][1] << 4) & 0xF0) | (c[1][1] & 0xF);
    a[2] = ((c[0][2] << 4) & 0xF0) | (c[1][2] & 0xF);
    a[3] = ((c[0][3] << 4) & 0xF0) | (c[1][3] & 0xF);
}

static inline void ShiftCells_i(uint8_t r[4])
{
    uint32_t *ri = (uint32_t *)r;
    
    r[1] = (r[1] << 2) | (r[1] >> 6);
    r[2] = (r[2] << 4) | (r[2] >> 4);
    r[3] = (r[3] << 6) | (r[3] >> 2);
    
    *ri = ((*ri) << 4) | ((*ri) >> 28);
}

static inline void ExpandKey(uint32_t key[KEYSIZE], uint32_t *expandedKey)
{
    int i, j;

    for(i = 0; i < (KEYSIZE + RCON_COUNT); i ++)
    {
        if(i < KEYSIZE)
        {
            expandedKey[i] = key[i];
        }
        else
        {
            expandedKey[i] = rcon_i[i - KEYSIZE];
            for(j = 0; j < i; j ++)
            {
                expandedKey[i] ^= expandedKey[j];
                SubBytes_i((uint8_t *)(expandedKey + i));
                ShiftCells_i((uint8_t *)(expandedKey + i));
                MixCells_i((uint8_t *)(expandedKey + i));
            }
        }
    }
}

void encrypt(uint32_t  *expandedKey, uint8_t a[4])
{
    int i;

    *((uint32_t *)a) ^= expandedKey[0];

    for(i = 1; i < (KEYSIZE + RCON_COUNT - 1); i ++)
    {
        SubBytes_i(a);
        ShiftCells_i(a);
        MixCells_i(a);
        *((uint32_t *)a) ^= expandedKey[i];
    }

    SubBytes_i(a);
    ShiftCells_i(a);
    *((uint32_t *)a) ^= expandedKey[i];
}

int main(int argc, char *argv[])
{
    uint8_t msg[4];
    uint32_t key[4];
    uint32_t expKey[20];
    uint32_t val;
    unsigned long i;
    unsigned long n;
    unsigned long long t1, t2;
    double sum, item;
    struct sigaction sigint_act;

    if(argc != 3)
    {
        printf("Usage: <prog> <n> <output filename>\n n is the range of output from 1 to n\n");
        exit(1);
    }

    memset(&sigint_act, 0, sizeof(struct sigaction));
    sigint_act.sa_handler = &sigint_handler;

    if(sigaction(SIGINT, &sigint_act, NULL))
    {
        perror("Sigaction Error:");
        return -1;
    }

    printf("Key(4 uint32):");
    for(i = 0; i < 4; i ++)
    {
        scanf("%u", &key[i]);
    }
    freopen(argv[2], "w", stdout);

    for(i = 0; i < 4; i ++)
    {
        msg[i] = 0x0;
    }
    sum = 0;
    timer_init();
    quit = 0;

    n = (unsigned long)atol(argv[1]);
    for(i = 0; (!quit) && (i < n); i ++)
    {
        *((uint32_t *)msg) = i;
        memset(expKey, 0, 20 * sizeof(uint32_t));
        ExpandKey(key, expKey);
        t1 = get_rdtsc();
        do
        {
            encrypt(expKey, msg);
        }while(*((uint32_t *)msg) >= n);
        t2 = get_rdtsc();
        item = ((double)(t2 - t1) / cpu_freq) * TIMESCALE;
        printf("Encrypt %lu: %u, time cost is %lfus\n", i, *((uint32_t *)msg), item);
        fflush(stdout);
        sum += item;
    }

    if(i > 0)
    {
        printf("Generating permutation from 0 - %u in range 0 - %u cost %lfus, and"
                " average cost is %lfus\n", i - 1, n - 1, sum, sum/(double)i);
    }
    fflush(stdout);
    fclose(stdout);
    return 0;
}
