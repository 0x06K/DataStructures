//==================== DOUBLY LINKED LIST IMPLEMENTATION ====================

#include <stdexcept>
#include <algorithm>
#include "DoublyLinkedList.h"

//==================== NODE CONSTRUCTORS ====================

template<typename T>
DoublyLinkedList<T>::Node::Node() : data(), next(nullptr), prev(nullptr) {}

template<typename T>
DoublyLinkedList<T>::Node::Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

template<typename T>
DoublyLinkedList<T>::Node::Node(T&& value) : data(std::move(value)), next(nullptr), prev(nullptr) {}

template<typename T>
template<typename... Args>
DoublyLinkedList<T>::Node::Node(Args&&... args) : data(std::forward<Args>(args)...), next(nullptr), prev(nullptr) {}

template<typename T>
DoublyLinkedList<T>::Node::~Node() {}

//==================== PRIVATE HELPER FUNCTIONS ====================

template<typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::createNode(const T& value) {
    return new Node(value);
}

template<typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::createNode(T&& value) {
    return new Node(std::move(value));
}

template<typename T>
template<typename... Args>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::createNode(Args&&... args) {
    return new Node(std::forward<Args>(args)...);
}

template<typename T>
void DoublyLinkedList<T>::destroyNode(Node* node) {
    delete node;
}

template<typename T>
typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::getNodeAt(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    Node* current;
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = tail;
        for (size_t i = size - 1; i > index; --i) {
            current = current->prev;
        }
    }
    return current;
}

template<typename T>
const typename DoublyLinkedList<T>::Node* DoublyLinkedList<T>::getNodeAt(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    const Node* current;
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
    } else {
        current = tail;
        for (size_t i = size - 1; i > index; --i) {
            current = current->prev;
        }
    }
    return current;
}

template<typename T>
void DoublyLinkedList<T>::linkNodes(Node* prev, Node* current, Node* next) {
    if (current) {
        current->prev = prev;
        current->next = next;
    }
    if (prev) {
        prev->next = current;
    }
    if (next) {
        next->prev = current;
    }
}

template<typename T>
void DoublyLinkedList<T>::unlinkNode(Node* node) {
    if (!node) return;
    
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }
    
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }
    
    node->prev = nullptr;
    node->next = nullptr;
}

template<typename T>
void DoublyLinkedList<T>::insertNodeAfter(Node* pos, Node* new_node) {
    if (!pos) {
        if (empty()) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    } else {
        new_node->next = pos->next;
        new_node->prev = pos;
        if (pos->next) {
            pos->next->prev = new_node;
        } else {
            tail = new_node;
        }
        pos->next = new_node;
    }
}

template<typename T>
void DoublyLinkedList<T>::insertNodeBefore(Node* pos, Node* new_node) {
    if (!pos) {
        if (empty()) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
    } else {
        new_node->prev = pos->prev;
        new_node->next = pos;
        if (pos->prev) {
            pos->prev->next = new_node;
        } else {
            head = new_node;
        }
        pos->prev = new_node;
    }
}

template<typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList& other) {
    clear();
    for (const Node* current = other.head; current != nullptr; current = current->next) {
        push_back(current->data);
    }
}

template<typename T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList&& other) {
    head = other.head;
    tail = other.tail;
    size = other.size;
    
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

//==================== CONSTRUCTORS AND DESTRUCTOR ====================

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(size_t count, const T& value) : head(nullptr), tail(nullptr), size(0) {
    for (size_t i = 0; i < count; ++i) {
        push_back(value);
    }
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    copyFrom(other);
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& other) noexcept : head(nullptr), tail(nullptr), size(0) {
    moveFrom(std::move(other));
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

//==================== ASSIGNMENT OPERATORS ====================

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        moveFrom(std::move(other));
    }
    return *this;
}

//==================== ELEMENT ACCESS ====================

