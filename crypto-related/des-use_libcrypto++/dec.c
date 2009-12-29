#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

int main(int argc, char *argv[])
{
    int ret;
    DES_key_schedule schd;
    DES_cblock Key;
    unsigned char res[255];
    DES_cblock ivec;
    int i;
    
    memset(res, 0, 255);
    memcpy(&ivec, "thistest", 8);
    memcpy(&Key, argv[1], 8);
    

    DES_set_odd_parity(&Key);
    DES_set_key_checked(&Key, &schd);
    DES_ncbc_encrypt((unsigned char *)argv[2], res, strlen(argv[2]),
                     &schd, &ivec, DES_DECRYPT);

    for(i = 0; i < strlen(argv[2]); i ++)
        printf("%x\n", res[i]);

    return 0;
}
