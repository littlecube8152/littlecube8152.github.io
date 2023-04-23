/**
This is a simple wrapper.
**/

#include <bits/stdc++.h>
using namespace std;

vector<int> EggSystem(vector<int> &c, vector<int> &p, vector<vector<int>> &ops);

//////////////////////////////////////////////////////////////
namespace {
  // Fast Input: https://codeforces.com/blog/entry/8080?#comment-138205
  static char buf[1<<21];
  static char* stdinDataEnd = buf + sizeof(buf);
  static const char* stdinPos = stdinDataEnd;

  void read_ahead(size_t amount) {
    size_t remaining = stdinDataEnd - stdinPos;
    if (remaining < amount) {
      memmove(buf, stdinPos, remaining);
      size_t sz = fread(buf + remaining, 1, sizeof(buf) - remaining, stdin);
      stdinPos = buf;
      stdinDataEnd = buf + remaining + sz;
      if (stdinDataEnd != buf + sizeof(buf))
        *stdinDataEnd = 0;
    }
  }

  int read_int() {
    read_ahead(16);
    int x = 0;
    bool neg = false;
    while (*stdinPos && *stdinPos != '-' && !(*stdinPos >= '0' && *stdinPos <= '9')) ++stdinPos;
    if (*stdinPos == '-') { ++stdinPos; neg = true; }
    while (*stdinPos >= '0' && *stdinPos <= '9') {
      x *= 10;
      x += *stdinPos - '0';
      ++stdinPos;
    }
    return neg ? -x : x;
  }
  
  void output_vector(const vector<int>& a) {
    char *lptr = buf;
    for (int x: a) {
      char miniBuf[16];
      char *ptr = miniBuf;
      bool neg = false;
      if (x < 0) { x=-x; neg = true; }
      if (x == 0) { *ptr++ = '0'; }
      while (x != 0) {
        *ptr++ = x%10 + '0';
        x/=10;
      }
      if (neg) *ptr++ = '-';
      while (ptr > miniBuf) *lptr++ = *--ptr;
      *lptr++ = '\n';
    }
    *lptr = 0;
    fwrite(buf, 1, lptr - buf, stdout);
  }
}

int main() {
  int n, m, q;
  n = read_int();
  m = read_int();
  vector<int> c(n);
  vector<int> p(m);
  for (int i = 0; i < n; i++) c[i] = read_int();
  for (int i = 0; i < m; i++) p[i] = read_int();
  q = read_int();
  vector<vector<int>> ops(q, vector<int>(3));
  for (int i = 0; i < q; i++) {
    ops[i][0] = read_int();
    ops[i][1] = read_int();
    ops[i][2] = read_int();
  }
  auto result = EggSystem(c, p, ops);
  output_vector(result);
  return 0;
}
//////////////////////////////////////////////////////////////