template<typename T>
T& DoublyLinkedList<T>::front() {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

template<typename T>
const T& DoublyLinkedList<T>::front() const {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

template<typename T>
T& DoublyLinkedList<T>::back() {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    return tail->data;
}

template<typename T>
const T& DoublyLinkedList<T>::back() const {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    return tail->data;
}

template<typename T>
T& DoublyLinkedList<T>::at(size_t index) {
    return getNodeAt(index)->data;
}

template<typename T>
const T& DoublyLinkedList<T>::at(size_t index) const {
    return getNodeAt(index)->data;
}

template<typename T>
T& DoublyLinkedList<T>::operator[](size_t index) {
    return getNodeAt(index)->data;
}

template<typename T>
const T& DoublyLinkedList<T>::operator[](size_t index) const {
    return getNodeAt(index)->data;
}

//==================== CAPACITY ====================

template<typename T>
size_t DoublyLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
bool DoublyLinkedList<T>::empty() const {
    return size == 0;
}

//==================== MODIFIERS ====================

template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    Node* new_node = createNode(value);
    if (empty()) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    ++size;
}

template<typename T>
void DoublyLinkedList<T>::push_front(T&& value) {
    Node* new_node = createNode(std::move(value));
    if (empty()) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    ++size;
}

template<typename T>
template<typename... Args>
void DoublyLinkedList<T>::emplace_front(Args&&... args) {
    Node* new_node = createNode(std::forward<Args>(args)...);
    if (empty()) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    ++size;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    
    Node* old_head = head;
    if (size == 1) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    
    destroyNode(old_head);
    --size;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node* new_node = createNode(value);
    if (empty()) {
        head = tail = new_node;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    ++size;
}

template<typename T>
void DoublyLinkedList<T>::push_back(T&& value) {
    Node* new_node = createNode(std::move(value));
    if (empty()) {
        head = tail = new_node;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    ++size;
}

template<typename T>
template<typename... Args>
void DoublyLinkedList<T>::emplace_back(Args&&... args) {
    Node* new_node = createNode(std::forward<Args>(args)...);
    if (empty()) {
        head = tail = new_node;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    ++size;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    
    Node* old_tail = tail;
    if (size == 1) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    
    destroyNode(old_tail);
    --size;
}

template<typename T>
void DoublyLinkedList<T>::insert(size_t index, const T& value) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    if (index == 0) {
        push_front(value);
    } else if (index == size) {
        push_back(value);
    } else {
        Node* pos = getNodeAt(index);
        Node* new_node = createNode(value);
        insertNodeBefore(pos, new_node);
        ++size;
    }
}

template<typename T>
void DoublyLinkedList<T>::insert(size_t index, T&& value) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    if (index == 0) {
        push_front(std::move(value));
    } else if (index == size) {
        push_back(std::move(value));
    } else {
        Node* pos = getNodeAt(index);
        Node* new_node = createNode(std::move(value));
        insertNodeBefore(pos, new_node);
        ++size;
    }
}

template<typename T>
void DoublyLinkedList<T>::insert(size_t index, size_t count, const T& value) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    for (size_t i = 0; i < count; ++i) {
        insert(index + i, value);
    }
}

template<typename T>
template<typename... Args>
void DoublyLinkedList<T>::emplace(size_t index, Args&&... args) {
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    if (index == 0) {
        emplace_front(std::forward<Args>(args)...);
    } else if (index == size) {
        emplace_back(std::forward<Args>(args)...);
    } else {
        Node* pos = getNodeAt(index);
        Node* new_node = createNode(std::forward<Args>(args)...);
        insertNodeBefore(pos, new_node);
        ++size;
    }
}

template<typename T>
void DoublyLinkedList<T>::erase(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    
    Node* node = getNodeAt(index);
    unlinkNode(node);
    destroyNode(node);
    --size;
}

template<typename T>
void DoublyLinkedList<T>::erase(size_t start_index, size_t end_index) {
    if (start_index >= size || end_index > size || start_index > end_index) {
        throw std::out_of_range("Invalid range");
    }
    
    for (size_t i = start_index; i < end_index; ++i) {
        erase(start_index); // Always erase at start_index as elements shift
    }
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void DoublyLinkedList<T>::resize(size_t new_size) {
    if (new_size < size) {
        while (size > new_size) {
            pop_back();
        }
    } else if (new_size > size) {
        while (size < new_size) {
            push_back(T());
        }
    }
}

template<typename T>
void DoublyLinkedList<T>::resize(size_t new_size, const T& value) {
    if (new_size < size) {
        while (size > new_size) {
            pop_back();
        }
    } else if (new_size > size) {
        while (size < new_size) {
            push_back(value);
        }
    }
}

template<typename T>
void DoublyLinkedList<T>::assign(size_t count, const T& value) {
    clear();
    for (size_t i = 0; i < count; ++i) {
        push_back(value);
    }
}

template<typename T>
void DoublyLinkedList<T>::swap(DoublyLinkedList& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}

//==================== OPERATIONS ====================

template<typename T>
void DoublyLinkedList<T>::reverse() {
    if (size <= 1) return;
    
    Node* current = head;
    while (current) {
        std::swap(current->next, current->prev);
        current = current->prev; // prev is now next after swap
    }
    std::swap(head, tail);
}

template<typename T>
void DoublyLinkedList<T>::sort() {
    if (size <= 1) return;
    
    // Simple bubble sort implementation
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current && current->next) {
            if (current->data > current->next->data) {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

template<typename T>
void DoublyLinkedList<T>::merge(DoublyLinkedList& other) {
    if (other.empty()) return;
    
    if (empty()) {
        moveFrom(std::move(other));
        return;
    }
    
    tail->next = other.head;
    other.head->prev = tail;
    tail = other.tail;
    size += other.size;
    
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template<typename T>
void DoublyLinkedList<T>::unique() {
    if (size <= 1) return;
    
    Node* current = head;
    while (current && current->next) {
        if (current->data == current->next->data) {
            Node* duplicate = current->next;
            unlinkNode(duplicate);
            destroyNode(duplicate);
            --size;
        } else {
            current = current->next;
        }
    }
}

template<typename T>
void DoublyLinkedList<T>::remove(const T& value) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        if (current->data == value) {
            unlinkNode(current);
            destroyNode(current);
            --size;
        }
        current = next;
    }
}

template<typename T>
template<typename Predicate>
void DoublyLinkedList<T>::removeIf(Predicate pred) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        if (pred(current->data)) {
            unlinkNode(current);
            destroyNode(current);
            --size;
        }
        current = next;
    }
}

//==================== SEARCH AND COMPARISON ====================

template<typename T>
bool DoublyLinkedList<T>::contains(const T& value) const {
    return find(value) != size;
}

template<typename T>
size_t DoublyLinkedList<T>::find(const T& value) const {
    Node* current = head;
    size_t index = 0;
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        ++index;
    }
    return size; // Not found
}

