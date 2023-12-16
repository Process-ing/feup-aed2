/**
 * Header file for class Graph.
 */

#ifndef FEUP_AED2_GRAPH_H
#define FEUP_AED2_GRAPH_H

#include <vector>
#include <unordered_set>

template <class T, class U> class Edge;
template <class T, class THash, class U> class Graph;
template <class T, class U> class Vertex;

template <class T, class THash, class U> struct VTHash;
template <class T, class THash, class U>
using VertexSet = std::unordered_set<Vertex<T, U>*, VTHash<T, THash, U>, VTHash<T, THash, U>>;

template <class T, class U>
class Vertex {
  public:
    explicit Vertex(const T &info);

    const T &getInfo() const;
    void setInfo(const T &info);
    bool isVisited() const;
    void setVisited(bool visited);
    bool isProcessing() const;
    void setProcessing(bool processing);
    int getIndegree() const;
    void setIndegree(int indegree);
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
    const std::vector<T, U> &getAdj() const;

    friend class Graph<T, class THash, U>;

  private:
    T info_;
    std::vector<Vertex<T, U>*> adj_;
    bool visited_;
    bool processing_;
    int indegree_;
    int num_;
    int low_;

    void addEdge(Vertex<T, U> *dest, const U &info);
    bool removeEdgeTo(const T &dest);
};


template<class T, class THash, class U>
struct VTHash {
  int operator()(const Vertex<T, U>& v);
  bool operator()(const Vertex<T, U>& v1, const Vertex<T, U>& v2);
};


template <class T, class U>
class Edge {
  public:
    Edge(Vertex<T, U> *dest, const U &info);
    Vertex<T, U> *getDest() const;
    void setDest(Vertex<T, U> *dest);
    const U& getInfo() const;
    void setInfo(const U &info);

  private:
    Vertex<T, U> *dest_;
    U info_;
};


template <class T, class THash, class U>
class Graph {
  public:
    Graph();

    const VertexSet<T, THash, U> &getVertexSet() const;
    Vertex<T, U> *findVertex(const T &info) const;
    bool addVertex(const T &info);
    bool removeVertex(const T &info);
    bool addEdge(const T &src, const T &dest, const U &info);
    bool removeEdge(const T &src, const T &dest);

private:
    VertexSet<T, THash, U> vertexSet_;
};


template<class T, class U>
Vertex<T, U>::Vertex(const T &info): info_(info), adj_(),
    visited_(false), processing_(false), indegree_(0), num_(0), low_(0) {}

template<class T, class U>
const T &Vertex<T, U>::getInfo() const {
    return info_;
}

template<class T, class U>
void Vertex<T, U>::setInfo(const T &info) {
    info_ = info;
}

template<class T, class U>
void Vertex<T, U>::addEdge(Vertex<T, U> *dest, const U &info) {
    adj_.emplace_back(dest, info);
}

template<class T, class U>
bool Vertex<T, U>::removeEdgeTo(const T &dest) {
    for (auto it = adj_.begin(); it != adj_.end(); it++) {
        if (it->getDest().getInfo() == dest) {
            adj_.erase(it);
            return true;
        }
    }
    return false;
}


template<class T, class U>
bool Vertex<T, U>::isVisited() const {
    return visited_;
}

template<class T, class U>
void Vertex<T, U>::setVisited(bool visited) {
    visited_ = visited;
}

template<class T, class U>
bool Vertex<T, U>::isProcessing() const {
    return processing_;
}

template<class T, class U>
void Vertex<T, U>::setProcessing(bool processing) {
    processing_ = processing;
}

template<class T, class U>
int Vertex<T, U>::getIndegree() const {
    return indegree_;
}

template<class T, class U>
void Vertex<T, U>::setIndegree(int indegree) {
    indegree_ = indegree;
}

template<class T, class U>
int Vertex<T, U>::getNum() const {
    return num_;
}

template<class T, class U>
void Vertex<T, U>::setNum(int num) {
    num_ = num;
}

template<class T, class U>
int Vertex<T, U>::getLow() const {
    return low_;
}

template<class T, class U>
void Vertex<T, U>::setLow(int low) {
    low_ = low;
}

template<class T, class U>
const std::vector<T, U> &Vertex<T, U>::getAdj() const {
    return adj_;
}


template<class T, class U>
Edge<T, U>::Edge(Vertex<T, U> *dest, const U &info): dest_(dest), info_(info) {}

template<class T, class U>
Vertex<T, U> *Edge<T, U>::getDest() const {
    return dest_;
}

template<class T, class U>
void Edge<T, U>::setDest(Vertex<T, U> *dest) {
    dest_ = dest;
}

template<class T, class U>
const U &Edge<T, U>::getInfo() const {
    return info_;
}

template<class T, class U>
void Edge<T, U>::setInfo(const U &info) {
    info_ = info;
}


template<class T, class THash, class U>
Graph<T, THash, U>::Graph() = default;

template<class T, class THash, class U>
const VertexSet<T, THash, U> &Graph<T, THash, U>::getVertexSet() const {
    return vertexSet_;
}

template<class T, class THash, class U>
Vertex<T, U> *Graph<T, THash, U>::findVertex(const T &info) const {
    auto found = vertexSet_.find(Vertex<T, U>(info));
    return found != vertexSet_.begin() ? *found : nullptr;
}

template<class T, class THash, class U>
bool Graph<T, THash, U>::addVertex(const T &info) {
    return vertexSet_.insert(Vertex<T, U>(info)).second;
}

template<class T, class THash, class U>
bool Graph<T, THash, U>::removeVertex(const T &info) {
    return vertexSet_.erase(Vertex<T, U>(info)) == 1;
}

template<class T, class THash, class U>
bool Graph<T, THash, U>::addEdge(const T &src, const T &dest, const U &info) {
    auto v1 = findVertex(src);
    auto v2 = findVertex(dest);
    if (!v1 || !v2)
        return false;
    v1->addEdge(v2, info);
    return true;
}

template<class T, class THash, class U>
bool Graph<T, THash, U>::removeEdge(const T &src, const T &dest) {
    auto v1 = findVertex(src);
    if (!v1)
        return false;
    return v1->removeEdgeTo(dest);
}


template<class T, class THash, class U>
int VTHash<T, THash, U>::operator()(const Vertex<T, U> &v) {
    return THash()(v.getInfo());
}

template<class T, class THash, class U>
bool VTHash<T, THash, U>::operator()(const Vertex<T, U> &v1, const Vertex<T, U> &v2) {
    return THash()(v1.getInfo(), v2.getInfo());
}

#endif //FEUP_AED2_GRAPH_H
