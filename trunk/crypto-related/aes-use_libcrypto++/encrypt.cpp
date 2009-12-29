#include <iostream>
#include <cstring>
#include <sstream>
#include <crypto++/dll.h>
#include <crypto++/default.h>
#include <crypto++/factory.h>
#include <crypto++/modes.h>
#include <crypto++/aes.h>
#include <crypto++/filters.h>
#include <crypto++/secblock.h>

using namespace std;
using namespace CryptoPP;

int main()
{
    string key;
    unsigned int limit;
    int flag;

    cout << "Input key(32Byte from [0-9a-f]):";
    cin >> key;
    cout << "Input upper limit:";
    cin >> limit;

    StringSource ss(key, true, new HexDecoder);
    SecByteBlock bkey((size_t)ss.MaxRetrievable());
    ss.Get(bkey, bkey.size());

    ECB_Mode<AES>::Encryption aes(bkey, bkey.size());
    ECB_Mode<AES>::Encryption aes1(bkey, bkey.size());

    SecByteBlock *outputsbb;
    for(unsigned int i = 0; i < limit; i ++)
    {
        const byte *pi = (const byte *)&i;

        flag = 0;

        StreamTransformationFilter *stf = new StreamTransformationFilter(aes);
        StringSource outputss(pi, (size_t)sizeof(int)/sizeof(byte), true, stf);
        outputsbb = new SecByteBlock((size_t)outputss.MaxRetrievable());
        outputss.Get(*outputsbb, outputsbb->size());

        if(*((unsigned int *)(outputsbb->BytePtr())) < limit &&
                *((unsigned int *)(outputsbb->BytePtr()) + 4) == 0 &&
                *((unsigned int *)(outputsbb->BytePtr()) + 8) == 0 &&
                *((unsigned int *)(outputsbb->BytePtr()) + 12) == 0)
        {
            flag = 1;
        }


        while(!flag)
        {
            StreamTransformationFilter *stf1 = new StreamTransformationFilter(aes1);
            StringSource outputss1(*outputsbb, outputsbb->size(), true, stf1);
            delete outputsbb;
            outputsbb = new SecByteBlock((size_t)outputss1.MaxRetrievable());
            outputss1.Get(*outputsbb, outputsbb->size());

            if(*((unsigned int *)(outputsbb->BytePtr())) < limit &&
                    *((unsigned int *)(outputsbb->BytePtr()) + 4) == 0 &&
                    *((unsigned int *)(outputsbb->BytePtr()) + 8) == 0 &&
                    *((unsigned int *)(outputsbb->BytePtr()) + 12) == 0)
            {
                flag = 1;
                cout << i << ": " << *((unsigned int *)(outputsbb->BytePtr())) << endl;
            }
        }
        delete outputsbb;
    }

    return 0;
}
