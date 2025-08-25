#include <stdexcept>
#include <algorithm>
#include <utility>
#include "PriorityQueue.h"
//==================== PRIVATE HELPER FUNCTIONS ====================

template<typename T>
void PriorityQueue<T>::reallocate(size_t new_capacity) {
    T* new_heap = new T[new_capacity];
    for (size_t i = 0; i < size; ++i) {
        new_heap[i] = std::move(heap[i]);
    }
    delete[] heap;
    heap = new_heap;
    capacity = new_capacity;
}

template<typename T>
void PriorityQueue<T>::heapifyUp(size_t index) {
    while (hasParent(index) && compare(heap[index], getParent(index))) {
        swapElements(index, parent(index));
        index = parent(index);
    }
}

template<typename T>
void PriorityQueue<T>::heapifyDown(size_t index) {
    while (hasLeftChild(index)) {
        size_t target_child = leftChild(index);
        if (hasRightChild(index) && compare(getRightChild(index), getLeftChild(index))) {
            target_child = rightChild(index);
        }
        
        if (compare(heap[index], heap[target_child])) {
            break;
        }
        
        swapElements(index, target_child);
        index = target_child;
    }
}

template<typename T>
size_t PriorityQueue<T>::parent(size_t index) const {
    return (index - 1) / 2;
}

template<typename T>
size_t PriorityQueue<T>::leftChild(size_t index) const {
    return 2 * index + 1;
}

template<typename T>
size_t PriorityQueue<T>::rightChild(size_t index) const {
    return 2 * index + 2;
}

template<typename T>
bool PriorityQueue<T>::hasParent(size_t index) const {
    return index > 0;
}

template<typename T>
bool PriorityQueue<T>::hasLeftChild(size_t index) const {
    return leftChild(index) < size;
}

template<typename T>
bool PriorityQueue<T>::hasRightChild(size_t index) const {
    return rightChild(index) < size;
}

template<typename T>
T& PriorityQueue<T>::getParent(size_t index) {
    return heap[parent(index)];
}

template<typename T>
T& PriorityQueue<T>::getLeftChild(size_t index) {
    return heap[leftChild(index)];
}

template<typename T>
T& PriorityQueue<T>::getRightChild(size_t index) {
    return heap[rightChild(index)];
}

template<typename T>
const T& PriorityQueue<T>::getParent(size_t index) const {
    return heap[parent(index)];
}

template<typename T>
const T& PriorityQueue<T>::getLeftChild(size_t index) const {
    return heap[leftChild(index)];
}

template<typename T>
const T& PriorityQueue<T>::getRightChild(size_t index) const {
    return heap[rightChild(index)];
}

template<typename T>
void PriorityQueue<T>::swapElements(size_t index1, size_t index2) {
    std::swap(heap[index1], heap[index2]);
}

template<typename T>
bool PriorityQueue<T>::compare(const T& a, const T& b) const {
    return is_max_heap ? (a > b) : (a < b);
}

template<typename T>
void PriorityQueue<T>::buildHeap() {
    if (size <= 1) return;
    for (int i = static_cast<int>(parent(size - 1)); i >= 0; --i) {
        heapifyDown(static_cast<size_t>(i));
    }
}

template<typename T>
void PriorityQueue<T>::copyFrom(const PriorityQueue& other) {
    heap = new T[other.capacity];
    size = other.size;
    capacity = other.capacity;
    is_max_heap = other.is_max_heap;
    for (size_t i = 0; i < size; ++i) {
        heap[i] = other.heap[i];
    }
}

template<typename T>
void PriorityQueue<T>::moveFrom(PriorityQueue&& other) {
    heap = other.heap;
    size = other.size;
    capacity = other.capacity;
    is_max_heap = other.is_max_heap;
    
    other.heap = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
void PriorityQueue<T>::destroyElements() {
    delete[] heap;
    heap = nullptr;
    size = 0;
    capacity = 0;
}

//==================== CONSTRUCTORS AND DESTRUCTOR ====================

template<typename T>
PriorityQueue<T>::PriorityQueue(bool max_heap) 
    : heap(nullptr), size(0), capacity(16), is_max_heap(max_heap) {
    heap = new T[capacity];
}

template<typename T>
PriorityQueue<T>::PriorityQueue(size_t initial_capacity, bool max_heap) 
    : heap(nullptr), size(0), capacity(initial_capacity), is_max_heap(max_heap) {
    if (capacity == 0) capacity = 1;
    heap = new T[capacity];
}

template<typename T>
PriorityQueue<T>::PriorityQueue(T* array, size_t array_size, bool max_heap) 
    : heap(nullptr), size(array_size), capacity(array_size), is_max_heap(max_heap) {
    if (capacity == 0) capacity = 1;
    heap = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        heap[i] = array[i];
    }
    buildHeap();
}

