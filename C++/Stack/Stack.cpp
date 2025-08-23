//==================== STACK IMPLEMENTATION ====================

#include <stdexcept>
#include <algorithm>
#include "Stack.h"

//==================== NODE CONSTRUCTORS ====================

template<typename T>
Stack<T>::Node::Node() : data(), next(nullptr) {}

template<typename T>
Stack<T>::Node::Node(const T& value) : data(value), next(nullptr) {}

template<typename T>
Stack<T>::Node::Node(T&& value) : data(std::move(value)), next(nullptr) {}

template<typename T>
template<typename... Args>
Stack<T>::Node::Node(Args&&... args) : data(std::forward<Args>(args)...), next(nullptr) {}

template<typename T>
Stack<T>::Node::~Node() {}

//==================== PRIVATE HELPER FUNCTIONS ====================

template<typename T>
typename Stack<T>::Node* Stack<T>::createNode(const T& value) {
    return new Node(value);
}

template<typename T>
typename Stack<T>::Node* Stack<T>::createNode(T&& value) {
    return new Node(std::move(value));
}

template<typename T>
template<typename... Args>
typename Stack<T>::Node* Stack<T>::createNode(Args&&... args) {
    return new Node(std::forward<Args>(args)...);
}

template<typename T>
void Stack<T>::destroyNode(Node* node) {
    delete node;
}

template<typename T>
void Stack<T>::copyFrom(const Stack& other) {
    clear();
    
    if (other.empty()) {
        return;
    }
    
    // Create a temporary stack to reverse the order
    Stack<T> temp;
    Node* current = other.top_node;
    while (current) {
        temp.push(current->data);
        current = current->next;
    }
    
    // Copy from temp to maintain original order
    current = temp.top_node;
    while (current) {
        push(current->data);
        current = current->next;
    }
}

template<typename T>
void Stack<T>::moveFrom(Stack&& other) {
    top_node = other.top_node;
    size = other.size;
    
    other.top_node = nullptr;
    other.size = 0;
}

//==================== CONSTRUCTORS AND DESTRUCTOR ====================

template<typename T>
Stack<T>::Stack() : top_node(nullptr), size(0) {}

template<typename T>
Stack<T>::Stack(const Stack& other) : top_node(nullptr), size(0) {
    copyFrom(other);
}

template<typename T>
Stack<T>::Stack(Stack&& other) noexcept : top_node(nullptr), size(0) {
    moveFrom(std::move(other));
}

template<typename T>
Stack<T>::~Stack() {
    clear();
}

//==================== ASSIGNMENT OPERATORS ====================

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        clear();
        moveFrom(std::move(other));
    }
    return *this;
}

//==================== ELEMENT ACCESS ====================

template<typename T>
T& Stack<T>::top() {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top_node->data;
}

template<typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return top_node->data;
}

//==================== CAPACITY ====================

template<typename T>
size_t Stack<T>::getSize() const {
    return size;
}

template<typename T>
bool Stack<T>::empty() const {
    return size == 0;
}

//==================== MODIFIERS ====================

template<typename T>
void Stack<T>::push(const T& value) {
    Node* new_node = createNode(value);
    new_node->next = top_node;
    top_node = new_node;
    ++size;
}

template<typename T>
void Stack<T>::push(T&& value) {
    Node* new_node = createNode(std::move(value));
    new_node->next = top_node;
    top_node = new_node;
    ++size;
}

template<typename T>
template<typename... Args>
void Stack<T>::emplace(Args&&... args) {
    Node* new_node = createNode(std::forward<Args>(args)...);
    new_node->next = top_node;
    top_node = new_node;
    ++size;
}

template<typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    
    Node* old_top = top_node;
    top_node = top_node->next;
    destroyNode(old_top);
    --size;
}

template<typename T>
void Stack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void Stack<T>::swap(Stack& other) {
    std::swap(top_node, other.top_node);
    std::swap(size, other.size);
}

//==================== COMPARISON ====================

template<typename T>
bool Stack<T>::equals(const Stack& other) const {
    if (size != other.size) {
        return false;
    }
    
    Node* current1 = top_node;
    Node* current2 = other.top_node;
    
    while (current1) {
        if (current1->data != current2->data) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    
    return true;
}

//==================== ITERATOR IMPLEMENTATION ====================

template<typename T>
Stack<T>::Iterator::Iterator() : current(nullptr) {}

template<typename T>
Stack<T>::Iterator::Iterator(Node* node) : current(node) {}

template<typename T>
Stack<T>::Iterator::Iterator(const Iterator& other) : current(other.current) {}

template<typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator=(const Iterator& other) {
    current = other.current;
    return *this;
}

template<typename T>
T& Stack<T>::Iterator::operator*() {
    if (!current) {
        throw std::runtime_error("Iterator is null");
    }
    return current->data;
}

template<typename T>
const T& Stack<T>::Iterator::operator*() const {
    if (!current) {
        throw std::runtime_error("Iterator is null");
    }
    return current->data;
}

template<typename T>
T* Stack<T>::Iterator::operator->() {
    if (!current) {
        throw std::runtime_error("Iterator is null");
    }
    return &(current->data);
}

template<typename T>
const T* Stack<T>::Iterator::operator->() const {
    if (!current) {
        throw std::runtime_error("Iterator is null");
    }
    return &(current->data);
}

template<typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator++() {
    if (current) {
        current = current->next;
    }
    return *this;
}

template<typename T>
typename Stack<T>::Iterator Stack<T>::Iterator::operator++(int) {
    Iterator temp(*this);
    if (current) {
        current = current->next;
    }
    return temp;
}

template<typename T>
bool Stack<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template<typename T>
bool Stack<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

//==================== ITERATOR FUNCTIONS ====================

template<typename T>
typename Stack<T>::Iterator Stack<T>::begin() {
    return Iterator(top_node);
}

template<typename T>
typename Stack<T>::Iterator Stack<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
const typename Stack<T>::Iterator Stack<T>::begin() const {
    return Iterator(top_node);
}

template<typename T>
const typename Stack<T>::Iterator Stack<T>::end() const {
    return Iterator(nullptr);
}