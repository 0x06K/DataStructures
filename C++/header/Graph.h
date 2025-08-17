//==================== GRAPH (ADJACENCY LIST) ====================
#ifndef GRAPH_H
#define GRAPH_H

template<typename T>
class Graph {
private:
    struct Edge {
        T destination;
        double weight;
        Edge* next;
        
        // Edge constructors to implement
        Edge();
        Edge(const T& dest);
        Edge(const T& dest, double w);
        Edge(T&& dest);
        Edge(T&& dest, double w);
        Edge(const Edge& other);
        Edge(Edge&& other) noexcept;
        Edge& operator=(const Edge& other);
        Edge& operator=(Edge&& other) noexcept;
        ~Edge();
    };
    
    struct Vertex {
        T data;
        Edge* edge_list;
        bool visited;
        double distance;
        T predecessor;
        int discovery_time;
        int finish_time;
        
        // Vertex constructors to implement
        Vertex();
        Vertex(const T& value);
        Vertex(T&& value);
        Vertex(const Vertex& other);
        Vertex(Vertex&& other) noexcept;
        Vertex& operator=(const Vertex& other);
        Vertex& operator=(Vertex&& other) noexcept;
        ~Vertex();
    };
    
    Vertex* vertices;
    size_t vertex_count;
    size_t vertex_capacity;
    size_t edge_count;
    bool is_directed;
    bool is_weighted;
    
    // Private helper functions to implement
    void reallocateVertices(size_t new_capacity);
    size_t findVertexIndex(const T& vertex) const;
    Vertex* findVertex(const T& vertex);
    const Vertex* findVertex(const T& vertex) const;
    Edge* createEdge(const T& dest);
    Edge* createEdge(const T& dest, double weight);
    Edge* createEdge(T&& dest);
    Edge* createEdge(T&& dest, double weight);
    void destroyEdge(Edge* edge);
    void destroyEdgeList(Edge* edge_list);
    Edge* findEdge(Vertex* vertex, const T& destination);
    const Edge* findEdge(const Vertex* vertex, const T& destination) const;
    void addEdgeToVertex(Vertex* vertex, Edge* edge);
    bool removeEdgeFromVertex(Vertex* vertex, const T& destination);
    void copyEdgeList(Edge* source, Edge*& destination);
    void copyFrom(const Graph& other);
    void moveFrom(Graph&& other);
    void initializeVertices();
    void destroyVertices();
    void resetVertexStates();
    
    // Algorithm helpers to implement
    void dfsHelper(const T& vertex, void (*visit)(const T&));
    void dfsHelperRecursive(size_t vertex_index, void (*visit)(const T&), int& time);
    void bfsHelper(const T& vertex, void (*visit)(const T&));
    bool hasPathHelper(const T& source, const T& destination);
    void dijkstraHelper(const T& source);
    void bellmanFordHelper(const T& source);
    void floydWarshallHelper();
    bool topologicalSortHelper(T* result);
    void stronglyConnectedComponentsHelper();
    double primMSTHelper();
    double kruskalMSTHelper();
    
public:
    // Constructors and Destructor
    Graph(bool directed = false, bool weighted = false);
    Graph(size_t initial_capacity, bool directed = false, bool weighted = false);
    Graph(const Graph& other);
    Graph(Graph&& other) noexcept;
    ~Graph();
    
