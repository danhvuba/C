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
node *Find(node *, int);   // функция поискa элемента
void Draw(int, node *);    // функция рисования дерево

node *Insert(node *node_key, int x)
{
    if (node_key == NULL)
    {
        //это произойдет если мы пришли в конец дерево, тогда создадим новый узел
        node *new_node = new node;
        new_node->number = x;
        new_node->count = 1;
        new_node->left_node = NULL;
        new_node->right_node = NULL;
        node_key = new_node;
    }
    else if (node_key->number < x)
    {
        node_key->right_node = Insert(node_key->right_node, x);
    }
    else if (node_key->number > x)
    {
        node_key->left_node = Insert(node_key->left_node, x);
    }
    else
        node_key->count++; // это произойдет если мы нашли элемент, то 'count++'
    return node_key;
};

node *Remove(node *node_key, int x)
{
    if (node_key == NULL)
    {
        cout << "нет элемент " << x << " в дереве" << endl;
    }
    else if (node_key->number < x)
    {
        node_key->right_node = Remove(node_key->right_node, x);
    }
    else if (node_key->number > x)
    {
        node_key->left_node = Remove(node_key->left_node, x);
    }
    else if (node_key->number == x) // уже нашли элемент
    {
        if (node_key->right_node == NULL)
        {
            // случай не имеет правое поддерево
            node *new_node = node_key->left_node;
            delete node_key;
            return new_node;
        }

        else if (node_key->left_node == NULL)
        {
            // случай не имеет левое поддерево
            node *new_node = node_key->right_node;
            delete node_key;
            return new_node;
        }

        node *tmp = node_key->left_node;
        // найдем самый правый узел из левого поддерева
        while (tmp->right_node != NULL)
        {
            tmp = tmp->right_node;
        }

        node_key->number = tmp->number;
        node_key->count = tmp->count;

        node_key->left_node = Remove(node_key->left_node, tmp->number);
        // удалим узел, который мы уже взял
    }
    return node_key;
};

node *Find(node *node_key, int x)
{
    if (node_key == NULL)
    {
        return NULL;
    }
    if (node_key->number < x)
    {
        return Find(node_key->right_node, x);
    }
    else if (node_key->number > x)
    {
        return Find(node_key->left_node, x);
    }
    return node_key;
};

void Draw(int level, node *node_key)
{
    if (node_key != NULL)
    {
        Draw(level + 1, node_key->right_node);
        cout << endl;
        for (int i = 0; i < level; i++)
        {
            // выводим на экран "  " по степени узла
            cout << setw(5) << " ";
        }

        cout << node_key->number << "(" << node_key->count << ")";
        Draw(level + 1, node_key->left_node);
    }
}

int main()
{
    node *tree = NULL;
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    // случайно выбрать элементо
    for (int i = 0; i < n; i++)
    {
        int a = rand() % (n / 2);
        cout << i << "-й шаг, прибавим элемент: " << a << endl;
        tree = Insert(tree, a);
    }
    cout << "Дерево" << endl;

    Draw(0, tree);
    cout << endl;

    int val;
    cout << "найдем элемент: ";
    cin >> val;
    node *x = Find(tree, val);
    if (x != NULL)
    {
        cout << "&node " << x->number << "= " << x << ", количество повторяющих = " << x->count << endl;
    }
    else
        cout << "в дереве нет элемента " << val << endl;

    cout << "\nудалим элемент: ";
    cin >> val;
    tree = Remove(tree, val);

    cout << "Hовое дерево: ";
    Draw(0, tree);
    cout << endl;
}