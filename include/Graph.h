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
#include <iostream>
#include <sstream>
#include <memory>

template <class VertexInfo, class EdgeInfo> class Edge;
template <class VertexInfo, class EdgeInfo, class VertexInfoHash> class Graph;
template <class VertexInfo, class EdgeInfo> class Vertex;
template <class VertexInfo, class EdgeInfo, class VertexInfoHash> struct VertexHash;

template <class VertexInfo, class EdgeInfo>
using VertexRef = std::weak_ptr<Vertex<VertexInfo, EdgeInfo>>;
template <class VertexInfo, class EdgeInfo, class VertexInfoHash>
using VertexSet = std::unordered_set<
    std::shared_ptr<Vertex<VertexInfo, EdgeInfo>>,
    VertexHash<VertexInfo, EdgeInfo, VertexInfoHash>,
    VertexHash<VertexInfo, EdgeInfo, VertexInfoHash>
>;

template <class VertexInfo, class EdgeInfo>
class Vertex {
  public:
    explicit Vertex(const VertexInfo &info);

    const VertexInfo &getInfo() const;
    void setInfo(const VertexInfo &info);
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
    const std::vector<Edge<VertexInfo, EdgeInfo>> &getAdj() const;
    void addEdge(VertexRef<VertexInfo, EdgeInfo> dest, const EdgeInfo &info);

  private:
    VertexInfo info_;
    std::vector<Edge<VertexInfo, EdgeInfo>> adj_;
    bool visited_;
    bool processing_;
    int indegree_;
    int num_;
    int low_;
};


template<class VertexInfo, class EdgeInfo, class VertexInfoHash>
struct VertexHash {
  int operator()(const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v) const;
  bool operator()(
      const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v1,
      const std::shared_ptr<Vertex<VertexInfo, EdgeInfo>> &v2
  ) const;
};


template <class VertexInfo, class EdgeInfo>
class Edge {
  public:
    Edge(VertexRef<VertexInfo, EdgeInfo> dest, const EdgeInfo &info);
    VertexRef<VertexInfo, EdgeInfo> getDest() const;
    void setDest(VertexRef<VertexInfo, EdgeInfo> dest);
    const EdgeInfo& getInfo() const;
    void setInfo(const EdgeInfo &info);

  private:
    VertexRef<VertexInfo, EdgeInfo> dest_;
    EdgeInfo info_;
};


template <class VertexInfo, class EdgeInfo, class VertexInfoHash>
class Graph {
  public:
    Graph();

    const VertexSet<VertexInfo, EdgeInfo, VertexInfoHash> &getVertexSet() const;
    VertexRef<VertexInfo, EdgeInfo> findVertex(const VertexInfo &info) const;
    bool addVertex(const VertexInfo &info);
    bool addEdge(const VertexInfo &src, const VertexInfo &dest, const EdgeInfo &info);

  private:
    VertexSet<VertexInfo, EdgeInfo, VertexInfoHash> vertexSet_;
};


template<class VertexInfo, class EdgeInfo>
Vertex<VertexInfo, EdgeInfo>::Vertex(const VertexInfo &info): info_(info), adj_(),
    visited_(false), processing_(false), indegree_(0), num_(0), low_(0) {}

template<class VertexInfo, class EdgeInfo>
const VertexInfo &Vertex<VertexInfo, EdgeInfo>::getInfo() const {
    return info_;
}

template<class VertexInfo, class EdgeInfo>
void Vertex<VertexInfo, EdgeInfo>::setInfo(const VertexInfo &info) {
    info_ = info;
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
void Edge<VertexInfo, EdgeInfo>::setDest(VertexRef<VertexInfo, EdgeInfo> dest) {
    dest_ = dest;
}

template<class VertexInfo, class EdgeInfo>
const EdgeInfo &Edge<VertexInfo, EdgeInfo>::getInfo() const {
    return info_;
}

template<class VertexInfo, class EdgeInfo>
void Edge<VertexInfo, EdgeInfo>::setInfo(const EdgeInfo &info) {
    info_ = info;
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
    return vertexSet_.insert(std::make_shared<Vertex<VertexInfo, EdgeInfo>>(Vertex<VertexInfo, EdgeInfo>(info)))
        .second;
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
