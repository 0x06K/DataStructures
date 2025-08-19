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
SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++(){ current=current->next; return *this; }

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
SinglyLinkedList<T>::Node::Node(T &&value){ data = value; next = 0; }

template <typename T>
template <typename... Args>
SinglyLinkedList<T>::Node::Node(Args &&...args) : data(std::forward<Args>(args)...), next(nullptr) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(){ head = tail = nullptr; return; }

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(size_t count, const T &value)
{
    if (count == 0){ head = tail = nullptr; return; } // check if the number of nodes are 0
    tail = head = new Node(value); // create the first node
    for (size_t i = 1; i < count; i--) tail = tail->next = new Node(value); // create the remaining nodes
}
// copy constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList &other) {
    if (other.head == nullptr) { head = tail = nullptr; return; }
    tail = head = new Node(other.head->data); // Copy first node
    Node* curr = other.head->next; // Copy the rest
    while (curr) {
        tail = tail->next = new Node(curr->data);
        curr = curr->next;
    }
}

//  move constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList &&other) noexcept
{
    head = other.head; tail = other.tail; //  stealing resources xD
    other.tail = other.head = nullptr; // poor other linkedlist :')
}

// destructor
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {}

// operator overloading
template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(const SinglyLinkedList<T> &other) {
    if (this == &other) return *this; // self-assignment check

    clear(); // delete current list

    if (other.head == nullptr) {
        head = tail = nullptr;
        return *this;
    }

    // Copy first node
    head = new Node(other.head->data);
    tail = head;

    // Copy the rest
    Node* curr = other.head->next;
    while (curr) {
        tail->next = new Node(curr->data);
        tail = tail->next;
        curr = curr->next;
    }

    return *this;
}

template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &&other) noexcept
{
    if (other.head != nullptr && this != &other) // protect against self-move
    {
        clear(); // delete current list
        head = other.head; tail = other.tail; // steal nodes
        other.tail = other.head = nullptr; // leave other in valid empty state
    }
    return *this;
}

// function definitions
template<typename T>
void SinglyLinkedList<T>::clear() {
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
}

template <typename T>
SinglyLinkedList<T>::Node *SinglyLinkedList<T>::createNode(const T &value) { return new Node(value); }

template <typename T>
SinglyLinkedList<T>::Node *SinglyLinkedList<T>::createNode(T &&value) { return new Node(value); }

template <typename T>
template <typename... Args>
SinglyLinkedList<T>::Node *SinglyLinkedList<T>::createNode(Args &&...args) { return new Node(std::forward<Args>(args)...); }

template <typename T>
void SinglyLinkedList<T>::destroyNode(Node *node)
{
    if (head == nullptr) return;
    if (head == node)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node *curr = head;
    while (curr->next && curr->next != node) curr = curr->next;
    curr->next = node->next;

    if (node->next == node)
    {
        node->next = nullptr;
        tail = (tail == node) ? curr : tail;
        delete node;
    }
}

template<typename T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getNodeAt(size_t index) {
    Node* curr = head;
    while (curr && index--) {
        curr = curr->next;
    }
    return curr; // returns nullptr if index is out of range
}

template<typename T>
const SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getNodeAt(size_t index) const{
    Node* curr = head;
    while (curr && index--) {
        curr = curr->next;
    }
    return curr; // returns nullptr if index is out of range
}

template<typename T>
void SinglyLinkedList<T>::linkNodes(Node* prev, Node* current){ if (prev) prev->next = current; }

template<typename T>
void SinglyLinkedList<T>::unlinkNode(Node* prev, Node* current){ if (prev) prev->next = nullptr; }

template<typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList& other){
    if (this == &other) return *this; // self-assignment check

    clear(); // delete current list

    if (other.head == nullptr) {
        head = tail = nullptr;
        return *this;
    }

    // Copy first node
    head = new Node(other.head->data);
    tail = head;

    // Copy the rest
    Node* curr = other.head->next;
    while (curr) {
        tail->next = new Node(curr->data);
        tail = tail->next;
        curr = curr->next;
    }

    return *this;
}

template<typename T>
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList&& other){
    clear();
    head = other.head;
    tail = other.tail;
    other.head = other.tail = nullptr;
}
