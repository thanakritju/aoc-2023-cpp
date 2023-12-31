#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>
#include <queue>

#define VERBOSE

using namespace std;

const int rows = 141;
const int columns = 141;

struct Node
{
  int row;
  int col;
  char direction;
  short times;
  int value;

  bool operator<(const Node &other) const
  {
    return value > other.value;
  }
};

bool crossed_boarder(int row, int col, int max_row, int max_col)
{
  return row < 0 || col < 0 || row >= max_row || col >= max_col;
}

long solve(vector<string> input)
{
  short arr[rows][columns];
  int max_row = input.size();
  int max_col = input[0].size();
  for (int i = 0; i < max_row; i++)
  {
    for (int j = 0; j < max_col; j++)
    {
      arr[i][j] = input[i][j] - '0';
    }
  }

  priority_queue<Node> minHeap;
  Node n;
  n.col = 0;
  n.row = 0;
  n.direction = '>';
  n.times = 1;
  n.value = 0;
  Node n2;
  n2.col = 0;
  n2.row = 0;
  n2.direction = 'v';
  n2.times = 1;
  n2.value = 0;
  minHeap.push(n);
  minHeap.push(n2);

  return 0;
}

long solve2(vector<string> input)
{
  return 0;
}

int test()
{
  return 0;
}

int parse_and_run(string path)
{
  vector<string> data;
  ifstream file(path);
  if (!file.is_open())
  {
    cerr << "Failed to open " << path << endl;
    return 1;
  }

  vector<string> lines;
  string line;
  while (getline(file, line))
  {
    lines.push_back(line);
  }
  long ans1 = solve(lines);
  long ans2 = solve2(lines);
  cout << "--------------------------" << endl;
  cout << "The part 1 answer is " << ans1 << endl;
  cout << "The part 2 answer is " << ans2 << endl;
  cout << "--------------------------" << endl;

  return 0;
}

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    return test();
  }
  else if (argc == 2)
  {
    return parse_and_run(argv[1]);
  }
}