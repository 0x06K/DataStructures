#include <iostream>
using namespace std;
#include <windows.h>

struct node
{
    int data = 0;
    node *left = NULL;
    node *right = NULL;
    node(int data = 0)
    {
        this->data = data;
    }
};

class Tree
{
private:
    node *head;
    node *current;
    node *trav;

public:
    Tree(int data = 0)
    {
        head = new node(data);
        current = head;
    }
    int data()
    {
        return head->data;
    }

    void print()
    {
    }
    void add(int data = 0)
    {
        trav = current;
        while (trav)
        {
            if (data >= current->data)
            {
                trav = current->left;
            }
            else
            {
                trav = current->right;
            }
            current = trav;
        }
        trav = new node(data);
        printf("%d ", trav->data);
        current = head;
    }
    void trunc()
    {
        trav = current;
        if (trav->left)
        {
            current = trav->left;
            trunc();
        }
        if (trav->right)
        {
            current = trav->right;
            trunc();
        }
        else
        {
            printf("%d -> ", trav->data);
            delete trav;
            return;
        }
        current = head;
    }
};

