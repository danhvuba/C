#include "header.h"

uint32_t Keeloq_Encrypt(uint32_t data, const uint64_t key)
{
    uint32_t x = data;
    for (int i = 0; i < 528; i++)
    {
        x = (x >> 1) ^ ((bit(Keeloq_NF, g5(x, 31, 26, 20, 9, 1)) ^ bit(x, 16) ^ bit(x, 0) ^ bit(key, i & 63)) << 31);
    }
    return x;
}

uint32_t Keeloq_Encrypt(uint32_t data, const uint64_t key, int r)
{
    uint32_t x = data;
    for (int i = 0; i < r; i++)
    {
        x = (x >> 1) ^ ((bit(Keeloq_NF, g5(x, 31, 26, 20, 9, 1)) ^ bit(x, 16) ^ bit(x, 0) ^ bit(key, i & 63)) << 31);
    }
    return x;
}

uint32_t Keeloq_Descrypt(uint32_t data, const uint64_t key)
{
    uint32_t x = data;
    for (int i = 0; i < 528; i++)
    {
        x = (x << 1) ^ (bit(Keeloq_NF, g5(x, 30, 25, 19, 8, 0)) ^ bit(x, 15) ^ bit(x, 31) ^ bit(key, (15 - i) & 63));
    }
    return x;
}

void Print_bit(uint32_t data)
{
    for (int i = 31; i >= 0; i--)
    {
        cout << bit(data, i);
    }
}

void Print_bit(uint64_t key)
{
    for (int i = 63; i >= 0; i--)
    {
        cout << bit(key, i);
    }
}

uint64_t Rotation_key(uint64_t key, int r)
{
    uint64_t k = key;
    for (int i = 0; i < r; i++)
    {
        k = Rotation(k);
    }
    return k;
}

bool Is_Shift_r(uint32_t data, uint32_t data2, int r)
{
    uint32_t x = pow(2, 32 - r) - 1;      // x = 111...1
    if (((data >> r) ^ (data2 & x)) == 0) // ^ -- XOR
    {
        return true;
    }
    return false;
}

int Find_encode_data(uint32_t text, uint64_t key, int r)
{
    int count = 0;
    uint64_t key_shifted = Rotation_key(key, r);

    // encode text to cipher by key
    uint32_t cipher_text = Keeloq_Encrypt(text, key);
    // Print_(r);
    // Print_bit(key);
    // cout << "     key\n";
    // Print_bit(kr);
    // cout << "     key >>> " << r << "\n";
    // cout << "\n  ";
    // Print_(r);
    // Print_bit(data);
    // cout << "     ";
    // Print_(r);
    // Print_bit(cipher_text);
    // cout << "\n  ";

    // count number of data for text encoded by r round    =? ----||P>>r
    for (int i = 0; i < pow(2, r); i++)
    {
        // creat text encoded 'r' round  ----||P>>r
        uint32_t data = (text >> r) ^ (i << (32 - r));
        // encode data by key_shifted
        uint32_t cipher_data = Keeloq_Encrypt(data, key_shifted);
        if (Is_Shift_r(cipher_text, cipher_data, r))
        {
            count++;
            // Print_bit(P1);
            // Print_(r);
            // cout << "     ";
            // Print_bit(E_kr_P1);
            // cout << "        i=" << i << "\n  ";
        }
    }
    return count;
}

void Print_(int r)
{
    for (int i = 0; i < r; i++)
    {
        cout << "_";
    }
}