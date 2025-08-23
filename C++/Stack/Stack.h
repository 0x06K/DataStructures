//==================== STACK ====================

#ifndef STACK_H
#define STACK_H

template<typename T>
class Stack {
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
    
    Node* top_node;
    size_t size;
    
    // Private helper functions to implement
    Node* createNode(const T& value);
    Node* createNode(T&& value);
    template<typename... Args>
    Node* createNode(Args&&... args);
    void destroyNode(Node* node);
    void copyFrom(const Stack& other);
    void moveFrom(Stack&& other);
    
public:
    // Constructors and Destructor
    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack();
    
    // Assignment operators
    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;
    
    // Element access
    T& top();
    const T& top() const;
    
    // Capacity
    size_t getSize() const;
    bool empty() const;
    
    // Modifiers
    void push(const T& value);
    void push(T&& value);
    template<typename... Args>
    void emplace(Args&&... args);
    void pop();
    void clear();
    void swap(Stack& other);
    
    // Comparison
    bool equals(const Stack& other) const;
    
    // Iterator class (top to bottom)
    class Iterator {
    private:
        Node* current;
        friend class Stack;
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
