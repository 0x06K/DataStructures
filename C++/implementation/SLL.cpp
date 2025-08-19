#include <iostream>
#include "C:\Users\blackrose\Desktop\Github\DataStructures\C++\header\SLL.h"
using namespace std;

// iterator
template <typename T>
SinglyLinkedList<T>::Iterator::Iterator() { current = nullptr; }

template <typename T>
SinglyLinkedList<T>::Iterator::Iterator(Node *node) { current = node; }

template <typename T>
SinglyLinkedList<T>::Iterator &SinglyLinkedList<T>::Iterator::operator=(const Iterator &other)
{
    current = other->current;
    return *this;
}

template<typename T>
T& SinglyLinkedList<T>::Iterator::operator*() { return current->data; }

template<typename T>
const T& SinglyLinkedList<T>::Iterator::operator*() const { return current->data; }

template<typename T>
const T* SinglyLinkedList<T>::Iterator::operator->() const { return &(current->data); }

template<typename T>
T* SinglyLinkedList<T>::Iterator::operator->() { return &(current->data); }

template<typename T>
SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++(){
    current=current->next;
    return *this;
}

template<typename T>
SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int) {
    Iterator temp = *this;     // save old iterator
    current = current->next;   // advance to next node
    return temp;               // return old iterator (by value)
}

template<typename T>
bool SinglyLinkedList<T>::Iterator::operator==(const SinglyLinkedList<T>::Iterator& other) const{
    return (current == other->current);
}

template<typename T>
bool SinglyLinkedList<T>::Iterator::operator!=(const SinglyLinkedList<T>::Iterator& other) const{
    return (current != other->current);
}
// constructors



template <typename T>
SinglyLinkedList<T>::Node::Node() { data = next = nullptr; }

template <typename T>
SinglyLinkedList<T>::Node::Node(const T &value)
{
    data = value;
    next = 0;
}

template <typename T>
SinglyLinkedList<T>::Node::Node(T &&value)
{
    data = value;
    next = 0;
}

template <typename T>
template <typename... Args>
SinglyLinkedList<T>::Node::Node(Args &&...args) : data(std::forward<Args>(args)...), next(nullptr) {}

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
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(const SinglyLinkedList<T> &other)
{
    if (other.head == 0)
        return *this; // case: other list is empty

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

template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &&other) noexcept
{
    if (other.head == 0)
        return *this; // case: other list is empty

    if (this != &other) // protect against self-move
    {
        clear(); // delete current list

        head = other.head; // steal nodes
        tail = other.tail;

        other.head = nullptr; // leave other in valid empty state
        other.tail = nullptr;
    }
    return *this;
}

template <typename T>
SinglyLinkedList<T>::Node *SinglyLinkedList<T>::createNode(const T &value) { return new Node(value); }

template <typename T>
SinglyLinkedList<T>::Node *SinglyLinkedList<T>::createNode(T &&value) { return new Node(value); }

template <typename T>
template <typename... Args>
SinglyLinkedList<T>::Node *SinglyLinkedList<T>::createNode(Args &&...args) { return new Node(value); }

template <typename T>
void SinglyLinkedList<T>::destroyNode(Node *node)
{
    if (head == nullptr)
        return;
    if (head == node)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node *curr = head;
    while (curr->next && curr->next != node)
        curr = curr->next;
    curr->next = node->next;

    if (node->next == node)
    {
        node->next = nullptr;
        tail = (tail == node) ? curr : tail;
        delete node;
    }
}