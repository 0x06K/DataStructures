#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    BinarySearchTree T1(5);
    T1.insert(3);
    T1.insert(2);
    T1.insert(14);
    T1.insert(2);
    T1.insert(34);
    T1.insert(73);
    T1.insert(18);
    T1.display();
}