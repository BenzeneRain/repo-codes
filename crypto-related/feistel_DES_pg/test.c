#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <feistel_pg_lib.h>

#define TIMESCALE 1000000.0

static double cpu_freq;

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

int main(int argc, char *argv[])
{
    uint8_t **key;
    uint32_t round;
    unsigned long n;
    unsigned long i, j;
    unsigned long ans;
    uint32_t a, b;
    unsigned long long t1, t2;
    double tt, avg, total;

    printf("Round of feistel permutation:");
    scanf("%d", &round);

    key = (uint8_t **)malloc(round * sizeof(uint8_t **));

    for(i = 0; i < round; i ++)
    {
        key[i] = (uint8_t *)malloc(PERMKEYLENGTH * sizeof(uint8_t *));
        memset(key[i], 0, PERMKEYLENGTH * sizeof(uint8_t));
    }
    
    for(i = 0; i < round; i ++)
    {
        printf("Please input key for %dth round(4 uint32):", i + 1);
        for(j = 0; j < PERMKEYLENGTH; j ++)
        {
            scanf("%u", &key[i][j]);
        }
    }

    freopen(argv[2], "w", stdout);
    n = (unsigned long)atol(argv[1]);
    discomp_max(n, &a, &b);
    total = 0;
    timer_init();
    for(i = 0; i < n ; i ++)
    {
        t1 = get_rdtsc();
        ans = permute(i, n, a, b, key, round);
        t2 = get_rdtsc();
        tt = ((double)(t2 - t1) / cpu_freq) * TIMESCALE;
        total += tt;
        printf("%u -> %u, time cost is %lfus\n", i, ans, tt);
        fflush(stdout);
    }

    printf("Feistel permutation round for each item is %d\n", round);
    printf("Total cost is %lfus, and average cost is %lfus\n", total, total/n);
    fflush(stdout);
    fclose(stdout);

    for(i = 0; i < round; i ++)
    {
        free(key[i]);
    }
    free(key);

    return 0;
}
