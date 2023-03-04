#include <iostream>
#include<iomanip>
using namespace std;
struct student
{
    int *score;
    student *next;
};

student *Add(int, student*);
void Print(student*);