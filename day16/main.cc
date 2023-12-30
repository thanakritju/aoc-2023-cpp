#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>
#include <stack>

#define VERBOSE

using namespace std;

const int rows = 110;
const int columns = 110;

bool crossed_boarder(int row, int col, int max_row, int max_col)
{
  return row < 0 || col < 0 || row >= max_row || col >= max_col;
}

int count(string vis[][columns], int max_row, int max_col)
{
  int count = 0;
  for (int i = 0; i < max_row; i++)
  {
    for (int j = 0; j < max_col; j++)
    {
      if (vis[i][j].size() > 0)
      {
        count++;
      }
    }
  }
  return count;
}

vector<tuple<int, int, char>> get_next_directions(char arr[rows][columns], int row, int col, char direction, int max_row, int max_col)
{
  vector<tuple<int, int, char>> v;

  if (direction == '>' && !crossed_boarder(row, col + 1, max_row, max_col))
  {
    char next = arr[row][col + 1];
    if (next == '|')
    {
      v.push_back({row, col + 1, '^'});
      v.push_back({row, col + 1, 'v'});
    }
    if (next == '\\')
    {
      v.push_back({row, col + 1, 'v'});
    }
    if (next == '/')
    {
      v.push_back({row, col + 1, '^'});
    }
    if (next == '-' || next == '.')
    {
      v.push_back({row, col + 1, '>'});
    }
  }

  if (direction == '<' && !crossed_boarder(row, col - 1, max_row, max_col))
  {
    char next = arr[row][col - 1];
    if (next == '|')
    {
      v.push_back({row, col - 1, '^'});
      v.push_back({row, col - 1, 'v'});
    }
    if (next == '\\')
    {
      v.push_back({row, col - 1, '^'});
    }
    if (next == '/')
    {
      v.push_back({row, col - 1, 'v'});
    }
    if (next == '-' || next == '.')
    {
      v.push_back({row, col - 1, '<'});
    }
  }

  if (direction == '^' && !crossed_boarder(row - 1, col, max_row, max_col))
  {
    char next = arr[row - 1][col];
    if (next == '-')
    {
      v.push_back({row - 1, col, '<'});
      v.push_back({row - 1, col, '>'});
    }
    if (next == '\\')
    {
      v.push_back({row - 1, col, '<'});
    }
    if (next == '/')
    {
      v.push_back({row - 1, col, '>'});
    }
    if (next == '|' || next == '.')
    {
      v.push_back({row - 1, col, '^'});
    }
  }

  if (direction == 'v' && !crossed_boarder(row + 1, col, max_row, max_col))
  {
    char next = arr[row + 1][col];
    if (next == '-')
    {
      v.push_back({row + 1, col, '<'});
      v.push_back({row + 1, col, '>'});
    }
    if (next == '\\')
    {
      v.push_back({row + 1, col, '>'});
    }
    if (next == '/')
    {
      v.push_back({row + 1, col, '<'});
    }
    if (next == '|' || next == '.')
    {
      v.push_back({row + 1, col, 'v'});
    }
  }
  return v;
}

long dfs(char arr[rows][columns], tuple<int, int, char> start, int max_row, int max_col)
{
  string vis[rows][columns];
  for (int i = 0; i < max_row; i++)
  {
    for (int j = 0; j < max_col; j++)
    {
      vis[i][j] = "";
    }
  }
  stack<tuple<int, int, char>> st;
  int row = get<0>(start);
  int col = get<1>(start);
  char direction = get<2>(start);
  for (tuple<int, int, char> t : get_next_directions(arr, row, col, direction, max_row, max_col))
  {
    st.push(t);
  };

  while (!st.empty())
  {
    tuple<int, int, char> curr = st.top();
    st.pop();

    int row = get<0>(curr);
    int col = get<1>(curr);
    char direction = get<2>(curr);
    // cout << "row: " << row << " col: " << col << " direction: " << direction << endl;

    if (vis[row][col].find(direction) != -1)
    {
      continue;
    }

    vis[row][col] += direction;
    for (tuple<int, int, char> t : get_next_directions(arr, row, col, direction, max_row, max_col))
    {
      st.push(t);
    };
  }

  return count(vis, max_row, max_col);
}

long solve(vector<string> input)
{
  char arr[rows][columns];
  int max_row = input.size();
  int max_col = input[0].size();
  for (int i = 0; i < max_row; i++)
  {
    for (int j = 0; j < max_col; j++)
    {
      arr[i][j] = input[i][j];
    }
  }

  return dfs(arr, {0, -1, '>'}, max_row, max_col);
}

long solve2(vector<string> input)
{
  char arr[rows][columns];
  int max_row = input.size();
  int max_col = input[0].size();
  for (int i = 0; i < max_row; i++)
  {
    for (int j = 0; j < max_col; j++)
    {
      arr[i][j] = input[i][j];
    }
  }
  long count = 0;
  cout << "max_row :" << max_row << " max_col: " << max_col << endl;
  for (int i = 0; i < max_row; i++)
  {
    long c1 = dfs(arr, {i, -1, '>'}, max_row, max_col);
    cout << "i: " << i << " c1: " << c1 << endl;
    long c2 = dfs(arr, {i, max_row, '<'}, max_row, max_col);
    cout << "i: " << i << " c2: " << c2 << endl;
    long c3 = dfs(arr, {-1, i, 'v'}, max_row, max_col);
    cout << "i: " << i << " c3: " << c3 << endl;
    long c4 = dfs(arr, {max_col, i, '^'}, max_row, max_col);
    cout << "i: " << i << " c4: " << c4 << endl;
    if (c1 > count)
    {
      count = c1;
    }
    if (c2 > count)
    {
      count = c2;
    }
    if (c3 > count)
    {
      count = c3;
    }
    if (c4 > count)
    {
      count = c4;
    }
  }

  return count;
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