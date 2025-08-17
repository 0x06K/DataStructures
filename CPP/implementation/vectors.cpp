//==================== DYNAMIC ARRAY ====================
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;
    
    // Private helper functions to implement
    void resize();
    void reallocate(size_t new_capacity);
    void copyData(const T* source, T* destination, size_t count);
    void destroyElements();
    void shiftElementsRight(size_t index, size_t positions);
    void shiftElementsLeft(size_t index, size_t positions);
    
public:
    // Constructors and Destructor
    DynamicArray();
    DynamicArray(size_t initial_capacity);
    DynamicArray(size_t count, const T& value);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    ~DynamicArray();
    
    // Assignment operators
    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other) noexcept;
    
    // Element access
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T* getData();
    const T* getData() const;
    
    // Capacity functions
    size_t getSize() const;
    size_t getCapacity() const;
    bool empty() const;
    void reserve(size_t new_capacity);
    void shrinkToFit();
    
    // Modifiers
    void push_back(const T& value);
    void push_back(T&& value);
    template<typename... Args>
    void emplace_back(Args&&... args);
    void pop_back();
    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value);
    void insert(size_t index, size_t count, const T& value);
    template<typename... Args>
    void emplace(size_t index, Args&&... args);
    void erase(size_t index);
    void erase(size_t start_index, size_t end_index);
    void clear();
    void resize(size_t new_size);
    void resize(size_t new_size, const T& value);
    void assign(size_t count, const T& value);
    void swap(DynamicArray& other);
    
    // Search and comparison
    bool contains(const T& value) const;
    size_t find(const T& value) const;
    size_t findLast(const T& value) const;
    size_t count(const T& value) const;
    bool equals(const DynamicArray& other) const;
    
    // Iterator class
    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* p);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* operator->() const;
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        Iterator operator+(size_t n) const;
        Iterator operator-(size_t n) const;
        Iterator& operator+=(size_t n);
        Iterator& operator-=(size_t n);
        ptrdiff_t operator-(const Iterator& other) const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        bool operator<(const Iterator& other) const;
        bool operator>(const Iterator& other) const;
        bool operator<=(const Iterator& other) const;
        bool operator>=(const Iterator& other) const;
        T& operator[](size_t n);
        const T& operator[](size_t n) const;
    };
    
    // Iterator functions
    Iterator begin();
    Iterator end();
    const Iterator begin() const;
    const Iterator end() const;
    Iterator rbegin();
    Iterator rend();
    const Iterator rbegin() const;
    const Iterator rend() const;
};

#endif