//==================== QUEUE ====================
#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        
        // Node constructors to implement
        Node();
        Node(const T& value);
        Node(T&& value);
        template<typename... Args>
        Node(Args&&... args);
        ~Node();
    };
    
    Node* front_node;
    Node* rear_node;
    size_t size;
    
    // Private helper functions to implement
    Node* createNode(const T& value);
    Node* createNode(T&& value);
    template<typename... Args>
    Node* createNode(Args&&... args);
    void destroyNode(Node* node);
    void copyFrom(const Queue& other);
    void moveFrom(Queue&& other);
    
public:
    // Constructors and Destructor
    Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    ~Queue();
    
    // Assignment operators
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;
    
    // Element access
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    
    // Capacity
    size_t getSize() const;
    bool empty() const;
    
    // Modifiers
    void enqueue(const T& value);
    void enqueue(T&& value);
    template<typename... Args>
    void emplace(Args&&... args);
    void dequeue();
    void clear();
    void swap(Queue& other);
    
    // Comparison
    bool equals(const Queue& other) const;
    
    // Iterator class (front to back)
    class Iterator {
    private:
        Node* current;
        friend class Queue;
    public:
        Iterator();
        Iterator(Node* node);
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
    
    // Iterator functions
    Iterator begin();
    Iterator end();
    const Iterator begin() const;
    const Iterator end() const;
};

#endif
