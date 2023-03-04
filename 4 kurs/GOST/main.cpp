#include <iostream>

using namespace std;

#define Shift_left_11(x) ((x >> 21) ^ ((((x >> 21) << 21) ^ x) << 11))

const int n[8][16] = {{12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1},
                      {6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15},
                      {11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0},
                      {12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11},
                      {7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12},
                      {5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0},
                      {8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7},
                      {1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2}};

uint32_t Function_t(uint32_t a)
{
    uint32_t res = 0;
    for (int i = 0; i < 8; i++)
    {
        res = res ^ (n[i][(a >> (4 * i)) & 15] << (4 * i));
    }
    return res;
}

// add modules 2^32
// uint32_t Add(uint32_t x, uint32_t y)
// {
//     int a = (x >> 31) & 1;
//     int b = (y >> 31) & 1;
//     uint32_t res = ((x ^ (a << 31)) + (y ^ (b << 31))) ^ ((a ^ b) << 31);
//     return res;
// }

uint64_t Encrypt(uint64_t a, uint32_t K[8])
{
    uint32_t l = a >> 32;
    uint32_t r = ((a >> 32) << 32) ^ a;
    for (int i = 0; i < 24; i++)
    {
        uint32_t g = r;
        r = l ^ (Shift_left_11(Function_t(r + K[(i % 8)])));
        l = g;
    }
    for (int i = 0; i < 8; i++)
    {
        uint32_t g = r;
        r = l ^ (Shift_left_11(Function_t(r + K[7 - i])));
        l = g;
    }
    uint64_t res = r;
    res = (res << 32) ^ l;
    return res;
}

uint64_t Decrypt(uint64_t a, uint32_t K[8])
{
    uint32_t l = a >> 32;
    uint32_t r = ((a >> 32) << 32) ^ a;
    for (int i = 0; i < 8; i++)
    {
        uint32_t g = r;
        r = l ^ (Shift_left_11(Function_t(r + K[i])));
        l = g;
    }
    for (int i = 0; i < 24; i++)
    {
        uint32_t g = r;
        r = l ^ (Shift_left_11(Function_t(r + K[7 - (i % 8)])));
        l = g;
    }
    uint64_t res = r;
    res = (res << 32) ^ l;
    return res;
    return 0;
}

int main()
{
    uint32_t K[8];
    K[0] = 0xffeeddcc;
    K[1] = 0xbbaa9988;
    K[2] = 0x77665544;
    K[3] = 0x33221100;
    K[4] = 0xf0f1f2f3;
    K[5] = 0xf4f5f6f7;
    K[6] = 0xf8f9fafb;
    K[7] = 0xfcfdfeff;
    uint64_t a = 0xfedcba9876543210;
    uint64_t b = Encrypt(a, K);
    printf("encrypt   0x%lx  ---> 0x%lx\n", a, b);
    printf("decrypt   0x%lx\n", Decrypt(b, K));
}
