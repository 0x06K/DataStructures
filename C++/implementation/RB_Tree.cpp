//==================== RED-BLACK TREE ====================
#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

template<typename T>
class RedBlackTree {
private:
    enum Color { RED, BLACK };
    
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
        
        // Node constructors to implement
        Node();
        Node(const T& value, Color c = RED);
        Node(T&& value, Color c = RED);
        template<typename... Args>
        Node(Color c, Args&&... args);
        ~Node();
    };
    
    Node* root;
    Node* nil_node;  // Sentinel node
    size_t size;
    
    // Private helper functions to implement
    Node* createNode(const T& value, Color color = RED);
    Node* createNode(T&& value, Color color = RED);
    template<typename... Args>
    Node* createNode(Color color, Args&&... args);
    void destroyNode(Node* node);
    void destroyTree(Node* node);
    Node* copyTree(Node* node, Node* parent);
    void initializeNilNode();
    
    // Red-Black Tree specific operations to implement
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void insertFixup(Node* node);
    void deleteFixup(Node* node);
    void transplant(Node* u, Node* v);
    
    // Tree operations helpers to implement
    Node* insertHelper(const T& value);
    Node* insertHelper(T&& value);
    void deleteHelper(Node* node);
    Node* findHelper(Node* node, const T& value) const;
    Node* findMin(Node* node) const;
    Node* findMax(Node* node) const;
    Node* findSuccessor(Node* node) const;
    Node* findPredecessor(Node* node) const;
    
    // Traversal helpers to implement
    template<typename Func>
    void inorderHelper(Node* node, Func func) const;
    template<typename Func>
    void preorderHelper(Node* node, Func func) const;
    template<typename Func>
    void postorderHelper(Node* node, Func func) const;
    template<typename Func>
    void levelorderHelper(Func func) const;
    
    // Validation helpers to implement
    bool isValidRedBlackTree(Node* node, int& black_height) const;
    bool checkRedBlackProperties(Node* node) const;
    int getBlackHeight(Node* node) const;
    void copyFrom(const RedBlackTree& other);
    void moveFrom(RedBlackTree&& other);
    
public:
    // Constructors and Destructor
    RedBlackTree();
    RedBlackTree(const RedBlackTree& other);
    RedBlackTree(RedBlackTree&& other) noexcept;
    ~RedBlackTree();
    
    // Assignment operators
    RedBlackTree& operator=(const RedBlackTree& other);
    RedBlackTree& operator=(RedBlackTree&& other) noexcept;
    
    // Modifiers
    void insert(const T& value);
    void insert(T&& value);
    template<typename... Args>
    void emplace(Args&&... args);
    bool remove(const T& value);
    void clear();
    void swap(RedBlackTree& other);
    
    // Search operations
    bool contains(const T& value) const;
    Node* find(const T& value);
    const Node* find(const T& value) const;
    T& findMin();
    const T& findMin() const;
    T& findMax();
    const T& findMax() const;
    
    // Capacity and properties
    size_t getSize() const;
    bool empty() const;
    int height() const;
    int blackHeight() const;
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
    RedBlackTree merge(const RedBlackTree& other) const;
    Node* lowestCommonAncestor(const T& val1, const T& val2);
    
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
        Node* nil_sentinel;
        
        void pushLeft(Node* node);
        void pushStack(Node* node);
        Node* popStack();
        void clearStack();
        
    public:
        Iterator();
        Iterator(Node* root, Node* nil);
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