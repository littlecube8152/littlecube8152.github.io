/**
This is a simple wrapper.
**/

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> MakePlan(int n, vector<string> &grid);

int main() {

///////////////////////////////////////////////////
    string map_to[128];
    for (int c = 'A'; c <= 'Z'; c++)
      map_to[c] = bitset<6>(c-'A').to_string();
    for (int c = 'a'; c <= 'z'; c++)
      map_to[c] = bitset<6>(c-'a'+26).to_string();
    for (int c = '0'; c <= '9'; c++)
      map_to[c] = bitset<6>(c-'0'+52).to_string();
    map_to['+'] = bitset<6>(62).to_string();
    map_to['/'] = bitset<6>(63).to_string();
    for (int i = 0; i < 128; i++)
      reverse(map_to[i].begin(), map_to[i].end());
///////////////////////////////////////////////////

    char buf[20000];
    vector<string> grid;
    int n;
    scanf("%s", buf);
    if (buf[0] == 'B') {
      // BASE 64
      scanf("%d", &n);
      grid.reserve(n);
      for (int i = 0; i < n; i++) {
        string row = "";
        scanf("%s", buf);
        for (int j = 0; buf[j]; j++) {
          row += map_to[(int)buf[j]];
        }
        row.resize(n);
        grid.push_back(row);
      }
    } else {
      n = atoi(buf);
      grid.reserve(n);
      for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        string row(buf);
        grid.push_back(row);
      }
    }

    auto plan = MakePlan(n, grid);
    if (!plan.empty() && plan[0].first == -1) {
      puts("-1");
    } else {
      printf("%d\n", (int)plan.size());
      for (auto& it : plan) {
        printf("%d %d\n", it.first, it.second);
      }
    }
    return 0;
}
