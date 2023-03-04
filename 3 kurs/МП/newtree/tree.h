#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct node
{
    int number;
    node *left_node;
    node *right_node;
    int count; // количество равных элементов
};
// структура узла

node *Insert(node *, int); // функция вставки элемента
node *Remove(node *, int); // функция удаления элемента
node *Find(node *, int); // функция поискa элемента
void Draw(int, node *); // функция рисования дерево
