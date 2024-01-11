#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>
#include <set>

#define VERBOSE

using namespace std;

set<pair<int, int>> get_adj(pair<int, int> p, set<pair<int, int>> rocks)
{
  set<pair<int, int>> s;
  if (rocks.find({p.first + 1, p.second}) == rocks.end())
  {
    s.insert({p.first + 1, p.second});
  }
  if (rocks.find({p.first - 1, p.second}) == rocks.end())
  {
    s.insert({p.first - 1, p.second});
  }
  if (rocks.find({p.first, p.second + 1}) == rocks.end())
  {
    s.insert({p.first, p.second + 1});
  }
  if (rocks.find({p.first, p.second - 1}) == rocks.end())
  {
    s.insert({p.first, p.second - 1});
  }
  return s;
}

set<pair<int, int>> get_adj_2(int max_i, int max_j, pair<int, int> p, set<pair<int, int>> rocks)
{
  set<pair<int, int>> s;
  if (rocks.find({(p.first + 1) % max_i, p.second % max_j}) == rocks.end())
  {
    s.insert({p.first + 1, p.second});
  }
  if (rocks.find({(p.first - 1) % max_i, p.second % max_j}) == rocks.end())
  {
    s.insert({p.first - 1, p.second});
  }
  if (rocks.find({p.first % max_i, (p.second + 1) % max_j}) == rocks.end())
  {
    s.insert({p.first, p.second + 1});
  }
  if (rocks.find({p.first % max_i, (p.second - 1) % max_j}) == rocks.end())
  {
    s.insert({p.first, p.second - 1});
  }
  return s;
}

long solve(vector<string> input)
{
  int round = 64;
  set<pair<int, int>> rocks;
  set<pair<int, int>> plots;
  int j = 0;
  for (string line : input)
  {
    int i = 0;
    for (char c : line)
    {
      if (c == '#')
      {
        rocks.insert({i, j});
      }
      if (c == 'S')
      {
        plots.insert({i, j});
      }
      i++;
    }
    j++;
  }

  int count = 0;
  int previous_size = 0;
  while (count < round)
  {
    set<pair<int, int>> new_plots;
    for (pair<int, int> p : plots)
    {
      for (pair<int, int> adj : get_adj(p, rocks))
      {
        new_plots.insert(adj);
      }
    }
    plots = new_plots;
    int current_size = plots.size();
    cout << "round " << count + 1 << " size " << current_size << " diff " << current_size - previous_size << endl;
    previous_size = current_size;
    count++;
  }

  return plots.size();
}

long solve2(vector<string> input)
{
  int round = 64;
  set<pair<int, int>> rocks;
  set<pair<int, int>> plots;
  int max_i = input[0].size();
  int max_j = input.size();
  int j = 0;
  for (string line : input)
  {
    int i = 0;
    for (char c : line)
    {
      if (c == '#')
      {
        rocks.insert({i, j});
      }
      if (c == 'S')
      {
        plots.insert({i, j});
      }
      i++;
    }
    j++;
  }
  int count = 0;
  int previous_size = 0;
  while (count < round)
  {
    set<pair<int, int>> new_plots;
    for (pair<int, int> p : plots)
    {
      for (pair<int, int> adj : get_adj_2(max_i, max_j, p, rocks))
      {
        new_plots.insert(adj);
      }
    }
    plots = new_plots;
    int current_size = plots.size();
    cout << "round " << count + 1 << " size " << current_size << " diff " << current_size - previous_size << endl;
    previous_size = current_size;
    count++;
  }
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
  long ans1 = 0;
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