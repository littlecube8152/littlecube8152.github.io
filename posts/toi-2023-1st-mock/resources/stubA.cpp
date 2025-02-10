/**
This is a simple wrapper for communication with the manager.
DO NOT CHANGE THIS FILE!!!!!
**/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <set>
#include <string>
#include <vector>
using namespace std;

// Functions to be implemented in the solution.
void AutographChallenge();

// Functions provided to the solution.
int Check(int k);

////////////////////////////////////////////////
namespace {  // Used in this file only.
void run();
FILE *fifo_in, *fifo_out;
void _send_msg(const string& msg);
void _send_msg(const string& msg, int k);
int _recv_int();
}  // namespace
////////////////////////////////////////////////

int main(int argc, char **argv) {

    // IF YOU WANT TO TEST LOCALLY ON YOUR COMPUTER,
    // 如果你想要在本地端測試你的程式，
    // COMMENT THESE TWO LINES AND UNCOMMENT THE TWO LINES BELOW.
    // 把下面這兩行註解起來，然後把更下面兩行打開，這樣就可以從命令列互動了。
    fifo_in = fopen(argv[1], "r");
    fifo_out = fopen(argv[2], "w");
    // fifo_in = stdin;
    // fifo_out = stdout;

    run();

    fclose(fifo_in);
    fclose(fifo_out);
    return 0;
}

////////////////////////////////////////////////
namespace {
void _send_msg(const string& msg) {
    fprintf(fifo_out, "%s\n", msg.c_str());
    fflush(fifo_out);
}

void _send_msg(const string& msg, const int k) {
    string query = msg + " " + to_string(k);
    fprintf(fifo_out, "%s\n", query.c_str());
    fflush(fifo_out);
}

int _recv_int() {
    int val;
    int ret = fscanf(fifo_in, "%d", &val);
    // Receives error.
    if (ret != 1 || val == -100) {
        fclose(fifo_in);
        fclose(fifo_out);
        exit(0);
    }
    return val;
}

void run() {
  int n = _recv_int();
  for (int i = 0; i < n; i++) {
    AutographChallenge();
    _send_msg("done");
  }
}
}  // namespace

int Check(int k) {
  _send_msg("check", k);
  return _recv_int();
}
