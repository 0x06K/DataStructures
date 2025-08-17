//==================== DOUBLY LINKED LIST ====================
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        // Node constructors to implement
        Node();
        Node(const T& value);
        Node(T&& value);
        template<typename... Args>
        Node(Args&&... args);
        ~Node();
    };
    
    Node* head;
    Node* tail;
    size_t size;
    
    // Private helper functions to implement
    Node* createNode(const T& value);
    Node* createNode(T&& value);
    template<typename... Args>
    Node* createNode(Args&&... args);
    void destroyNode(Node* node);
    Node* getNodeAt(size_t index);
    const Node* getNodeAt(size_t index) const;
    void linkNodes(Node* prev, Node* current, Node* next);
    void unlinkNode(Node* node);
    void insertNodeAfter(Node* pos, Node* new_node);
    void insertNodeBefore(Node* pos, Node* new_node);
    void copyFrom(const DoublyLinkedList& other);
    void moveFrom(DoublyLinkedList&& other);
    
public:
    // Constructors and Destructor
    DoublyLinkedList();
    DoublyLinkedList(size_t count, const T& value);
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList(DoublyLinkedList&& other) noexcept;
    ~DoublyLinkedList();
    
    // Assignment operators
    DoublyLinkedList& operator=(const DoublyLinkedList& other);
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept;
    
    // Element access
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    
    // Capacity
    size_t getSize() const;
    bool empty() const;
    
    // Modifiers
    void push_front(const T& value);
    void push_front(T&& value);
    template<typename... Args>
    void emplace_front(Args&&... args);
    void pop_front();
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
    void swap(DoublyLinkedList& other);
    
    // Operations
    void reverse();
    void sort();
    void merge(DoublyLinkedList& other);
    void unique();
    void remove(const T& value);
    template<typename Predicate>
    void removeIf(Predicate pred);
    
    // Search and comparison
    bool contains(const T& value) const;
    size_t find(const T& value) const;
    size_t findLast(const T& value) const;
    size_t count(const T& value) const;
    bool equals(const DoublyLinkedList& other) const;
    
    // Forward Iterator class
    class Iterator {
    private:
        Node* current;
        friend class DoublyLinkedList;
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
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };
    
    // Reverse Iterator class
    class ReverseIterator {
    private:
        Node* current;
        friend class DoublyLinkedList;
    public:
        ReverseIterator();
        ReverseIterator(Node* node);
        ReverseIterator(const ReverseIterator& other);
        ReverseIterator& operator=(const ReverseIterator& other);
        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* operator->() const;
        ReverseIterator& operator++();
        ReverseIterator operator++(int);
        ReverseIterator& operator--();
        ReverseIterator operator--(int);
        bool operator==(const ReverseIterator& other) const;
        bool operator!=(const ReverseIterator& other) const;
    };
    
    // Iterator functions
    Iterator begin();
    Iterator end();
    const Iterator begin() const;
    const Iterator end() const;
    ReverseIterator rbegin();
    ReverseIterator rend();
    const ReverseIterator rbegin() const;
    const ReverseIterator rend() const;
};

#endif
