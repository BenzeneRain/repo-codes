#include <stdio.h>
#include <math.h>

unsigned long long get_rdtsc()
{
    unsigned long long ret;

    __asm__ __volatile__ ("rdtsc":"=A"(ret));

    return ret;
}

int main()
{
    int i;
    unsigned long long t1, t2;
    double freq;
    FILE *fin;
    char line[255];
    fin = fopen("/proc/cpuinfo", "r");
    if(!fin)
    {
        printf("\n");
        return 1;
    }
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
        printf("Error\n");
        return 1;
    }

    fclose(fin);
    printf("cpu frequency = %lfHz\n", freq);

    for(i = 0; i < 10; i ++)
    {
        t1 = get_rdtsc();
        sleep(1);
        t2 = get_rdtsc();
        printf("t2 - t1 = %llu, time = %lfus\n ", t2 - t1, ((double)(t2 - t1) / freq) * 1000);
    }
    return 0;
}
