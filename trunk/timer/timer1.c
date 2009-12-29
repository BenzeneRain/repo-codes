#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <time.h>

int main()
{
    struct tms buf;
    double ttt;
    clock_t t1, t2;
    double k;
    unsigned long long i,j;

    ttt = sysconf(_SC_CLK_TCK);
    times(&buf);
    t1 = buf.tms_utime + buf.tms_stime;
    printf("Hello, World!\n");
    for(i = 0; i < 1000; i ++)
        for(j = 1; j < 1000; j ++)
            k = i / j;
    printf("Wake up\n");
    times(&buf);
    t2 = buf.tms_utime + buf.tms_stime;
    printf("%lfs\n", (t2 - t1)/ttt);

    return 0;
}
