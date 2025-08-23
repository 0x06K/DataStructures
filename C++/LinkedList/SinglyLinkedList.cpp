#include <iostream>
#include "SinglyLinkedList.h"
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
SinglyLinkedList<T>::SinglyLinkedList(){ head = tail = nullptr; size = 0; return; }

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(size_t count, const T &value)
{
    size = 0;
    if (count == 0){ head = tail = nullptr; return; } // check if the number of nodes are 0
    tail = head = new Node(value); // create the first node
    for (size_t i = 1; i < count; i--){ // create the remaining nodes
        tail = tail->next = new Node(value);
        size++;
    } 
}
// copy constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList &other) {
    size = 0;
    if (other.head == nullptr) { head = tail = nullptr; return; }
    tail = head = new Node(other.head->data); // Copy first node
    Node* curr = other.head->next; // Copy the rest
    while (curr) {
        tail = tail->next = new Node(curr->data);
        curr = curr->next;
        size++;
    }
}

//  move constructor
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList &&other) noexcept
{
    size = other.size;
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
        size++;
    }

    return *this;
}

template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(SinglyLinkedList<T> &&other) noexcept
{
    if (other.head != nullptr && this != &other) // protect against self-move
    {
        clear(); // delete current list
        head = other.head; tail = other.tail; size = other.size; // steal nodes
        other.tail = other.head = nullptr; // leave other in valid empty state
    }
    return *this;
}

