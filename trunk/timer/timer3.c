#include <stdio.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main()
{
    struct rusage usage;
    unsigned long long t1, t2;
    double k;
    unsigned long long i,j;

    getrusage(RUSAGE_SELF, &usage);
    t1 = (unsigned long long)usage.ru_utime.tv_sec * 1000000ULL + (unsigned long long)usage.ru_utime.tv_usec;
    t1 += (unsigned long long)usage.ru_stime.tv_sec * 1000000ULL + (unsigned long long)usage.ru_stime.tv_usec;
    printf("Hello, World!\n");
    for(i = 0; i < 1000; i ++)
        for(j = 1; j < 1000; j ++)
            k = i / j;
    sleep(3);
    printf("Wake up\n");
    getrusage(RUSAGE_SELF, &usage);
    t2 = (unsigned long long)usage.ru_utime.tv_sec * 1000000ULL + (unsigned long long)usage.ru_utime.tv_usec;
    t2 += (unsigned long long)usage.ru_stime.tv_sec * 1000000ULL + (unsigned long long)usage.ru_stime.tv_usec;
    printf("%lluus\n", (t2 - t1));

    return 0;
}
