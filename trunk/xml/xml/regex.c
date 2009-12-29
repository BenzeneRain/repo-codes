#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

int main(int argc, char *argv[])
{
    regex_t regex;
    regmatch_t pmatch[10];
    char ebuf[128];
    int ret;
    int i, j;

    printf("%s\t%s\n", argv[1], argv[2]);

    ret = regcomp(&regex, argv[1], 0);
    if(ret != 0)
    {
        regerror(ret, &regex, ebuf, sizeof(ebuf));
        printf("%s\n", ebuf);
        exit(0);
    }

    ret = regexec(&regex, argv[2], 10, pmatch, 0);
    if(ret != 0)
    {
        regerror(ret, &regex, ebuf, sizeof(ebuf));
        printf("%s\n", ebuf);
        exit(0);
    }

    for(i = 0; i < 10;i++)
    {
        if(pmatch[i].rm_so == -1)
            break;
        printf("%d: ",i + 1);
        for(j = pmatch[i].rm_so; j < pmatch[i].rm_eo; j ++)
        {
            printf("%c", argv[2][j]);
        }
        printf("\n");
    }
    return 0;
}
