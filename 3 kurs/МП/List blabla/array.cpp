#include "array.h"
student *Add(int x, student *key)
{
    if (key == NULL)
    {
        student *new_student = new student;
        new_student->score = new int;
        new_student->next = NULL;
        *new_student->score = x;
        key = new_student;
    }
    else
        key->next = Add(x, key->next);
    return key;
}

void Print(student *key)
{
    int i=0;
    if (key!=NULL)
    {
        i++;
        cout<<setw(5)<<i<<setw(10)<<*key->score<<" "<<endl;;
    }
    else return;
    Print(key->next);
    
}