#include <stdio.h>

unsigned long long get_rdtsc()
{
    asm("rdtsc");
}

int main()
{
    unsigned long long i, t1, t2;
    long double freq;
    FILE *fin;
    char *line;
    int length;

    fin = fopen("/proc/cpuinfo", "r");
    while(getline(&line, &length, fin) != EOF)
    {
        if(sscanf(line, "cpu MHz\t\t: %llf", &freq) == 1)
        {
            freq *= 1000000ULL;
            break;
        }
    }
    close(fin);
    printf("cpu frequency = %lf\n", freq);

    for(i = 0; i < 10; i ++)
    {
        t1 = get_rdtsc();
        sleep(1);
        t2 = get_rdtsc();
        printf("t2 - t1 = %lld (%lldMHZ), time = %llf\n ", t2 - t1, (t2-t1)/1000000, ((double)(t2 - t1) / freq) * 1000);
    }
    return 0;
}
