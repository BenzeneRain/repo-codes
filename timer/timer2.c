#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <time.h>

int main()
{
    double ttt;
    clock_t t1, t2;
    double k;
    unsigned long long i,j;

    ttt = CLOCKS_PER_SEC;
    t1 = clock();
    printf("Hello, World!\n");
    for(i = 0; i < 1000; i ++)
        for(j = 1; j < 1000; j ++)
            k = i / j;
    printf("Wake up\n");
    t2 = clock();
    printf("%lfs\n", (t2 - t1)/ttt);

    return 0;
}
