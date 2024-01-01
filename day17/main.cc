#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>
#include <queue>
#include <map>
#include <set>

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
  Node *prev;

  Node(int r, int c, char dir, short t, int val, Node *prevNode = nullptr)
      : row(r), col(c), direction(dir), times(t), value(val), prev(prevNode)
  {
  }

  bool operator<(const Node &other) const
  {
    return value > other.value;
  }

  vector<Node> Next(int v)
  {
    vector<Node> vn;
    // left
    if (direction == '<')
    {
      if (times < 3 && direction != '>')
      {
        vn.push_back(Node(row, col - 1, '<', times + 1, value + v, this));
      }
    }
    else
    {
      if (direction != '>')
      {
        vn.push_back(Node(row, col - 1, '<', 1, value + v, this));
      }
    }

    // right
    if (direction == '>')
    {
      if (times < 3 && direction != '<')
      {
        vn.push_back(Node(row, col + 1, '>', times + 1, value + v, this));
      }
    }
    else
    {
      if (direction != '<')
      {
        vn.push_back(Node(row, col + 1, '>', 1, value + v, this));
      }
    }

    // bottom
    if (direction == 'v')
    {
      if (times < 3 && direction != '^')
      {
        vn.push_back(Node(row + 1, col, 'v', times + 1, value + v, this));
      }
    }
    else
    {
      if (direction != '^')
      {
        vn.push_back(Node(row + 1, col, 'v', 1, value + v, this));
      }
    }

    // top
    if (direction == '^')
    {
      if (times < 3 && direction != 'v')
      {
        vn.push_back(Node(row - 1, col, '^', times + 1, value + v, this));
      }
    }
    else
    {
      if (direction != 'v')
      {
        vn.push_back(Node(row - 1, col, '^', 1, value + v, this));
      }
    }

    return vn;
  }

  string Display()
  {
    std::stringstream ss;
    ss << "col: " << col << " row: " << row << " direction: " << direction << " times: " << times << " value: " << value;
    return ss.str();
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
  set<tuple<int, int, int>> vis;
  Node n(0, 0, '>', 1, 0);
  Node *current = nullptr;
  minHeap.push(Node(0, 0, '>', 1, 0));
  minHeap.push(Node(0, 0, 'v', 1, 0));
  while (!minHeap.empty())
  {
    n = minHeap.top();
    minHeap.pop();
    if (n.row == max_row - 1 && n.col == max_col - 1)
    {
      current = &n;
      cout << "found.. " << n.Display() << endl;
      break;
    }

    if (vis.find({n.row, n.col, n.direction}) != vis.end() || crossed_boarder(n.row, n.col, max_row, max_col))
    {
      continue;
    };

    cout << "visiting.. " << n.Display() << endl;
    vis.insert({n.row, n.col, n.direction});

    for (Node adj : n.Next(arr[n.row][n.col]))
    {
      minHeap.push(adj);
    }
  }

  while (current != nullptr)
  {
    cout << "back tracking.. " << current->Display() << endl;
    current = current->prev;
  }

  return n.value;
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