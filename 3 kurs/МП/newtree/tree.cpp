#include "tree.h"

node *Insert(node *node_key, int x)
{
    if (node_key == NULL)
    {
        node *new_node = new node;
        new_node->number = x;
        new_node->count = 1;
        new_node->left_node = NULL;
        new_node->right_node = NULL;
        node_key = new_node;
    }
    //это произойдет если мы пришли в конец дерево, тогда создадим новый узел
    else if (node_key->number < x)
    {
        node_key->right_node = Insert(node_key->right_node, x);
    }
    else if (node_key->number > x)
    {
        node_key->left_node = Insert(node_key->left_node, x);
    }
    else
        node_key->count++;
    // это произойдет если мы нашли элемент, то 'count++'
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
            node *new_node = node_key->left_node;
            delete node_key;
            return new_node;
        }
        // случай не имеет правое поддерево
        else if (node_key->left_node == NULL)
        {
            node *new_node = node_key->right_node;
            delete node_key;
            return new_node;
        }
        // случай не имеет левое поддерево

        node *tmp = node_key->left_node;
        while (tmp->right_node != NULL)
        {
            tmp = tmp->right_node;
        }
        // найдем самый правый узел из левого поддерева
        node_key->number = tmp->number;
        node_key->count = tmp->count;

        node_key->left_node = Remove(node_key->left_node, tmp->number);
        // удалим узел, который мы уже взял

        // случай имеет обо поддерево
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
            cout << setw(5) << " ";
        }
        // выводим на экран "  " по степени узла
        cout << node_key->number << "(" << node_key->count << ")";
        Draw(level + 1, node_key->left_node);
    }
}
