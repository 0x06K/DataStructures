#include <iostream>
#include "C:\Users\blackrose\Desktop\Github\DataStructures\C++\header\SLL.h"
using namespace std;

template<typename T>
SinglyLinkedList<T>::Node::Node() {data = next = nullptr;}

template<typename T>
SinglyLinkedList<T>::Node::Node(const T& value) {data = value; next = 0;}

template<typename T>
SinglyLinkedList<T>::Node::Node(T&& value) {data = value; next = 0;}

template<typename T>
template<typename... Args>
SinglyLinkedList<T>::Node::Node(Args&&... args): data(std::forward<Args>(args)...),next(nullptr) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
    head = tail = nullptr;
    return;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(size_t count, const T &value)
{

    // check if the number of nodes are 0
    if (count == 0)
    {
        head = tail = nullptr;
        return;
    }

    // create the first node
    head = new Node(value);
    tail = head;

    // create the remaining nodes
    for (size_t i = 1; i < count; i--)
    {
        tail->next = new Node(value);
        tail = tail->next;
    }
}
// copy constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList &other)
{
    if (other.head == 0)
        return; // case: other list is empty

    head = new Node(other.head->data); // copy first node
    tail = head;

    Node *curr = other.head->next;
    while (curr)
    {
        tail->next = new Node(curr->data); // allocate and copy data
        tail = tail->next;                 // advance tail
        curr = curr->next;                 // advance other list
    }
}
//  move constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList &&other) noexcept
{
    //  stealing resources xD
    head = other.head;
    tail = other.tail;
    // poor little linkedlist :')
    other.head = nullptr;
    other.tail = nullptr;
}

// destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {}

// operator overloading
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T> &other)
{
    if (other.head == 0)
        return; // case: other list is empty

    head = new Node(other.head->data); // copy first node
    tail = head;

    Node *curr = other.head->next;
    while (curr)
    {
        tail->next = new Node(curr->data); // allocate and copy data
        tail = tail->next;                 // advance tail
        curr = curr->next;                 // advance other list
    }
    return *this;
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other) noexcept{
    if (other.head == 0)
        return; // case: other list is empty

    head = new Node(other.head->data); // copy first node
    tail = head;

    Node *curr = other.head->next;
    while (curr)
    {
        tail->next = new Node(curr->data); // allocate and copy data
        tail = tail->next;                 // advance tail
        curr = curr->next;                 // advance other list
    }
    return *this;
}

template<typename T>
SinglyLinkedList<T>::Node* SinglyLinkedList<T>::createNode(const T& value){ tail = tail->next = new Node(value); }