#include "dijkstra.h"
#include "graph.h"

#include <queue>
#ifdef DEBUG
#include <cstdio>
#endif

const int64_t INF = INT64_C(1) << 61;

DijkstraOutput::DijkstraOutput(std::vector<int64_t>&& distances,
                               std::vector<std::vector<int>>&& children)
  : distances(std::move(distances)), children(std::move(children))
{
}

const int voidParent = -1;

struct VertexDistance
{
  int vertex;
  int64_t distance;

  bool operator<(const VertexDistance& o) const;
};

bool
VertexDistance::operator<(const VertexDistance& o) const
{
  //              v-- priority queue is max
  return distance > o.distance || (distance == o.distance && vertex < o.vertex);
}

// TODO: visited mark
DijkstraOutput
dijkstra(const Graph<WeightedEdge>& graph, const int start)
{
  #ifdef DEBUG
  fprintf(stderr, "Started Dijkstra from %d.\n", start);
  #endif
  const int vertexCnt = graph.vertexCnt;
  std::vector<int64_t> distances(vertexCnt, INF);
  std::vector<int> parents(vertexCnt, voidParent);
  std::priority_queue<VertexDistance> Q;
  const int64_t initialDistance = 0;
  distances[start] = initialDistance;
  parents[start] = voidParent;
  Q.push({start, initialDistance});

  while (!Q.empty()) {
    const VertexDistance cur = Q.top();
    Q.pop();
    const int curV = cur.vertex;
    const int64_t curD = cur.distance;
    for (const WeightedEdge& e : graph[curV]) {
      const int neighbor = e.to;
      const int64_t newDistance = curD + e.weight;
      if (distances[neighbor] > newDistance) {
        distances[neighbor] = newDistance;
        parents[neighbor] = curV;
        Q.push({neighbor, newDistance});
      }
    }
  }

  std::vector<std::vector<int>> children(vertexCnt);
  for (int u = 0; u < vertexCnt; ++u) {
    const int p = parents[u];
    if (voidParent == p) {
      continue;
    }

    children[p].push_back(u);
  }

  #ifdef DEBUG
  fprintf(stderr, "Finished Dijkstra from %d.\n", start);
  #endif
  return DijkstraOutput(std::move(distances), std::move(children));
}
