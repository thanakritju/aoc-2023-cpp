#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>

#define VERBOSE

using namespace std;

int columns = 500;
int rows = 500;

void print(vector<pair<long, long>> vertices)
{
  cout << "------------------" << endl;
  for (pair<long, long> v : vertices)
  {
    cout << "x: " << v.first << ", y: " << v.second << endl;
  }
  cout << "------------------" << endl;
}

bool has_galaxy(string s)
{
  return s.find('#') != -1;
}

vector<pair<long, long>> init_with_multiply(vector<string> input, int times)
{
  int x = 0;
  vector<pair<long, long>> vertices;
  vector<pair<long, long>> expanded_vertices;
  vector<int> xs;
  vector<int> ys;
  string s;
  for (string line : input)
  {
    int y = 0;
    for (char c : line)
    {
      if (c == '#')
      {
        vertices.push_back({y, x});
      }
      y++;
    }
    x++;
  }
  print(vertices);

  for (int i = 0; i < input.size(); i++)
  {
    s = "";
    for (int j = 0; j < input[i].size(); j++)
    {
      s += input[i][j];
    }
    if (!has_galaxy(s))
    {
      cout << "y: " << i << endl;
      ys.push_back(i);
    }
  }

  for (int i = 0; i < input.size(); i++)
  {
    s = "";
    for (int j = 0; j < input[i].size(); j++)
    {
      s += input[j][i];
    }
    if (!has_galaxy(s))
    {
      cout << "x: " << i << endl;
      xs.push_back(i);
    }
  }

  for (pair<long, long> v : vertices)
  {
    int dx = 0;
    int dy = 0;
    for (int x : xs)
    {
      if (v.first > x)
      {
        dx += times - 1;
      }
    }
    for (int y : ys)
    {
      if (v.second > y)
      {
        dy += times - 1;
      }
    }
    expanded_vertices.push_back({v.first + dx, v.second + dy});
  }
  print(expanded_vertices);

  return expanded_vertices;
}

int manhattan(pair<int, int> p1, pair<int, int> p2)
{
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int solve(vector<string> input)
{
  vector<pair<long, long>> vertices = init_with_multiply(input, 2);
  int sum = 0;
  for (size_t i = 1; i < vertices.size(); ++i)
  {
    for (size_t j = 0; j < i; j++)
    {
      sum += manhattan(vertices[i], vertices[j]);
    }
  }

  return sum;
}

long solve2(vector<string> input)
{
  vector<pair<long, long>> vertices = init_with_multiply(input, 1000000);
  long sum = 0;
  for (size_t i = 1; i < vertices.size(); ++i)
  {
    for (size_t j = 0; j < i; j++)
    {
      sum += manhattan(vertices[i], vertices[j]);
    }
  }

  return sum;
}

int test()
{
  assert(has_galaxy("..........") == false);
  assert(has_galaxy(".#......#.") == true);
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