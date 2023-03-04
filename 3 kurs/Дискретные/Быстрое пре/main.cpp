#include "header.h"

int main()
{
    srand(clock());

    ////////////////////////////////////// g
    vector<float> f;
    cout << "\nf= ";
    for (int i = 0; i < l; i++)
    {
        int x = rand() % 2;
        f.push_back(x);
        cout << x;
    }
    cout << endl;

    vector<float> B0 = {1, 0};
    vector<float> B1 = {-1, 1};
    vector<vector<float>> B = {B0, B1};
    vector<float> ff = BPF(f, B);
    for (int i = 0; i < l; i++)
    {
        cout<<ff[i]<<endl;
    }
    
}