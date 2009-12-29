#include <stdio.h>
#include <string.h>

static const char base64_ch[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char revbase64_ch[64];

int main(int argc, char *argv[])
{
    int i, k, j;
    int length = strlen(argv[1]);
    char input[255];
    char buffer[255];
    int loops = (length / 4) - 1;
    int left = 0;

    memset(input, 0, sizeof(input));
    memset(buffer, 0, sizeof(buffer));
    memcpy(input, argv[1], length);

    for(i = 0; i < 64; i ++)
    {
        revbase64_ch[(int)base64_ch[i]] = i;
    }


    k = 0;
    j = 0;
    for(i = 0; i < loops; i ++)
    {
        buffer[j] = ((revbase64_ch[(int)input[k]] << 2) & 0xfc) | 
                    ((revbase64_ch[(int)input[k + 1]] >> 4) & 0x3);
        buffer[j + 1] = ((revbase64_ch[(int)input[k + 1]] << 4) & 0xf0) | 
                        ((revbase64_ch[(int)input[k + 2]] >> 2) & 0xf);
        buffer[j + 2] = ((revbase64_ch[(int)input[k + 2]] << 6) & 0xc0) | 
                        ((revbase64_ch[(int)input[k + 3]]) & 0x3f);
        k = k + 4;
        j = j + 3;
    }

    i = 3;
    while(i >= 0)
    {
        if(input[j + i] == '=')
        {
            left ++;
            i --;
        }
        else
        {
            break;
        }
    }

    switch(left)
    {
        case 0:
            buffer[j] = ((revbase64_ch[(int)input[k]] << 2) & 0xfc) | 
                ((revbase64_ch[(int)input[k + 1]] >> 4) & 0x3);
            buffer[j + 1] = ((revbase64_ch[(int)input[k + 1]] << 4) & 0xf0) | 
                ((revbase64_ch[(int)input[k + 2]] >> 2) & 0xf);
            buffer[j + 2] = ((revbase64_ch[(int)input[k + 2]] << 6) & 0xc0) | 
                ((revbase64_ch[(int)input[k + 3]]) & 0x3f);
            j = j + 3;
            break;
        case 1:
            buffer[j] = ((revbase64_ch[(int)input[k]] << 2) & 0xfc) | 
                ((revbase64_ch[(int)input[k + 1]] >> 4) & 0x3);
            buffer[j + 1] = ((revbase64_ch[(int)input[k + 1]] << 4) & 0xf0) |
                ((revbase64_ch[(int)input[k + 2]] >> 2) & 0xf);
            j = j + 2;
            break;
        case 2:
            buffer[j] = ((revbase64_ch[(int)input[k]] << 2) & 0xfc) |
                ((revbase64_ch[(int)input[k + 1]] >> 4) & 0x3);
            j = j + 1;
            break;
        default:
            break;
    }

    buffer[j] = 0;
    printf("%s\n", buffer);

    return 0;
}
