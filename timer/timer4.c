#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main()
{
    struct timespec res;
    double t1, t2;
    double k;
    unsigned long long i,j;
    char buf[1000];

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &res);
    t1 = res.tv_sec * 1000000ULL + (double)res.tv_nsec / 1000.0;
    printf("Hello, World!\n");
    for(i = 0; i < 1000; i ++)
    {
        for(j = 1; j < 1000; j ++)
            k = i / j;
        memset(buf, 'a', 1000);
        printf("%s\n", buf); 
    }
    sleep(5);
    printf("Wake up\n");
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &res);
    t2 = res.tv_sec * 1000000ULL + (double)res.tv_nsec / 1000.0;
    printf("%lfus\n", (t2 - t1));

    return 0;
}
