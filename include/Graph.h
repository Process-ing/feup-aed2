/**
 * @file
 * Header file for class Graph.
 */

#ifndef FEUP_AED2_GRAPH_H
#define FEUP_AED2_GRAPH_H

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <memory>

template <class VertexInfo, class EdgeInfo> class Edge;
template <class VertexInfo, class EdgeInfo, class VertexInfoHash> class Graph;
template <class VertexInfo, class EdgeInfo> class Vertex;
template <class VertexInfo, class EdgeInfo, class VertexInfoHash> struct VertexHash;

/**
 * @brief Reference to a vertex.
 * @tparam VertexInfo Type of the vertex's info.
 * @tparam EdgeInfo Type of the edge's info.
 */
template <class VertexInfo, class EdgeInfo>
using VertexRef = std::weak_ptr<Vertex<VertexInfo, EdgeInfo>>;
/**
 * @brief Hash table for for storing vertexes, used by the Graph class.
 * @tparam VertexInfo Type of the vertex's info.
 * @tparam EdgeInfo Type of the edge's info.
 * @tparam VertexInfoHash Hash class for VertexInfo.
 */
template <class VertexInfo, class EdgeInfo, class VertexInfoHash>
using VertexSet = std::unordered_set<
    std::shared_ptr<Vertex<VertexInfo, EdgeInfo>>,
    VertexHash<VertexInfo, EdgeInfo, VertexInfoHash>,
    VertexHash<VertexInfo, EdgeInfo, VertexInfoHash>
>;

/**
 * @brief Vertex of a graph, containing some info.
 * @tparam VertexInfo Type of the vertex's info.
 * @tparam EdgeInfo Type of the edge's info.
 */
template <class VertexInfo, class EdgeInfo>
class Vertex {
  public:
    /**
     * @brief Constructs a Vertex object
     * @param info Vertex's info
     */
    explicit Vertex(const VertexInfo &info);

    /**
     * @brief Returns the vertex's info.
     * @return Vertex's info
     */
    const VertexInfo &getInfo() const;

    /**
     * @brief Returns if the vertex was visited or not (auxiliary flag in algorithms).
     * @return Whether the vertex was visited or not
     */
    bool isVisited() const;

    /**
     * @brief Sets if the vertex was visited or not.
     * @param visited Whether the vertex was visited or not
     */
    void setVisited(bool visited);

    /**
     * @brief Returns if the vertex is being processed or not (auxiliary flag in algorithms).
     * @return Whether the vertex is being processed or not
     */
    bool isProcessing() const;

    /**
     * @brief Sets if the vertex is being processed or not.
     * @param processing Whether the vertex is being processed or not
     */
    void setProcessing(bool processing);

    /**
     * @brief Returns the in degree of the vertex (number of incoming edges).
     * @return In degree
     */
    int getIndegree() const;

    /**
     * @brief Sets the in degree.
     * @param indegree Vertex's in degree
     */
    void setIndegree(int indegree);

    /**
     * @brief Returns the vertex's depth (distance to the root, auxiliary value in algorithms).
     * @return Vertex's depth
     */
    int getDepth() const;

    /**
     * @brief Sets the vertex's depth.
     * @param distance Vertex's depth
     */
    void setDepth(int distance);

    /**
     * @brief Returns the vertex's num value (auxiliary value in Tarjan's algorithms).
     * @return Num value
     */
    int getNum() const;

    /**
     * @brief Set the vertex's num value.
     * @param num New num value
     */
    void setNum(int num);

    /**
     * @brief Returns the vertex's low value (auxiliary value in Tarjan's algorithms).
     * @return Low value
     */
    int getLow() const;

    /**
     * @brief Sets the vertex's low value.
     * @param low New low value
     */
    void setLow(int low);

    /**
     * @brief Returns the parent node (auxiliary in best flight's algorithm).
     * @return Reference to parent
     */
    VertexRef<VertexInfo, EdgeInfo> getParent();

    /**
     * @brief Sets the parent node.
     * @param parent Reference to the parent.
     */
    void setParent(VertexRef<VertexInfo, EdgeInfo> parent);

    /**
     * @brief Returns all the outgoing edges of the vertex.
     * @return Vector of outgoing edges.
     */
    const std::vector<Edge<VertexInfo, EdgeInfo>> &getAdj() const;

    /**
     * @brief Add an outgoing edge to the vertex.
     * Complexity: O(1)
     * @param dest Edge's destination
     * @param info Edge's info
     */
    void addEdge(VertexRef<VertexInfo, EdgeInfo> dest, const EdgeInfo &info);

