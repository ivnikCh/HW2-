#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> rev_graph;
std::vector<bool> used;
std::vector<int> top;
std::vector<int> color;
int now_clr = 1;

void DfsSort(int now_v) {
  used[now_v] = true;
  for (int& to_v : graph[now_v]) {
    if (!used[to_v]) {
      DfsSort(to_v);
    }
  }
  top.push_back(now_v);
}

void DfsComp(int now_v) {
  color[now_v] = now_clr;
  for (int& to_v : rev_graph[now_v]) {
    if (color[to_v] == 0) {
      DfsComp(to_v);
    }
  }
}

signed main() {
  int vertex;
  int edge;
  std::cin >> vertex >> edge;
  graph.resize(vertex);
  rev_graph.resize(vertex);
  used.resize(vertex, false);
  color.resize(vertex, 0);
  for (int i = 0; i < edge; i++) {
    int from;
    int to_v;
    std::cin >> from >> to_v;
    from--;
    to_v--;
    graph[from].push_back(to_v);
    rev_graph[to_v].push_back(from);
  }
  for (int i = 0; i < vertex; i++) {
    if (!used[i]) {
      DfsSort(i);
    }
  }
  reverse(top.begin(), top.end());
  for (int& start_v : top) {
    if (color[start_v] == 0) {
      DfsComp(start_v);
      now_clr++;
    }
  }
  std::cout << now_clr - 1 << '\n';
  for (int& it_v : color) {
    std::cout << it_v << ' ';
  }
  return 0;
}
