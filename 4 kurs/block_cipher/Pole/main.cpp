#include <iostream>
#include <math.h>
using namespace std;

#define bit(a, i) ((a >> i) & 1)
#define Shift(a, fx) (((a ^ (((a >> 7) & 1) << 7)) << 1) ^ (fx * ((a >> 7) & 1)))

int Mul(uint8_t ax, uint8_t bx, uint8_t fx)
{
    uint8_t result=0;
    for (int i = 0; i < 8; i++)
    {
        if (bit(bx,i))
        {
            result=result^ax;
        }
        ax=Shift(ax,fx);
    }
    return result;
}

int main()
{
    int a[8] = {1, 0, 0, 0, 0, 1, 1, 1};
    uint8_t fx = 0;
    for (int i = 0; i < 8; i++)
    {
        fx = fx + a[7 - i] * pow(2, i);
    }

    uint ax=6*16+7;
    cout<<ax<<endl;
    int x=1;
    while (true)
    {
         x=Mul(x,ax,fx);
        cout<<x<<endl;
        if (x==1)
        {
            break;
        }  
    }
    
}