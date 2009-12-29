#include <stdio.h>
#include <string.h>

static const char base64_ch[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int main(int argc, char *argv[])
{
    char buffer[255];
    char output[255];
    int length = strlen(argv[1]);
    int loops = length / 3;
    int lefts = length % 3;
    int i, j, k;

    memset(buffer, 0, 255);
    memset(output, 0, 255);
    memcpy(output, argv[1], length);

    j = 0; 
    k = 0;
    for(i = 0; i < loops; i ++)
    {
        buffer[j] = base64_ch[(output[k] >> 2) & 0x3f];
        buffer[j + 1] = base64_ch[((output[k] & 0x3) << 4) | ((output[k + 1] >> 4) & 0xf)];
        buffer[j + 2] = base64_ch[((output[k + 1] & 0xf) << 2) | ((output[k + 2] >> 6) & 0x3)];  
        buffer[j + 3] = base64_ch[(output[k + 2] & 0x3f)]; 
        k = k + 3;
        j = j + 4;
    }
    
    switch(lefts)
    {
        case 0:
            break;
        case 1:
            buffer[j] = base64_ch[(output[k] >> 2) & 0x3f];
            buffer[j + 1] = base64_ch[((output[k] & 0x3) << 4)];
            buffer[j + 2] = '=';
            buffer[j + 3] = '=';
            j = j + 4;
            break;
        case 2:
            buffer[j] = base64_ch[(output[k] >> 2) & 0x3f];
            buffer[j + 1] = base64_ch[((output[k] & 0x3) << 4) | ((output[k + 1] >> 4) & 0xf)];
            buffer[j + 2] = base64_ch[((output[k + 1] & 0xf) << 2)];  
            buffer[j + 3] = '=';
            j = j + 4;
            break;
        default:
            break;
    }

    buffer[j] = 0;

    printf("%s\n", buffer);

    return 0;
}
