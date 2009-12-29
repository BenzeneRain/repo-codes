#include <stdio.h>
#include <memory.h>
#include <openssl/sha.h>

int main(int argc, char *argv[])
{
    int len;
    int i;
    char output[21];

    if(argc < 2)
    {
        printf("Please input the message to hash!\n");
        return -1;
    }

    memset(output, 0, 21 * sizeof(char));
    len = strlen(argv[1]);
    SHA1(argv[1], len, output);

    for(i = 0; i < 20 ; i ++)
    {
        printf("%x", output[i] & 0xff);
    }
    printf("\n");
    return 0;
}

