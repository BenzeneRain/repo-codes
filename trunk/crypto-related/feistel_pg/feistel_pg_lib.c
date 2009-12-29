#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <memory.h>
#include <feistel_pg_lib.h>
#include <tinyprp.h>

static uint64_t feistel_enc(uint32_t a, uint32_t b, uint32_t m, uint32_t *key[], uint32_t round);
static uint64_t feistel_dec(uint32_t a, uint32_t b, uint32_t m, uint32_t *key[], uint32_t round);

void discomp_max(uint32_t max, uint32_t *a, uint32_t *b)
{
    *a = (uint32_t)ceil(sqrt(max));
    *b = *a + BINC;
    *a = *a + AINC;
}

uint32_t permute(uint32_t val, uint32_t max, uint32_t a, uint32_t b, uint32_t *key[], uint32_t round)
{
    uint64_t c;

    c = (uint64_t)val;
    do
    {
       c = feistel_enc(a, b, c, key, round);
    }while(c >= (uint64_t)max);

    return c;
}

uint32_t revpermute(uint32_t val, uint32_t max, uint32_t a, uint32_t b, uint32_t *key[], uint32_t round)
{
    uint64_t c;

    c = (uint64_t)val; 
    do
    {
        c = feistel_dec(a, b, c, key, round);
    }while(c >= (uint64_t)max);

    return c;
}

static uint64_t feistel_enc(uint32_t a, uint32_t b, uint32_t m, uint32_t *key[], uint32_t round)
{
    uint64_t L, R;
    uint64_t tmp;
    uint8_t val[4];
    int i;

    L = m % a;
    R = (uint64_t)floor((double)m / (double)a);
    
    for(i = 0; i < round; i ++)
    {
        memset(val, 0, 4 * sizeof(uint8_t));
        memcpy(val, &R, 4 * sizeof(uint8_t));
        if((i & 0x1) == 0)
        {
            encrypt_32(key[i], val);
            tmp = (L + *((uint32_t *)val)) % a;
        }
        else
        {
            encrypt_32(key[i], val);
            tmp = (L + *((uint32_t *)val)) % b;
        }
        L = R;
        R = tmp;
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

static uint64_t feistel_dec(uint32_t a, uint32_t b, uint32_t m, uint32_t *key[], uint32_t round)
{
    uint64_t L, R;
    uint64_t tmp;
    uint8_t val[4];
    int i;

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
    
    
    for(i = round - 1; i >= 0; i --)
    {
        memset(val, 0, 4 * sizeof(uint8_t));
        memcpy(val, &L, 4 * sizeof(uint8_t));
        if((i & 0x1) == 0)
        {
            encrypt_32(key[i], val);
            tmp = (R + a - (*((uint32_t *)val) % a)) % a;
        }
        else
        {
            encrypt_32(key[i], val);
            tmp = (R + b - (*((uint32_t *)val) % b)) % b;
        }
        R = L;
        L = tmp;
    }
    
    return a * R + L;
}

