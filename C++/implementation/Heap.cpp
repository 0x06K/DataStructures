//==================== PRIORITY QUEUE (HEAP) ====================
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

template<typename T>
class PriorityQueue {
private:
    T* heap;
    size_t size;
    size_t capacity;
    bool is_max_heap;
    
    // Private helper functions to implement
    void reallocate(size_t new_capacity);
    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
    size_t parent(size_t index) const;
    size_t leftChild(size_t index) const;
    size_t rightChild(size_t index) const;
    bool hasParent(size_t index) const;
    bool hasLeftChild(size_t index) const;
    bool hasRightChild(size_t index) const;
    T& getParent(size_t index);
    T& getLeftChild(size_t index);
    T& getRightChild(size_t index);
    const T& getParent(size_t index) const;
    const T& getLeftChild(size_t index) const;
    const T& getRightChild(size_t index) const;
    void swapElements(size_t index1, size_t index2);
    bool compare(const T& a, const T& b) const;
    void buildHeap();
    void copyFrom(const PriorityQueue& other);
    void moveFrom(PriorityQueue&& other);
    void destroyElements();
    
public:
    // Constructors and Destructor
    PriorityQueue(bool max_heap = true);
    PriorityQueue(size_t initial_capacity, bool max_heap = true);
    PriorityQueue(T* array, size_t array_size, bool max_heap = true);
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue(PriorityQueue&& other) noexcept;
    ~PriorityQueue();
    
    // Assignment operators
    PriorityQueue& operator=(const PriorityQueue& other);
    PriorityQueue& operator=(PriorityQueue&& other) noexcept;
    
    // Element access
    T& top();
    const T& top() const;
    
    // Capacity
    size_t getSize() const;
    bool empty() const;
    size_t getCapacity() const;
    
    // Modifiers
    void push(const T& value);
    void push(T&& value);
    template<typename... Args>
    void emplace(Args&&... args);
    void pop();
    void clear();
    void swap(PriorityQueue& other);
    
    // Heap operations
    void buildHeapFromArray(T* array, size_t array_size);
    T* heapSort();
    bool isValidHeap() const;
    void changeKey(size_t index, const T& new_value);
    void increaseKey(size_t index, const T& new_value);
    void decreaseKey(size_t index, const T& new_value);
    
    // Merge operations
    void merge(PriorityQueue& other);
    static PriorityQueue mergePQueues(PriorityQueue& pq1, PriorityQueue& pq2);
    
    // Utility
    bool isMaxHeap() const;
    void switchHeapType();
    
    // Iterator class
    class Iterator {
    private:
        T* heap_data;
        size_t heap_size;
        size_t current_index;
        
    public:
        Iterator();
        Iterator(T* data, size_t size, size_t index);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* operator->() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };
    
    // Iterator functions (level-order traversal)
    Iterator begin();
    Iterator end();
    const Iterator begin() const;
    const Iterator end() const;
};

#endif
