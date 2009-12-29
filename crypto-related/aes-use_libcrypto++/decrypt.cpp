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

#define MAX 1000
#define CIPHERLENGTH 16

using namespace std;
using namespace CryptoPP;

int main()
{
    string key;
    int i;
    unsigned int val;

    cin >> key;

    StringSource ss(key, true, new HexDecoder);
    SecByteBlock bkey((size_t)ss.MaxRetrievable());
    ss.Get(bkey, bkey.size());

    ECB_Mode<AES>::Decryption aes(bkey, bkey.size());

    for(;;)
    {
        cin >> val;
        byte pi[CIPHERLENGTH] = {0};
        
        for(i = CIPHERLENGTH - 1; i >= 0; i --)
        {
            pi[i] = val & 0xff;
            val >>= 8;
        }

        StreamTransformationFilter *stf = new StreamTransformationFilter(aes);
        StringSource outputss(pi, CIPHERLENGTH, true, stf);
        SecByteBlock outputsbb((size_t)outputss.MaxRetrievable());
        outputss.Get(outputsbb, outputsbb.size());
        
        cout << *((unsigned int *)(outputsbb.BytePtr())) << endl;
    }

    return 0;
}
