#include <iostream>
#include "Tree.h"
using namespace std;

BinarySearchTree::BinarySearchTree(int data)
{
    this->root = new TreeNode(data);
}
BinarySearchTree::~BinarySearchTree()
{
}
TreeNode *BinarySearchTree::insertHelper(TreeNode *node, int data)
{
    if(node->right
    )

    return node;
}

void BinarySearchTree::insert(int data)
{
    TreeNode *temp = insertHelper(root, data);
    if (temp->data >= data) temp->left = new TreeNode(data);
    else temp->right = new TreeNode(data);
}

void BinarySearchTree::display()
{
    cout <<"inorder: ";inorder();cout<<endl;
    cout <<"preorder: ";preorder();cout<<endl;

}

void BinarySearchTree::inorderHelper(TreeNode* node){
    if (node->left) inorderHelper(node->left);
    cout << " " << node->data;
    if (node->right) inorderHelper(node->right);
}
void BinarySearchTree::inorder(){
    inorderHelper(root);
}

void BinarySearchTree::preorderHelper(TreeNode* node){
    cout << " " << node->data;
    if (node->left) inorderHelper(node->left);
    if (node->right) inorderHelper(node->right);
}
void BinarySearchTree::preorder(){
    preorderHelper(root);
}