#include <cstddef>
//==================== TRIE (PREFIX TREE) ====================
#ifndef TRIE_H
#define TRIE_H

class Trie {
private:
    static const int ALPHABET_SIZE = 26;  // For lowercase English letters
    
    struct TrieNode {
        TrieNode* children[ALPHABET_SIZE];
        bool is_end_of_word;
        int word_count;          // Count of words ending at this node
        int prefix_count;        // Count of words passing through this node
        char character;          // Character stored in this node
        TrieNode* parent;        // Parent node pointer
        
        // TrieNode constructors to implement
        TrieNode();
        TrieNode(char ch);
        TrieNode(const TrieNode& other);
        TrieNode& operator=(const TrieNode& other);
        ~TrieNode();
        
        // TrieNode helper methods to implement
        void initializeChildren();
        void copyChildren(const TrieNode& other);
        void destroyChildren();
        bool hasChildren() const;
        int getChildrenCount() const;
        TrieNode* getChild(char ch) const;
        void setChild(char ch, TrieNode* child);
        bool removeChild(char ch);
    };
    
    TrieNode* root;
    size_t word_count;
    size_t node_count;
    
    // Private helper functions to implement
    TrieNode* createNode();
    TrieNode* createNode(char ch);
    void destroyNode(TrieNode* node);
    void destroyTrie(TrieNode* node);
    TrieNode* copyTrie(TrieNode* node, TrieNode* parent);
    int charToIndex(char ch) const;
    char indexToChar(int index) const;
    bool isValidChar(char ch) const;
    
    // Core operation helpers to implement
    bool insertHelper(TrieNode* node, const char* word, int index);
    bool removeHelper(TrieNode* node, const char* word, int index);
    bool searchHelper(TrieNode* node, const char* word, int index) const;
    bool startsWithHelper(TrieNode* node, const char* prefix, int index) const;
    TrieNode* findNode(const char* word) const;
    TrieNode* findPrefixNode(const char* prefix) const;
    
    // Traversal and collection helpers to implement
    void collectAllWords(TrieNode* node, char* current_word, int depth, char**& words, int& word_index) const;
    void collectWordsWithPrefix(TrieNode* node, const char* prefix, char* current_word, int depth, char**& words, int& word_index) const;
    void getAllWordsHelper(TrieNode* node, char* buffer, int depth, char**& result, int& count) const;
    void getPrefixMatchesHelper(TrieNode* node, char* buffer, int depth, char**& result, int& count) const;
    
    // Utility helpers to implement
    int getMaxDepth(TrieNode* node) const;
    int getTotalNodes(TrieNode* node) const;
    void copyFrom(const Trie& other);
    void moveFrom(Trie&& other);
    
public:
    // Constructors and Destructor
    Trie();
    Trie(const Trie& other);
    Trie(Trie&& other) noexcept;
    ~Trie();
    
    // Assignment operators
    Trie& operator=(const Trie& other);
    Trie& operator=(Trie&& other) noexcept;
    
    // Core operations
    bool insert(const char* word);
    bool insert(const char* word, int count);
    bool remove(const char* word);
    bool search(const char* word) const;
    bool contains(const char* word) const;
    bool startsWith(const char* prefix) const;
    
    // Count operations
    int getWordCount(const char* word) const;
    int getPrefixCount(const char* prefix) const;
    size_t getTotalWords() const;
    size_t getTotalUniqueWords() const;
    
    // Capacity and properties
    bool empty() const;
    void clear();
    size_t getNodeCount() const;
    int getMaxDepth() const;
    void swap(Trie& other);
    
    // Word collection operations
    char** getAllWords(int& count) const;
    char** getWordsWithPrefix(const char* prefix, int& count) const;
    char** getWordsOfLength(int length, int& count) const;
    char* getLongestCommonPrefix() const;
    char* getLongestWord() const;
    char* getShortestWord() const;
    
    // Advanced operations
    char** getSuggestions(const char* prefix, int max_suggestions, int& count) const;
    char** getAutoComplete(const char* prefix, int max_completions, int& count) const;
    bool hasCommonPrefix(const char* word1, const char* word2) const;
    char* getCommonPrefix(const char* word1, const char* word2) const;
    
    // Iterator class for trie traversal
    class Iterator {
    private:
        struct IteratorState {
            TrieNode* node;
            int child_index;
            char character;
            IteratorState* next;
            
            IteratorState(TrieNode* n, int index, char ch);
        };
        
        IteratorState* state_stack;
        TrieNode* root_node;
        char* current_word;
        int word_length;
        int buffer_size;
        bool at_end;
        
        void pushState(TrieNode* node, int child_index, char ch);
        void popState();
        void clearStack();
        void findNextWord();
        void resizeBuffer(int new_size);
        
    public:
        Iterator();
        Iterator(TrieNode* root);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        ~Iterator();
        
        const char* operator*() const;
        const char* operator->() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        
        const char* getCurrentWord() const;
        int getCurrentWordLength() const;
        bool isAtEnd() const;
        void reset();
    };
    
    // Iterator functions
    Iterator begin();
    Iterator end();
    const Iterator begin() const;
    const Iterator end() const;
};

#endif