template<typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& other) {
    copyFrom(other);
}

template<typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue&& other) noexcept {
    moveFrom(std::move(other));
}

template<typename T>
PriorityQueue<T>::~PriorityQueue() {
    destroyElements();
}

//==================== ASSIGNMENT OPERATORS ====================

template<typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue& other) {
    if (this != &other) {
        destroyElements();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(PriorityQueue&& other) noexcept {
    if (this != &other) {
        destroyElements();
        moveFrom(std::move(other));
    }
    return *this;
}

//==================== ELEMENT ACCESS ====================

template<typename T>
T& PriorityQueue<T>::top() {
    if (empty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    return heap[0];
}

template<typename T>
const T& PriorityQueue<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    return heap[0];
}

//==================== CAPACITY ====================

template<typename T>
size_t PriorityQueue<T>::getSize() const {
    return size;
}

template<typename T>
bool PriorityQueue<T>::empty() const {
    return size == 0;
}

template<typename T>
size_t PriorityQueue<T>::getCapacity() const {
    return capacity;
}

//==================== MODIFIERS ====================

template<typename T>
void PriorityQueue<T>::push(const T& value) {
    if (size >= capacity) {
        reallocate(capacity * 2);
    }
    heap[size] = value;
    heapifyUp(size);
    ++size;
}

template<typename T>
void PriorityQueue<T>::push(T&& value) {
    if (size >= capacity) {
        reallocate(capacity * 2);
    }
    heap[size] = std::move(value);
    heapifyUp(size);
    ++size;
}

template<typename T>
template<typename... Args>
void PriorityQueue<T>::emplace(Args&&... args) {
    if (size >= capacity) {
        reallocate(capacity * 2);
    }
    heap[size] = T(std::forward<Args>(args)...);
    heapifyUp(size);
    ++size;
}

template<typename T>
void PriorityQueue<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    heap[0] = std::move(heap[size - 1]);
    --size;
    if (size > 0) {
        heapifyDown(0);
    }
}

template<typename T>
void PriorityQueue<T>::clear() {
    size = 0;
}

template<typename T>
void PriorityQueue<T>::swap(PriorityQueue& other) {
    std::swap(heap, other.heap);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(is_max_heap, other.is_max_heap);
}

//==================== HEAP OPERATIONS ====================

template<typename T>
void PriorityQueue<T>::buildHeapFromArray(T* array, size_t array_size) {
    if (array_size > capacity) {
        reallocate(array_size);
    }
    size = array_size;
    for (size_t i = 0; i < size; ++i) {
        heap[i] = array[i];
    }
    buildHeap();
}

template<typename T>
T* PriorityQueue<T>::heapSort() {
    T* sorted = new T[size];
    PriorityQueue temp_pq(*this);
    
    for (size_t i = 0; i < size; ++i) {
        sorted[i] = temp_pq.top();
        temp_pq.pop();
    }
    
    return sorted;
}

template<typename T>
bool PriorityQueue<T>::isValidHeap() const {
    for (size_t i = 0; i < size; ++i) {
        if (hasLeftChild(i) && compare(getLeftChild(i), heap[i])) {
            return false;
        }
        if (hasRightChild(i) && compare(getRightChild(i), heap[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
void PriorityQueue<T>::changeKey(size_t index, const T& new_value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    T old_value = heap[index];
    heap[index] = new_value;
    
    if (compare(new_value, old_value)) {
        heapifyUp(index);
    } else if (compare(old_value, new_value)) {
        heapifyDown(index);
    }
}

template<typename T>
void PriorityQueue<T>::increaseKey(size_t index, const T& new_value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (is_max_heap && new_value < heap[index]) {
        throw std::invalid_argument("New value is smaller than current value in max heap");
    }
    if (!is_max_heap && new_value > heap[index]) {
        throw std::invalid_argument("New value is larger than current value in min heap");
    }
    heap[index] = new_value;
    heapifyUp(index);
}

template<typename T>
void PriorityQueue<T>::decreaseKey(size_t index, const T& new_value) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (is_max_heap && new_value > heap[index]) {
        throw std::invalid_argument("New value is larger than current value in max heap");
    }
    if (!is_max_heap && new_value < heap[index]) {
        throw std::invalid_argument("New value is smaller than current value in min heap");
    }
    heap[index] = new_value;
    heapifyDown(index);
}

//==================== MERGE OPERATIONS ====================

template<typename T>
void PriorityQueue<T>::merge(PriorityQueue& other) {
    if (is_max_heap != other.is_max_heap) {
        throw std::invalid_argument("Cannot merge heaps of different types");
    }
    
    size_t new_size = size + other.size;
    if (new_size > capacity) {
        reallocate(new_size);
    }
    
    for (size_t i = 0; i < other.size; ++i) {
        heap[size + i] = std::move(other.heap[i]);
    }
    
    size = new_size;
    buildHeap();
    other.clear();
}

template<typename T>
PriorityQueue<T> PriorityQueue<T>::mergePQueues(PriorityQueue& pq1, PriorityQueue& pq2) {
    if (pq1.is_max_heap != pq2.is_max_heap) {
        throw std::invalid_argument("Cannot merge heaps of different types");
    }
    
    PriorityQueue result(pq1.size + pq2.size, pq1.is_max_heap);
    
    for (size_t i = 0; i < pq1.size; ++i) {
        result.heap[i] = pq1.heap[i];
    }
    for (size_t i = 0; i < pq2.size; ++i) {
        result.heap[pq1.size + i] = pq2.heap[i];
    }
    
    result.size = pq1.size + pq2.size;
    result.buildHeap();
    return result;
}

//==================== UTILITY ====================

template<typename T>
bool PriorityQueue<T>::isMaxHeap() const {
    return is_max_heap;
}

template<typename T>
void PriorityQueue<T>::switchHeapType() {
    is_max_heap = !is_max_heap;
    buildHeap();
}

//==================== ITERATOR IMPLEMENTATION ====================

template<typename T>
PriorityQueue<T>::Iterator::Iterator() 
    : heap_data(nullptr), heap_size(0), current_index(0) {}

template<typename T>
PriorityQueue<T>::Iterator::Iterator(T* data, size_t size, size_t index) 
    : heap_data(data), heap_size(size), current_index(index) {}

template<typename T>
PriorityQueue<T>::Iterator::Iterator(const Iterator& other) 
    : heap_data(other.heap_data), heap_size(other.heap_size), current_index(other.current_index) {}

template<typename T>
typename PriorityQueue<T>::Iterator& PriorityQueue<T>::Iterator::operator=(const Iterator& other) {
    if (this != &other) {
        heap_data = other.heap_data;
        heap_size = other.heap_size;
        current_index = other.current_index;
    }
    return *this;
}

template<typename T>
T& PriorityQueue<T>::Iterator::operator*() {
    if (current_index >= heap_size) {
        throw std::out_of_range("Iterator out of range");
    }
    return heap_data[current_index];
}

template<typename T>
const T& PriorityQueue<T>::Iterator::operator*() const {
    if (current_index >= heap_size) {
        throw std::out_of_range("Iterator out of range");
    }
    return heap_data[current_index];
}

template<typename T>
T* PriorityQueue<T>::Iterator::operator->() {
    if (current_index >= heap_size) {
        throw std::out_of_range("Iterator out of range");
    }
    return &heap_data[current_index];
}

template<typename T>
const T* PriorityQueue<T>::Iterator::operator->() const {
    if (current_index >= heap_size) {
        throw std::out_of_range("Iterator out of range");
    }
    return &heap_data[current_index];
}

template<typename T>
typename PriorityQueue<T>::Iterator& PriorityQueue<T>::Iterator::operator++() {
    ++current_index;
    return *this;
}

template<typename T>
typename PriorityQueue<T>::Iterator PriorityQueue<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++current_index;
    return temp;
}

template<typename T>
bool PriorityQueue<T>::Iterator::operator==(const Iterator& other) const {
    return heap_data == other.heap_data && 
           heap_size == other.heap_size && 
           current_index == other.current_index;
}

template<typename T>
bool PriorityQueue<T>::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

//==================== ITERATOR FUNCTIONS ====================

template<typename T>
typename PriorityQueue<T>::Iterator PriorityQueue<T>::begin() {
    return Iterator(heap, size, 0);
}

template<typename T>
typename PriorityQueue<T>::Iterator PriorityQueue<T>::end() {
    return Iterator(heap, size, size);
}

template<typename T>
const typename PriorityQueue<T>::Iterator PriorityQueue<T>::begin() const {
    return Iterator(heap, size, 0);
}

template<typename T>
const typename PriorityQueue<T>::Iterator PriorityQueue<T>::end() const {
    return Iterator(heap, size, size);
}