#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

std::vector<std::vector<std::pair<int, int>>> graph;
std::vector<bool> used;
std::vector<int> tin;
std::vector<int> dp_time;
std::vector<int> bridges;
std::map<std::pair<int, int>, int> mod_ed;
int timer = 0;

void Dfs(int now_v, int pred = -1) {
  used[now_v] = true;
  tin[now_v] = timer;
  dp_time[now_v] = timer;
  timer++;
  for (auto&& [to_v, ind] : graph[now_v]) {
    if (to_v == pred) {
      continue;
    }
    if (used[to_v]) {
      dp_time[now_v] = std::min(dp_time[now_v], tin[to_v]);
    } else {
      Dfs(to_v, now_v);
      dp_time[now_v] = std::min(dp_time[now_v], dp_time[to_v]);
      if (dp_time[to_v] > tin[now_v]) {
        if (mod_ed[{to_v, now_v}] == 1) {
          bridges.push_back(ind);
        }
      }
    }
  }
}

signed main() {
  int vertex;
  int edge;
  std::cin >> vertex >> edge;
  graph.resize(vertex);
  used.resize(vertex, false);
  tin.resize(vertex, 0);
  dp_time.resize(vertex, 0);
  for (int i = 0; i < edge; i++) {
    int fst_v;
    int sec_v;
    std::cin >> fst_v >> sec_v;
    fst_v--;
    sec_v--;
    mod_ed[{fst_v, sec_v}]++;
    mod_ed[{sec_v, fst_v}]++;
    graph[fst_v].push_back({sec_v, i});
    graph[sec_v].push_back({fst_v, i});
  }
  Dfs(0);
  sort(bridges.begin(), bridges.end());
  std::cout << (int)bridges.size() << '\n';
  for (auto& ind_ed : bridges) {
    std::cout << ind_ed + 1 << ' ';
  }
  return 0;
}
