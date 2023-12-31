#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>
#include <set>
#include <stack>

#define VERBOSE

using namespace std;

const int rows = 140;
const int columns = 140;

bool crossed_boarder(int row, int col)
{
  return row < 0 || col < 0 || row >= rows || col >= columns;
}

bool is_valid(bool vis[][columns], int row, int col)
{
  if (crossed_boarder(row, col))
    return false;

  if (vis[row][col])
    return false;

  return true;
}

bool is_in_string(char c, string s)
{
  for (char cs : s)
  {
    if (c == cs)
    {
      return true;
    }
  }
  return false;
}

bool is_connected(char arr[][columns], int row, int col, string direction)
{
  // cout << "is_connected: " << arr[row][col] << " " << direction << endl;
  if (direction == "top")
  {
    if (is_in_string(arr[row][col], "LJ|"))
    {
      if (!crossed_boarder(row - 1, col) && is_in_string(arr[row - 1][col], "F7|S"))
      {
        return true;
      }
    }
  }

  if (direction == "bottom")
  {
    if (is_in_string(arr[row][col], "F7|"))
    {
      if (!crossed_boarder(row + 1, col) && is_in_string(arr[row + 1][col], "LJ|S"))
      {
        return true;
      }
    }
  }

  if (direction == "left")
  {
    if (is_in_string(arr[row][col], "-7J"))
    {
      if (!crossed_boarder(row, col - 1) && is_in_string(arr[row][col - 1], "FL-S"))
      {
        return true;
      }
    }
  }

  if (direction == "right")
  {
    if (is_in_string(arr[row][col], "-LF"))
    {
      if (!crossed_boarder(row, col + 1) && is_in_string(arr[row][col + 1], "7J-S"))
      {
        return true;
      }
    }
  }

  return false;
}

int dfs(char arr[][columns], bool vis[][columns], int row, int col)
{
  stack<tuple<int, int, int>> st;
  st.push({row, col, 1});
  int d;

  while (!st.empty())
  {

    tuple<int, int, int> curr = st.top();
    st.pop();

    int row = get<0>(curr);
    int col = get<1>(curr);
    d = get<2>(curr);

    cout << "visiting x: " << col << ", y: " << row << ", d: " << d << endl;
    if (!is_valid(vis, row, col))
      continue;

    vis[row][col] = true;

    // top
    if (is_connected(arr, row, col, "top"))
    {
      st.push({row - 1, col, d + 1});
      if (arr[row - 1][col] == 'S' && d > 2)
      {
        break;
      }
    }

    // bottom
    if (is_connected(arr, row, col, "bottom"))
    {
      st.push({row + 1, col, d + 1});
      if (arr[row - 1][col] == 'S' && d > 2)
      {
        break;
      }
    }

    // left
    if (is_connected(arr, row, col, "left"))
    {
      st.push({row, col - 1, d + 1});
      if (arr[row][col - 1] == 'S' && d > 2)
      {
        break;
      }
    }

    // right
    if (is_connected(arr, row, col, "right"))
    {
      st.push({row, col + 1, d + 1});
      if (arr[row][col + 1] == 'S' && d > 2)
      {
        break;
      }
    }
  }
  return d;
}

bool solve_rec(vector<pair<int, int>> *vis, bool wasHere[][columns], char arr[][columns], int col, int row, int xend, int yend, int d)
{
  if (col == xend && row == yend && d > 2)
    return true;

  if (wasHere[row][col])
  {
    return false;
  }

  wasHere[row][col] = true;

  // top
  if (is_connected(arr, row, col, "top"))
  {
    if (solve_rec(vis, wasHere, arr, col, row - 1, xend, yend, d + 1))
    {
      (*vis).push_back({col, row});
      return true;
    }
  }

  // bottom
  if (is_connected(arr, row, col, "bottom"))
  {
    if (solve_rec(vis, wasHere, arr, col, row + 1, xend, yend, d + 1))
    {
      (*vis).push_back({col, row});
      return true;
    }
  }

  // left
  if (is_connected(arr, row, col, "left"))
  {
    if (solve_rec(vis, wasHere, arr, col - 1, row, xend, yend, d + 1))
    {
      (*vis).push_back({col, row});
      return true;
    }
  }

  // right
  if (is_connected(arr, row, col, "right"))
  {
    if (solve_rec(vis, wasHere, arr, col + 1, row, xend, yend, d + 1))
    {
      (*vis).push_back({col, row});
      return true;
    }
  }
  return false;
}

void print_arr(bool vis[][columns])
{
  for (int i = 0; i < columns; i++)
  {
    for (int j = 0; j < rows; j++)
    {
      if (vis[i][j])
      {
        cout << '#';
      }
      else
      {
        cout << '.';
      }
    }
    cout << endl;
  }
}

int shoelace(vector<pair<int, int>> nums)
{
  vector<int> xs;
  vector<int> ys;
  int count = nums.size();
  int sum = 0;
  cout << "count: " << count << endl;
  for (pair p : nums)
  {
    cout << "x: " << p.first << ", y: " << p.second << endl;
    xs.push_back(p.first);
    ys.push_back(p.second);
  }
  for (int i = 0; i < count; ++i)
  {
    sum += xs[i] * ys[(i + 1) % count];
    sum -= ys[i] * xs[(i + 1) % count];
  }

  // pick's + shoelace
  return abs(sum) / 2 + 1 - count / 2;
}

int solve(vector<string> input)
{
  int x, y;
  char arr[rows][columns];
  bool vis[rows][columns];
  int j = 0;
  for (string line : input)
  {
    int i = 0;
    for (char c : line)
    {
      if (c == 'S')
      {
        y = j;
        x = i;
      }
      arr[j][i] = c;
      vis[j][i] = false;
      i++;
    }
    j++;
  }
  cout << "starting point x: " << x << ", y: " << y << endl;
  cout << "starting point value: " << arr[y][x] << endl;
  vis[y][x] = true;
  int ans = dfs(arr, vis, y + 1, x);
  return (ans + 1) / 2;
}

int solve2(vector<string> input)
{
  int x, y;
  char arr[rows][columns];
  vector<pair<int, int>> vis;
  bool wasHere[rows][columns];
  int j = 0;
  for (string line : input)
  {
    int i = 0;
    for (char c : line)
    {
      if (c == 'S')
      {
        y = j;
        x = i;
      }
      arr[j][i] = c;
      wasHere[j][i] = false;
      i++;
    }
    j++;
  }
  cout << "starting point x: " << x << ", y: " << y << endl;
  cout << "starting point value: " << arr[y][x] << endl;
  solve_rec(&vis, wasHere, arr, x, y + 1, x, y, 1);
  print_arr(wasHere);
  return shoelace(vis);
}

int test()
{
  return 0;
}

int parse_and_run(string_view path)
{
  vector<string> data;
  fstream file(path);
  if (!file.is_open())
  {
    cerr << "Failed to open " << quoted(path) << endl;
    return 1;
  }

  vector<string> lines;
  string line;
  while (getline(file, line))
  {
    lines.push_back(line);
  }
  int ans1 = solve(lines);
  int ans2 = solve2(lines);
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