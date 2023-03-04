#include "array.h"

int main()
{
    student* root = NULL;
    root = Add(3, root);
    root = Add(6, root);
    root = Add(2, root);
    root = Add(9, root);
    root = Add(7, root);
    root = Add(4, root);
    cout << setw(5)<<"student"<<setw(10)<<"score"<<endl;
    cout<<"==================="<<endl;
    Print(root);
    cout << endl;
}