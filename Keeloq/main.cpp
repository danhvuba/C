
#include "header.h"

int main()
{
    // uint64_t key =0xB3952B5CA8D06B3D ;//0xB8952F5C78D06B3D; // 13300589148719049533;
    // cout << "key: " << key << endl;
    // Print_bit(key);
    // cout<<endl<<bit(key,16)<<endl;

    // uint32_t data = 0x7AEB6B3D; // 2026924861;
    // cout << "\ndata:  " << data << endl;
    // Print_bit(data);

    // uint32_t cipher_text = Keeloq_Encrypt(data, key);
    // cout << "\nciphertext:  " << cipher_text << "\n ";
    // Print_bit(cipher_text);
    // cout<<endl;

    // uint32_t plain_text = Keeloq_Descrypt(cipher_text, key);
    // cout << "\nplaintext:  " << plain_text << endl;
    // Print_bit(plain_text);
    // cout << endl;

    srand(time(NULL));
    for (int r = 1; r < 10; r++)
    {
        int count = 0;
        for (int i = 0; i < 100; i++)
        {
            uint64_t key = rand();
            uint32_t data = rand();
            count = count + Find_encode_data(data, key, r);
        }
        cout << "r= "<<r<<"  result= " << count << endl;
    }
}