template<typename T>
T& SinglyLinkedList<T>::operator[](size_t index) {
    if(index > size) throw std::out_of_range("index out of range");
    Node* temp = head;
    while(index--) temp = temp->next;
    return temp->data;
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
    size = 0;
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
    size--;
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

template<typename T>
T& SinglyLinkedList<T>::at(size_t index){
    if(index > size)throw std::out_of_range("index out of range");
    Node* current = head;
    while(index-- && current) current = current->next;
    if(current) return current->data;
    
}

template<typename T>
const T& SinglyLinkedList<T>::at(size_t index) const{
    if(index > size)throw std::out_of_range("index out of range");
    Node* current = head;
    while(index-- && current) current = current->next;
    if(current) return current->data;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::push_front(const T& value){
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::push_front(T&& value){
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
template<typename... Args>
void SinglyLinkedList<T>::emplace_front(Args&&... args){
    Node* newNode = new Node(std::forward<Args>(args)...);
    newNode->next = head;
    head = newNode;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::pop_front(){
    if(!head) return;
    Node* temp = head;
    head=head->next;
    temp->next = nullptr;
    delete temp;
    size--;
}

template<typename T>
void SinglyLinkedList<T>::pop_back(){
    if(head == tail) { delete head; head = nullptr;size--; return; }
    Node* temp = head;
    while(temp->next != tail) temp = temp->next;
    delete tail;
    tail = temp;
    size--;
}

template<typename T>
void SinglyLinkedList<T>::insert(size_t index, const T& value){
    if(index > size) throw std::out_of_range("index out of range");
    if(index == size){
        tail = tail->next=new Node(value);
        size++;
        return;
    }
    Node* curr = head;
    while(index--) curr = curr->next;
    Node* next = curr->next;
    curr = curr->next = new Node(value);
    curr->next = next;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::insert(size_t index, T&& value){
    if(index > size) throw std::out_of_range("index out of range");
    if(index == size){
        tail = tail->next=new Node(value);
        size++;
        return;
    }
    Node* curr = head;
    while(index--) curr = curr->next;
    Node* next = curr->next;
    curr = curr->next = new Node(value);
    curr->next = next;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::insert(size_t index, size_t count, const T& value) { 
    if(index > size) throw std::out_of_range("index out of range");
    if(index == size){
        while(count--) {
            tail=tail->next=new Node(value);
            size++;
        }
        return;
    } else{
        Node* temp = head;
        while(index--) temp = temp->next;
        Node* next = temp->next;
        while(count--) {temp=temp->next = new Node(value); size++;}
        temp->next = next;
    }
}

template<typename T>
template<typename... Args>
void SinglyLinkedList<T>::emplace(size_t index, Args&&... args){ 
    if(index > size) throw std::out_of_range("index out of range");
    if(index == size){
        tail = tail->next=new Node(std::forward<Args>(args)...); size++;
        return;
    }
    Node* curr = head;
    while(index--) curr = curr->next;
    Node* next = curr->next;
    curr = curr->next = new Node(std::forward<Args>(args)...);
    curr->next = next;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::erase(size_t index){
    if(index > size) throw std::out_of_range("index out of range");
    Node* temp = head;
    while(index--) temp=temp->next;
    while(temp) {
        Node* next = temp->next;
        delete temp;
        temp = next;
        size--;
    }
}

template<typename T>
void SinglyLinkedList<T>::erase(size_t start_index, size_t end_index){
    size_t count = start_index - end_index;
    if(start_index > size || end_index > size) throw std::out_of_range("index out of range");
    Node* temp = head;
    while(start_index--) temp=temp->next;
    while(temp && count--) {
        Node* next = temp->next;
        delete temp;
        temp = next;
        size--;
    }
}

template<typename T>
void SinglyLinkedList<T>::resize(size_t new_size){
    if(new_size == size) return;
    else if(new_size < size) erase(new_size);
    else {
        size_t count = new_size - size;
        while(count--){ tail = tail->next = new Node(); size++;}
    }
}

template<typename T>
void SinglyLinkedList<T>::resize(size_t new_size, const T& value){
    if(new_size == size) return;
    else if(new_size < size) erase(new_size);
    else {
        size_t count = new_size - size;
        while(count--){ tail = tail->next = new Node(value); size++;}
    }
}
template<typename T>
void SinglyLinkedList<T>::assign(size_t count, const T& value){
    if(count > size ) throw std::out_of_range("index out of range");
    Node* temp = head;
    while(count--) { temp->data = value; temp=temp->next; }
}

template<typename T>
void SinglyLinkedList<T>::swap(SinglyLinkedList& other) {
    SinglyLinkedList* temp = head;
    head = other.head; tail = other.tail; size = other.size;
    other.head = temp.head; other.tail = temp.tail; other.size = temp.size;
}

template<typename T>
void SinglyLinkedList<T>::reverse(){
    // using double pointer technique
    // 2nd method is using recursion
    Node* curr = head, prev = nullptr;
    while(curr) {
        Node* next = curr->next;
        curr->next = prev;
        curr = next;
        prev = curr;
    }
}

template<typename T>
void SinglyLinkedList<T>::sort(){
    Node* curr = head, next = curr->next;
    while(curr){
        while(next) {
            if(curr->data > next->data) {
                T tempData = curr->data;
                curr->data = next->data;
                next->data = tempData;
            }
            next = next->next;
        }
        curr=curr->next;
    }
}

template<typename T>
void SinglyLinkedList<T>::merge(SinglyLinkedList<T>& other){
    tail->next = other.head;
    tail = other.tail;
    size += other.size;
}

template<typename T>
void SinglyLinkedList<T>::unique(){
    Node* curr = head, next = curr->next;
    while(curr){
        bool unique = true;
        while(next) {
            if(curr->data == next->data) {
                unique = false;
                break;
            }
            next = next->next;
        }
        if(unique) cout << curr->data << " ";
        curr=curr->next;
    }
}

template<typename T>
void SinglyLinkedList<T>::remove(const T& value) {
    if(head == nullptr) return;
    if(head->data == value){
        Node* prev = head;
        head=head->next;
        delete prev;
        return;
    }
    Node* curr = head->next, prev = head;
    while(curr) {
        if(curr->data == value) {
            prev->next = curr->next;
            curr->next = nullptr;
            delete curr;
        }
        prev = curr;
        curr = curr->next;
    }
}

template<typename T>
bool SinglyLinkedList<T>::contains(const T& value) const {
    if(head == nullptr) return false;
    
    Node* curr = head;   
    while(curr) {
        if(curr->data == value) return true;
        curr = curr->next;
    }
    return false;
}

template<typename T>
size_t SinglyLinkedList<T>::find(const T& value) const{
    if(head == nullptr) return static_cast<size_t>(-1);
    Node* curr = head;   
    for(int i = 0; curr; i++){
        if(curr->data == value) return i;
        curr = curr->next;
    }
    return static_cast<size_t>(-1);
}

template<typename T>
size_t SinglyLinkedList<T>::findLast(const T& value) const {
    size_t index = 0;
    size_t lastFound = static_cast<size_t>(-1); // "not found" marker
    Node* curr = head;

    while (curr) {
        if (curr->data == value) {
            lastFound = index;
        }
        curr = curr->next;
        ++index;
    }

    return lastFound;
}

template<typename T>
size_t SinglyLinkedList<T>::count(const T& value) const {
    size_t cnt = 0;
    Node* curr = head;

    while (curr) {
        if (curr->data == value) {
            ++cnt;
        }
        curr = curr->next;
    }

    return cnt;
}

template<typename T>
bool SinglyLinkedList<T>::equals(const SinglyLinkedList& other) const {
    Node* curr1 = head;
    Node* curr2 = other.head;

    while (curr1 && curr2) {
        if (curr1->data != curr2->data) {
            return false;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    // both must end at the same time
    return curr1 == nullptr && curr2 == nullptr;
}

