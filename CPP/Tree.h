struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;
    
    // Private helper functions (recursive implementations)
    TreeNode* insertHelper(TreeNode* node, int data);
    TreeNode* searchHelper(TreeNode* node, int data);
    TreeNode* removeHelper(TreeNode* node, int data);
    TreeNode* findMinHelper(TreeNode* node);
    TreeNode* findMaxHelper(TreeNode* node);
    void inorderHelper(TreeNode* node);
    void preorderHelper(TreeNode* node);
    void postorderHelper(TreeNode* node);
    int heightHelper(TreeNode* node);
    int sizeHelper(TreeNode* node);
    void destroyHelper(TreeNode* node);
    
public:
    // Constructor & Destructor
    BinarySearchTree(int = 0);
    ~BinarySearchTree();
    
    // Basic Operations
    void insert(int data);
    bool search(int data);
    void remove(int data);
    void display();
    
    // Traversals
    void inorder();
    void preorder();
    void postorder();
    void levelorder();
    
    // Utility Functions
    int height();
    int size();
    bool isEmpty();
    void clear();
    int findMin();
    int findMax();
    bool isBalanced();
    int getLeafCount();
};