#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

int main(int argc, char *argv[])
{
    int ret;
    DES_key_schedule schd;
    DES_cblock Key;
    unsigned char res[255];
    unsigned char res1[255];
    DES_cblock ivec;
    int length = strlen(argv[2]);
    
    memset(res, 0, 255);
    memset(res1, 0, 255);
    memcpy(&ivec, "thistest", 8);
    memcpy(&Key, argv[1], 8);
    

    DES_set_odd_parity(&Key);
    DES_set_key_checked(&Key, &schd);
    DES_ncbc_encrypt((unsigned char *)argv[2], res, length,
                     &schd, &ivec, DES_ENCRYPT);

    memcpy(&ivec, "thistest", 8);
    memcpy(&Key, argv[1], 8);
    DES_ncbc_encrypt(res, res1, length,
                     &schd, &ivec, DES_DECRYPT);

    printf("%s\n", res1);

    return 0;
}