  private:
    VertexInfo info_;
    std::vector<Edge<VertexInfo, EdgeInfo>> adj_;
    bool visited_;
    bool processing_;
    int indegree_;
    int depth_;
    int num_;
    int low_;
    VertexRef<VertexInfo, EdgeInfo> parent_;
};

/**
 * @brief Hash class for a graph's vertex, based on VertexInfoHash.
 * @tparam VertexInfo Type of the vertex's info.
 * @tparam EdgeInfo Type of the edge's info.
 * @tparam VertexInfoHash Hash class for VertexInfo.
 */
template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
struct VertexHash {
    /**
     * @brief Returns the hashcode of a vertex, based on its info.
     * @param v Vertex
     * @return Vertex's hashcode
     */
    int operator()(const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v) const;

    /**
     * @brief Returns if two vertex's are the same, based on their infos.
     * @param v1 One vertex
     * @param v2 Other vertex
     * @return True if they are the same, false otherwise
     */
    bool operator()(
      const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v1,
      const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v2
    ) const;
};

/**
 * @brief Edge of a graph, containing some info.
 * @tparam VertexInfo Type of the vertex's info.
 * @tparam EdgeInfo Type of the edge's info.
 */
template <class VertexInfo, class EdgeInfo>
class Edge {
  public:
    /**
     * @brief Constructs an edge object.
     * @param dest Reference to the edge's destination vertex
     * @param info Edge's info
     */
    Edge(VertexRef<VertexInfo, EdgeInfo> dest, const EdgeInfo &info);

    /**
     * @brief Returns the edge's destination.
     * @return Reference to the edge's destination.
     */
    VertexRef<VertexInfo, EdgeInfo> getDest() const;

    /**
     * @brief Returns the edge's info.
     * @return Edge's info
     */
    const EdgeInfo& getInfo() const;

  private:
    VertexRef<VertexInfo, EdgeInfo> dest_;
    EdgeInfo info_;
};

/**
 * @brief Graph class, with the structure of a CRUD graph.
 * The class stores the vertexes in a hash table to allow constant time access to its vertices (see VertexSet).
 *
 * @tparam VertexInfo Type of the vertex's info.
 * @tparam EdgeInfo Type of the edge's info.
 * @tparam VertexInfoHash Hash class for VertexInfo.
 */
template <class VertexInfo, class EdgeInfo, class VertexInfoHash>
class Graph {
  public:
    /**
     * @brief Constructs an empty Graph object.
     */
    Graph();

    /**
     * @brief Returns the vertexes of the graph.
     * @return Set of the graph's vertexes
     */
    const VertexSet<VertexInfo, EdgeInfo, VertexInfoHash> &getVertexSet() const;

    /**
     * @brief Returns the vertex with the given info.
     * Complexity: O(1)
     * @param info Vertex's info
     * @return Reference to the respective vertex
     */
    VertexRef<VertexInfo, EdgeInfo> findVertex(const VertexInfo &info) const;

    /**
     * @brief Adds a vertex to the graph, with the given info.
     * Complexity: O(1)
     *
     * @param info Vertex's info
     * @return True if the graph was successfully added, false otherwise (if another vertex with the same info already
     *         exists).
     */
    bool addVertex(const VertexInfo &info);

    /**
     * @brief Adds an edge from one vertex to the other, with the respective info.
     * This function also updates the vertexes in degree appropriately.
     * Complexity: O(1)
     *
     * @param src Source vertex's info
     * @param dest Destination vertex's info
     * @param info Edge's info
     * @return True if the edge was successfully added, false otherwise (if at least one of the vertexes does not
 *             exist).
     */
    bool addEdge(const VertexInfo &src, const VertexInfo &dest, const EdgeInfo &info);

  private:
    VertexSet<VertexInfo, EdgeInfo, VertexInfoHash> vertexSet_;
};


template<class VertexInfo, class EdgeInfo>
Vertex<VertexInfo, EdgeInfo>::Vertex(const VertexInfo &info): info_(info), adj_(),
                                                              visited_(false), processing_(false), indegree_(0), num_(0), low_(0), depth_(0) {}

