#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>
#include <map>
#include <queue>

#define VERBOSE

using namespace std;

enum ModuleType
{
  Flipflop,
  Broadcast,
  Conjunction,
  Button,
};

struct Module
{
  ModuleType type;
  bool on;
  vector<string> destinations;
};

map<string, Module> init(vector<string> input)
{
  map<string, Module> m;
  for (string s : input)
  {
    stringstream ss(s);
    string key;
    string token;
    ss >> key;
    ss >> token;
    vector<string> destinations;
    Module mod;
    while (getline(ss, token, ','))
    {
      destinations.push_back(token);
    };
    mod.destinations = destinations;
    if (key == "broadcaster")
    {
      mod.type = Broadcast;
      m[key] = mod;
    }
    else
    {
      if (key[0] == '%')
      {
        mod.type = Flipflop;
        mod.om = false;
      }
      else
      {
        mod.type = Conjunction;
      }
      m[key.substr(1)] = mod;
    }
  }
  return m;
}

long solve(vector<string> input)
{
  map<string, Module> m = init(input);
  queue<pair<string, bool>> q;
  q.push({"broadcaster", false});

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