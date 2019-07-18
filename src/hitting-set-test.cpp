#include "graph.h"
#include "hitting-set.h"

#include <iostream>

int
main(int argc, char* argv[])
{
  Graph G(9);
  const auto addEdge =
    [&G](int u, int v)
    {
      G[u].push_back({v, 0});
      G[v].push_back({u, 0});
    };
  addEdge(0, 5);
  addEdge(1, 5);
  addEdge(1, 6);
  addEdge(1, 7);
  addEdge(2, 5);
  addEdge(3, 7);
  addEdge(4, 7);
  addEdge(4, 8);
  std::vector<int> HS = approximateHittingSet(5, G);
  std::cerr << HS.size() << std::endl;
  for (const int x : HS) {
    std::cerr << x << ' ';
  }
  std::cerr << std::endl;

  return 0;
}
