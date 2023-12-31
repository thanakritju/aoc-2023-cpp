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

  Node(int r, int c, char dir, short t, int val)
      : row(r), col(c), direction(dir), times(t), value(val)
  {
  }

  bool operator<(const Node &other) const
  {
    return value > other.value;
  }

  vector<Node> Next(short arr[rows][columns])
  {
    vector<Node> vn;
    // left
    if (direction == '<')
    {
      if (times < 3 && direction != '>')
      {
        vn.push_back(Node(row, col - 1, '<', times + 1, value + arr[row][col - 1]));
      }
    }
    else
    {
      if (direction != '>')
      {
        vn.push_back(Node(row, col - 1, '<', 1, value + arr[row][col - 1]));
      }
    }

    // right
    if (direction == '>')
    {
      if (times < 3 && direction != '<')
      {
        vn.push_back(Node(row, col + 1, '>', times + 1, value + arr[row][col + 1]));
      }
    }
    else
    {
      if (direction != '<')
      {
        vn.push_back(Node(row, col + 1, '>', 1, value + arr[row][col + 1]));
      }
    }

    // bottom
    if (direction == 'v')
    {
      if (times < 3 && direction != '^')
      {
        vn.push_back(Node(row + 1, col, 'v', times + 1, value + arr[row + 1][col]));
      }
    }
    else
    {
      if (direction != '^')
      {
        vn.push_back(Node(row + 1, col, 'v', 1, value + arr[row + 1][col]));
      }
    }

    // top
    if (direction == '^')
    {
      if (times < 3 && direction != 'v')
      {
        vn.push_back(Node(row - 1, col, '^', times + 1, value + arr[row - 1][col]));
      }
    }
    else
    {
      if (direction != 'v')
      {
        vn.push_back(Node(row - 1, col, '^', 1, value + arr[row - 1][col]));
      }
    }

    return vn;
  }

  vector<Node> NextV2(short arr[rows][columns])
  {
    vector<Node> vn;
    if (times < 4)
    {
      if (direction == '<')
      {
        vn.push_back(Node(row, col - 1, '<', times + 1, value + arr[row][col - 1]));
      }
      else if (direction == '>')
      {
        vn.push_back(Node(row, col + 1, '>', times + 1, value + arr[row][col + 1]));
      }
      else if (direction == 'v')
      {
        vn.push_back(Node(row + 1, col, 'v', times + 1, value + arr[row + 1][col]));
      }
      else if (direction == '^')
      {
        vn.push_back(Node(row - 1, col, '^', times + 1, value + arr[row - 1][col]));
      }
      else
      {
        throw runtime_error("Invalid direction " + direction);
      }
    }
    else
    {
      // left
      if (direction == '<')
      {
        if (times < 10 && direction != '>')
        {
          vn.push_back(Node(row, col - 1, '<', times + 1, value + arr[row][col - 1]));
        }
      }
      else
      {
        if (direction != '>')
        {
          vn.push_back(Node(row, col - 1, '<', 1, value + arr[row][col - 1]));
        }
      }

      // right
      if (direction == '>')
      {
        if (times < 10 && direction != '<')
        {
          vn.push_back(Node(row, col + 1, '>', times + 1, value + arr[row][col + 1]));
        }
      }
      else
      {
        if (direction != '<')
        {
          vn.push_back(Node(row, col + 1, '>', 1, value + arr[row][col + 1]));
        }
      }

      // bottom
      if (direction == 'v')
      {
        if (times < 10 && direction != '^')
        {
          vn.push_back(Node(row + 1, col, 'v', times + 1, value + arr[row + 1][col]));
        }
      }
      else
      {
        if (direction != '^')
        {
          vn.push_back(Node(row + 1, col, 'v', 1, value + arr[row + 1][col]));
        }
      }

      // top
      if (direction == '^')
      {
        if (times < 10 && direction != 'v')
        {
          vn.push_back(Node(row - 1, col, '^', times + 1, value + arr[row - 1][col]));
        }
      }
      else
      {
        if (direction != 'v')
        {
          vn.push_back(Node(row - 1, col, '^', 1, value + arr[row - 1][col]));
        }
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
  set<tuple<int, int, int, int>> vis;
  Node *found;
  minHeap.push(Node(0, 0, '>', 1, 0));
  minHeap.push(Node(0, 0, 'v', 1, 0));
  while (!minHeap.empty())
  {
    Node n = minHeap.top();
    minHeap.pop();
    if (n.row == max_row - 1 && n.col == max_col - 1)
    {
      found = &n;
      cout << "found.. " << n.Display() << endl;
      break;
    }

    if (vis.find({n.row, n.col, n.direction, n.times}) != vis.end() || crossed_boarder(n.row, n.col, max_row, max_col))
    {
      continue;
    };

    vis.insert({n.row, n.col, n.direction, n.times});

    for (Node adj : n.Next(arr))
    {
      minHeap.push(adj);
    }
  }

  return found->value;
}

long solve2(vector<string> input)
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
  set<tuple<int, int, int, int>> vis;
  Node *found;
  minHeap.push(Node(0, 0, '>', 1, 0));
  minHeap.push(Node(0, 0, 'v', 1, 0));
  while (!minHeap.empty())
  {
    Node n = minHeap.top();
    minHeap.pop();
    if (n.row == max_row - 1 && n.col == max_col - 1 && n.value > 4)
    {
      found = &n;
      cout << "found.. " << n.Display() << endl;
      break;
    }

    if (vis.find({n.row, n.col, n.direction, n.times}) != vis.end() || crossed_boarder(n.row, n.col, max_row, max_col))
    {
      continue;
    };

    // cout << "visiting.. " << n.Display() << endl;

    vis.insert({n.row, n.col, n.direction, n.times});

    for (Node adj : n.NextV2(arr))
    {
      minHeap.push(adj);
    }
  }

  return found->value;
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