//==================== BINARY SEARCH TREE ====================
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

template<typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;
        int height;
        
        // Node constructors to implement
        Node();
        Node(const T& value);
        Node(T&& value);
        template<typename... Args>
        Node(Args&&... args);
        ~Node();
    };
    
    Node* root;
    size_t size;
    
    // Private helper functions to implement
    Node* createNode(const T& value);
    Node* createNode(T&& value);
    template<typename... Args>
    Node* createNode(Args&&... args);
    void destroyNode(Node* node);
    void destroyTree(Node* node);
    Node* copyTree(Node* node, Node* parent);
    
    // Tree operations helpers
    Node* insertHelper(Node* node, const T& value, Node* parent);
    Node* insertHelper(Node* node, T&& value, Node* parent);
    Node* removeHelper(Node* node, const T& value);
    Node* findHelper(Node* node, const T& value) const;
    Node* findMin(Node* node) const;
    Node* findMax(Node* node) const;
    Node* findSuccessor(Node* node) const;
    Node* findPredecessor(Node* node) const;
    
    // Traversal helpers
    template<typename Func>
    void inorderHelper(Node* node, Func func) const;
    template<typename Func>
    void preorderHelper(Node* node, Func func) const;
    template<typename Func>
    void postorderHelper(Node* node, Func func) const;
    template<typename Func>
    void levelorderHelper(Func func) const;
    
    // Utility helpers
    int getHeight(Node* node) const;
    void updateHeight(Node* node);
    int getBalance(Node* node) const;
    bool isValidBST(Node* node, const T* min_val, const T* max_val) const;
    void copyFrom(const BinarySearchTree& other);
    void moveFrom(BinarySearchTree&& other);
    
public:
    // Constructors and Destructor
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree(BinarySearchTree&& other) noexcept;
    ~BinarySearchTree();
    
    // Assignment operators
    BinarySearchTree& operator=(const BinarySearchTree& other);
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;
    
    // Modifiers
    void insert(const T& value);
    void insert(T&& value);
    template<typename... Args>
    void emplace(Args&&... args);
    bool remove(const T& value);
    void clear();
    void swap(BinarySearchTree& other);
    
    // Search operations
    bool contains(const T& value) const;
    Node* find(const T& value);
    const Node* find(const T& value) const;
    T& findMin();
    const T& findMin() const;
    T& findMax();
    const T& findMax() const;
    
    // Capacity
    size_t getSize() const;
    bool empty() const;
    int height() const;
    bool isValid() const;
    
    // Traversals
    template<typename Func>
    void inorderTraversal(Func func) const;
    template<typename Func>
    void preorderTraversal(Func func) const;
    template<typename Func>
    void postorderTraversal(Func func) const;
    template<typename Func>
    void levelorderTraversal(Func func) const;
    
    // Tree operations
    BinarySearchTree merge(const BinarySearchTree& other) const;
    void balance();
    Node* lowestCommonAncestor(const T& val1, const T& val2);
    int diameter() const;
    bool isBalanced() const;
    
    // Iterator class (inorder traversal)
    class Iterator {
    private:
        struct StackNode {
            Node* node;
            StackNode* next;
            StackNode(Node* n);
        };
        StackNode* stack_top;
        Node* current;
        
        void pushLeft(Node* node);
        void pushStack(Node* node);
        Node* popStack();
        void clearStack();
        
    public:
        Iterator();
        Iterator(Node* root);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        ~Iterator();
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