template<typename T>
size_t DoublyLinkedList<T>::findLast(const T& value) const {
    Node* current = tail;
    size_t index = size - 1;
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->prev;
        --index;
    }
    return size; // Not found
}

template<typename T>
size_t DoublyLinkedList<T>::count(const T& value) const {
    size_t count = 0;
    Node* current = head;
    while (current) {
        if (current->data == value) {
            ++count;
        }
        current = current->next;
    }
    return count;
}

template<typename T>
bool DoublyLinkedList<T>::equals(const DoublyLinkedList& other) const {
    if (size != other.size) {
        return false;
    }
    
    Node* current1 = head;
    Node* current2 = other.head;
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
DoublyLinkedList<T>::Iterator::Iterator() : current(nullptr) {}

template<typename T>
DoublyLinkedList<T>::Iterator::Iterator(Node* node) : current(node) {}

template<typename T>
DoublyLinkedList<T>::Iterator::Iterator(const Iterator& other) : current(other.current) {}

template<typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator=(const Iterator& other) {
    current = other.current;
    return *this;
}

template<typename T>
T& DoublyLinkedList<T>::Iterator::operator*() {
    return current->data;
}

template<typename T>
const T& DoublyLinkedList<T>::Iterator::operator*() const {
    return current->data;
}

template<typename T>
T* DoublyLinkedList<T>::Iterator::operator->() {
    return &(current->data);
}

template<typename T>
const T* DoublyLinkedList<T>::Iterator::operator->() const {
    return &(current->data);
}

template<typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator++(int) {
    Iterator temp(*this);
    current = current->next;
    return temp;
}

template<typename T>
typename DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator--() {
    current = current->prev;
    return *this;
}

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::Iterator::operator--(int) {
    Iterator temp(*this);
    current = current->prev;
    return temp;
}

template<typename T>
bool DoublyLinkedList<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template<typename T>
bool DoublyLinkedList<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

//==================== REVERSE ITERATOR IMPLEMENTATION ====================

template<typename T>
DoublyLinkedList<T>::ReverseIterator::ReverseIterator() : current(nullptr) {}

template<typename T>
DoublyLinkedList<T>::ReverseIterator::ReverseIterator(Node* node) : current(node) {}

template<typename T>
DoublyLinkedList<T>::ReverseIterator::ReverseIterator(const ReverseIterator& other) : current(other.current) {}

template<typename T>
typename DoublyLinkedList<T>::ReverseIterator& DoublyLinkedList<T>::ReverseIterator::operator=(const ReverseIterator& other) {
    current = other.current;
    return *this;
}

template<typename T>
T& DoublyLinkedList<T>::ReverseIterator::operator*() {
    return current->data;
}

template<typename T>
const T& DoublyLinkedList<T>::ReverseIterator::operator*() const {
    return current->data;
}

template<typename T>
T* DoublyLinkedList<T>::ReverseIterator::operator->() {
    return &(current->data);
}

template<typename T>
const T* DoublyLinkedList<T>::ReverseIterator::operator->() const {
    return &(current->data);
}

template<typename T>
typename DoublyLinkedList<T>::ReverseIterator& DoublyLinkedList<T>::ReverseIterator::operator++() {
    current = current->prev;
    return *this;
}

template<typename T>
typename DoublyLinkedList<T>::ReverseIterator DoublyLinkedList<T>::ReverseIterator::operator++(int) {
    ReverseIterator temp(*this);
    current = current->prev;
    return temp;
}

template<typename T>
typename DoublyLinkedList<T>::ReverseIterator& DoublyLinkedList<T>::ReverseIterator::operator--() {
    current = current->next;
    return *this;
}

template<typename T>
typename DoublyLinkedList<T>::ReverseIterator DoublyLinkedList<T>::ReverseIterator::operator--(int) {
    ReverseIterator temp(*this);
    current = current->next;
    return temp;
}

template<typename T>
bool DoublyLinkedList<T>::ReverseIterator::operator==(const ReverseIterator& other) const {
    return current == other.current;
}

template<typename T>
bool DoublyLinkedList<T>::ReverseIterator::operator!=(const ReverseIterator& other) const {
    return current != other.current;
}

//==================== ITERATOR FUNCTIONS ====================

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
const typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() const {
    return Iterator(head);
}

template<typename T>
const typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() const {
    return Iterator(nullptr);
}

template<typename T>
typename DoublyLinkedList<T>::ReverseIterator DoublyLinkedList<T>::rbegin() {
    return ReverseIterator(tail);
}

template<typename T>
typename DoublyLinkedList<T>::ReverseIterator DoublyLinkedList<T>::rend() {
    return ReverseIterator(nullptr);
}

template<typename T>
const typename DoublyLinkedList<T>::ReverseIterator DoublyLinkedList<T>::rbegin() const {
    return ReverseIterator(tail);
}

template<typename T>
const typename DoublyLinkedList<T>::ReverseIterator DoublyLinkedList<T>::rend() const {
    return ReverseIterator(nullptr);
}