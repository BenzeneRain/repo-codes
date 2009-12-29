#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include <tinyprp.h>

void test_16(char *argv)
{
    uint8_t msg[2];
    uint16_t key[KEYSIZE_16];
    uint16_t expKey[20];
    uint16_t val;
    unsigned long i;
    unsigned long n;
    
    printf("Key(8 uint16):");
    for(i = 0; i < KEYSIZE_16; i ++)
    {
        scanf("%u", &key[i]);
    }

    for(i = 0; i < 2; i ++)
    {
        msg[i] = 0x0;
    }
    
    memset(expKey, 0, 20 * sizeof(uint16_t));
    ExpandKey_16(key, expKey);

    n = (unsigned long)atol(argv);
    for(i = 0; i < n; i ++)
    {
        memset(msg, 0, 2 * sizeof(uint8_t));
        *((uint16_t *)msg) = i;
        do
        {
            encrypt_16(expKey, msg);
        }while(*((uint16_t *)msg) >= n);
        printf("%lu --> %u --> ", i, *((uint16_t *)msg));
        do
        {
            decrypt_16(expKey, msg);
        }while(*((uint16_t *)msg) >= n);
        printf("%u\n", *((uint16_t *)msg));
    }
}

void test_32(char *argv)
{
    uint8_t msg[4];
    uint32_t key[KEYSIZE_32];
    uint32_t expKey[20];
    uint32_t val;
    unsigned long i;
    unsigned long n;
    
    printf("Key(4 uint32):");
    for(i = 0; i < KEYSIZE_32; i ++)
    {
        scanf("%u", &key[i]);
    }

    for(i = 0; i < 4; i ++)
    {
        msg[i] = 0x0;
    }
    
    memset(expKey, 0, 20 * sizeof(uint32_t));
    ExpandKey_32(key, expKey);

    n = (unsigned long)atol(argv);
    for(i = 0; i < n; i ++)
    {
        memset(msg, 0, 4 * sizeof(uint8_t));
        *((uint32_t *)msg) = i;
        do
        {
            encrypt_32(expKey, msg);
        }while(*((uint32_t *)msg) >= n);
        printf("%lu --> %u --> ", i, *((uint32_t *)msg));
        do
        {
            decrypt_32(expKey, msg);
        }while(*((uint32_t *)msg) >= n);
        printf("%u\n", *((uint32_t *)msg));
    }
}

int main(int argc, char *argv[])
{
//    test_16(argv[1]);
    test_32(argv[1]);

    return 0;
}
