//==================== HASH TABLE ====================
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

template<typename Key, typename Value>
class HashTable {
private:
    struct KeyValuePair {
        Key key;
        Value value;
        bool is_deleted;
        bool is_occupied;
        
        // KeyValuePair constructors to implement
        KeyValuePair();
        KeyValuePair(const Key& k, const Value& v);
        KeyValuePair(Key&& k, Value&& v);
        KeyValuePair(const KeyValuePair& other);
        KeyValuePair(KeyValuePair&& other) noexcept;
        KeyValuePair& operator=(const KeyValuePair& other);
        KeyValuePair& operator=(KeyValuePair&& other) noexcept;
        ~KeyValuePair();
    };
    
    KeyValuePair* buckets;
    size_t bucket_count;
    size_t size;
    size_t deleted_count;
    
    // Hash functions to implement
    size_t hash(const Key& key) const;
    size_t hash(const Key& key, size_t table_size) const;
    size_t doubleHash(const Key& key, size_t attempt) const;
    
    // Probing functions to implement
    size_t linearProbe(size_t hash_value, size_t attempt) const;
    size_t quadraticProbe(size_t hash_value, size_t attempt) const;
    size_t doubleHashProbe(size_t hash_value, size_t attempt, const Key& key) const;
    
    // Private helper functions to implement
    void rehash();
    void resize(size_t new_capacity);
    size_t findSlot(const Key& key) const;
    size_t findInsertSlot(const Key& key) const;
    bool needsResize() const;
    double loadFactor() const;
    size_t nextPrime(size_t n) const;
    bool isPrime(size_t n) const;
    void copyFrom(const HashTable& other);
    void moveFrom(HashTable&& other);
    void initializeBuckets();
    void destroyBuckets();
    
public:
    // Constructors and Destructor
    HashTable(size_t initial_capacity = 17);
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    ~HashTable();
    
    // Assignment operators
    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;
    
    // Element access
    Value& operator[](const Key& key);
    Value& operator[](Key&& key);
    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    
    // Modifiers
    void insert(const Key& key, const Value& value);
    void insert(Key&& key, Value&& value);
    void insert(const KeyValuePair& pair);
    void insert(KeyValuePair&& pair);
    template<typename... Args>
    void emplace(const Key& key, Args&&... args);
    template<typename... Args>
    void emplace(Key&& key, Args&&... args);
    bool remove(const Key& key);
    void clear();
    void swap(HashTable& other);
    
    // Lookup operations
    bool contains(const Key& key) const;
    Value* find(const Key& key);
    const Value* find(const Key& key) const;
    
    // Capacity
    size_t getSize() const;
    bool empty() const;
    size_t getBucketCount() const;
    double getLoadFactor() const;
    size_t getCollisionCount() const;
    
    // Hash table operations
    void rehashToSize(size_t new_size);
    void reserve(size_t min_capacity);
    
    // Iterator class
    class Iterator {
    private:
        KeyValuePair* buckets;
        size_t bucket_count;
        size_t current_index;
        
        void findNextValid();
        
    public:
        Iterator();
        Iterator(KeyValuePair* buckets, size_t bucket_count, size_t start_index);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        KeyValuePair& operator*();
        const KeyValuePair& operator*() const;
        KeyValuePair* operator->();
        const KeyValuePair* operator->() const;
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