template<class VertexInfo, class EdgeInfo>
const VertexInfo &Vertex<VertexInfo, EdgeInfo>::getInfo() const {
    return info_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::addEdge(VertexRef<VertexInfo, EdgeInfo> dest, const EdgeInfo &info) {
    adj_.emplace_back(dest, info);
}


template<class VertexInfo, class EdgeInfo>
bool Vertex<VertexInfo, EdgeInfo>::isVisited() const {
    return visited_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::setVisited(bool visited) {
    visited_ = visited;
}

template<class VertexInfo, class EdgeInfo>
bool Vertex<VertexInfo, EdgeInfo>::isProcessing() const {
    return processing_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::setProcessing(bool processing) {
    processing_ = processing;
}

template<class VertexInfo, class EdgeInfo>
int Vertex<VertexInfo, EdgeInfo>::getIndegree() const {
    return indegree_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::setIndegree(int indegree) {
    indegree_ = indegree;
}

template<class VertexInfo, class EdgeInfo>
int Vertex<VertexInfo, EdgeInfo>::getDepth() const {
    return depth_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::setDepth(int distance) {
    depth_ = distance;
}

template<class VertexInfo, class EdgeInfo>
int Vertex<VertexInfo, EdgeInfo>::getNum() const {
    return num_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::setNum(int num) {
    num_ = num;
}

template<class VertexInfo, class EdgeInfo>
int Vertex<VertexInfo, EdgeInfo>::getLow() const {
    return low_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::setLow(int low) {
    low_ = low;
}

template<class VertexInfo, class EdgeInfo>
VertexRef<VertexInfo, EdgeInfo> Vertex<VertexInfo, EdgeInfo>::getParent() {
    return parent_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::setParent(VertexRef<VertexInfo, EdgeInfo> parent) {
    parent_ = parent;
}

template<class VertexInfo, class EdgeInfo>
const std::vector<Edge<VertexInfo, EdgeInfo>> &Vertex<VertexInfo, EdgeInfo>::getAdj() const {
    return adj_;
}


template<class VertexInfo, class EdgeInfo>
Edge<VertexInfo, EdgeInfo>::Edge(VertexRef<VertexInfo, EdgeInfo> dest, const EdgeInfo &info)
    : dest_(dest), info_(info) {}

template<class VertexInfo, class EdgeInfo>
VertexRef<VertexInfo, EdgeInfo> Edge<VertexInfo, EdgeInfo>::getDest() const {
    return dest_;
}
template<class VertexInfo, class EdgeInfo>
const EdgeInfo &Edge<VertexInfo, EdgeInfo>::getInfo() const {
    return info_;
}


template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
Graph<VertexInfo, EdgeInfo, VertexInfoHash>::Graph() = default;

template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
const VertexSet<VertexInfo, EdgeInfo, VertexInfoHash> &Graph<VertexInfo, EdgeInfo, VertexInfoHash>::getVertexSet() const {
    return vertexSet_;
}

template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
VertexRef<VertexInfo, EdgeInfo> Graph<VertexInfo, EdgeInfo, VertexInfoHash>::findVertex(const VertexInfo &info) const {
    auto found = vertexSet_.find(std::make_shared<Vertex<VertexInfo, EdgeInfo>>(Vertex<VertexInfo, EdgeInfo>(info)));
    return found != vertexSet_.end() ? *found : VertexRef<VertexInfo, EdgeInfo>();
}

template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
bool Graph<VertexInfo, EdgeInfo, VertexInfoHash>::addVertex(const VertexInfo &info) {
    return vertexSet_.insert(std::make_shared<Vertex<VertexInfo, EdgeInfo>>(Vertex<VertexInfo, EdgeInfo>(info))).second;
}

template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
bool Graph<VertexInfo, EdgeInfo, VertexInfoHash>::addEdge(
    const VertexInfo &src, const VertexInfo &dest, const EdgeInfo &info) {
    auto v1 = findVertex(src);
    auto v2 = findVertex(dest);
    if (!v1.lock() || !v2.lock())
        return false;

    v1.lock()->addEdge(v2.lock(), info);
    v2.lock()->setIndegree(v2.lock()->getIndegree() + 1);
    return true;
}


template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
int VertexHash<VertexInfo, EdgeInfo, VertexInfoHash>
    ::operator()(const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v) const {
    return VertexInfoHash()(v->getInfo());
}

template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
bool VertexHash<VertexInfo, EdgeInfo, VertexInfoHash>::operator()(
    const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v1,
    const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v2
) const {
    return VertexInfoHash()(v1->getInfo(), v2->getInfo());
}

#endif //FEUP_AED2_GRAPH_H