    // Assignment operators
    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other) noexcept;
    
    // Vertex operations
    void addVertex(const T& vertex);
    void addVertex(T&& vertex);
    bool removeVertex(const T& vertex);
    bool hasVertex(const T& vertex) const;
    size_t getVertexCount() const;
    T* getVertices() const;
    size_t getVertexDegree(const T& vertex) const;
    size_t getInDegree(const T& vertex) const;
    size_t getOutDegree(const T& vertex) const;
    
    // Edge operations
    void addEdge(const T& source, const T& destination);
    void addEdge(const T& source, const T& destination, double weight);
    void addEdge(T&& source, T&& destination);
    void addEdge(T&& source, T&& destination, double weight);
    bool removeEdge(const T& source, const T& destination);
    bool hasEdge(const T& source, const T& destination) const;
    double getEdgeWeight(const T& source, const T& destination) const;
    void setEdgeWeight(const T& source, const T& destination, double weight);
    size_t getEdgeCount() const;
    
    // Graph properties
    bool isDirected() const;
    bool isWeighted() const;
    bool isEmpty() const;
    void clear();
    void swap(Graph& other);
    
    // Neighbor operations
    T* getNeighbors(const T& vertex, size_t& neighbor_count) const;
    T* getInNeighbors(const T& vertex, size_t& neighbor_count) const;
    T* getOutNeighbors(const T& vertex, size_t& neighbor_count) const;
    
    // Graph algorithms - Traversals
    void depthFirstSearch(const T& start_vertex, void (*visit)(const T&));
    void breadthFirstSearch(const T& start_vertex, void (*visit)(const T&));
    void depthFirstTraversal(void (*visit)(const T&));
    void breadthFirstTraversal(void (*visit)(const T&));
    
    // Graph algorithms - Path finding
    bool hasPath(const T& source, const T& destination);
    T* shortestPath(const T& source, const T& destination, size_t& path_length);
    double shortestPathDistance(const T& source, const T& destination);
    T* longestPath(const T& source, const T& destination, size_t& path_length);
    T** allShortestPaths(double**& distances);
    
    // Graph algorithms - Shortest path algorithms
    void dijkstra(const T& source, double*& distances, T*& predecessors);
    bool bellmanFord(const T& source, double*& distances, T*& predecessors);
    void floydWarshall(double**& distances, T**& predecessors);
    
    // Graph algorithms - Connectivity
    bool isConnected();
    bool isStronglyConnected();
    size_t countConnectedComponents();
    T** getConnectedComponents(size_t*& component_sizes, size_t& component_count);
    T** getStronglyConnectedComponents(size_t*& component_sizes, size_t& component_count);
    
    // Graph algorithms - Cycle detection
    bool hasCycle();
    T* findCycle(size_t& cycle_length);
    
    // Graph algorithms - Topological sorting
    bool isDAG();
    T* topologicalSort(size_t& sorted_count);
    T** allTopologicalSorts(size_t& sort_count);
    
    // Graph algorithms - Minimum spanning tree
    double minimumSpanningTreePrim(Edge**& mst_edges, size_t& edge_count);
    double minimumSpanningTreeKruskal(Edge**& mst_edges, size_t& edge_count);
    
    // Graph algorithms - Special properties
    bool isBipartite();
    T** getBipartitePartitions(size_t*& partition_sizes);
    bool isPlanar();
    int chromaticNumber();
    T* graphColoring(int*& colors);
    
    // Vertex Iterator class
    class VertexIterator {
    private:
        Vertex* vertices;
        size_t vertex_count;
        size_t current_index;
        
    public:
        VertexIterator();
        VertexIterator(Vertex* v, size_t count, size_t index);
        VertexIterator(const VertexIterator& other);
        VertexIterator& operator=(const VertexIterator& other);
        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* operator->() const;
        VertexIterator& operator++();
        VertexIterator operator++(int);
        bool operator==(const VertexIterator& other) const;
        bool operator!=(const VertexIterator& other) const;
    };
    
    // Edge Iterator class
    class EdgeIterator {
    private:
        Vertex* vertices;
        size_t vertex_count;
        size_t current_vertex;
        Edge* current_edge;
        
        void findNextEdge();
        
    public:
        EdgeIterator();
        EdgeIterator(Vertex* v, size_t count, size_t vertex_idx, Edge* edge);
        EdgeIterator(const EdgeIterator& other);
        EdgeIterator& operator=(const EdgeIterator& other);
        Edge& operator*();
        const Edge& operator*() const;
        Edge* operator->();
        const Edge* operator->() const;
        EdgeIterator& operator++();
        EdgeIterator operator++(int);
        bool operator==(const EdgeIterator& other) const;
        bool operator!=(const EdgeIterator& other) const;
    };
    
    // Iterator functions
    VertexIterator begin();
    VertexIterator end();
    const VertexIterator begin() const;
    const VertexIterator end() const;
    EdgeIterator edgeBegin();
    EdgeIterator edgeEnd();
    const EdgeIterator edgeBegin() const;
    const EdgeIterator edgeEnd() const;
};

#endif
