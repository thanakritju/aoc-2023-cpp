#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>
#include <set>

#define VERBOSE

using namespace std;

struct Rule
{
  long lower;
  long upper;
  long diff;
  long source;
  long destination;
  long length;
};

struct Seed
{
  long lower;
  long upper;
};

array<vector<Rule>, 7> init_rules(vector<string> input)
{
  array<vector<Rule>, 7> arr;
  int i = -1;
  for (string line : input)
  {
    if (line.empty())
    {
      i++;
    }
    if (isdigit(line[0]))
    {
      Rule r;
      string x, y, z;
      stringstream lineStream(line);
      lineStream >> x;
      lineStream >> y;
      lineStream >> z;
      r.lower = stol(y);
      r.upper = stol(y) + stol(z);
      r.diff = stol(x) - stol(y);
      r.source = stol(y);
      r.destination = stol(x);
      r.length = stol(z);

      cout << "r.source: " << r.source;
      cout << " r.destination: " << r.destination;
      cout << " r.length: " << r.length;
      cout << " r.lower: " << r.lower;
      cout << " r.upper: " << r.upper;
      cout << " r.diff: " << r.diff;
      arr[i].push_back(r);
    }
    cout << endl;
  }
  return arr;
}

vector<long> init_seeds(string input)
{
  vector<long> seeds;
  stringstream seedsStream(input);
  string seed;
  seedsStream >> seed;
  while (seedsStream >> seed)
  {
    seeds.push_back(stol(seed));
  }
  return seeds;
}

set<long> init_seeds_v2(string input)
{
  set<long> seeds;
  stringstream seedsStream(input);
  string seed;
  seedsStream >> seed;
  bool b = false;
  long previosSeed = 0;
  while (seedsStream >> seed)
  {
    if (b)
    {
      seeds.insert(previosSeed + stol(seed));
    }
    else
    {
      seeds.insert(stol(seed));
      previosSeed = stol(seed);
    }
    b = !b;
  }
  return seeds;
}

set<long> current_seed(vector<Rule> rules)
{
  set<long> seeds;
  for (Rule r : rules)
  {
    seeds.insert(r.lower - r.diff);
    seeds.insert(r.upper - r.diff);
  }
  return seeds;
}

vector<Seed> init_seeds_object(string s)
{
  vector<Seed> seeds;
  stringstream seedsStream(s);
  string seed;
  seedsStream >> seed;
  string lower;
  string diff;

  while (seedsStream >> lower && seedsStream >> diff)
  {
    Seed s;
    s.lower = stol(lower);
    s.upper = stol(lower) + stol(diff);
    cout << " Seed.lower: " << s.lower << endl;
    cout << " Seed.upper: " << s.upper << endl;
    seeds.push_back(s);
  }
  return seeds;
}

bool is_in_seeed_range(long value, vector<Seed> seeds)
{
  for (Seed seed : seeds)
  {
    if (value >= seed.lower && value < seed.upper)
    {
      return true;
    }
  }
  return false;
}

int solve(vector<string> input)
{
  long min = LONG_MAX;
  array<vector<Rule>, 7> arr = init_rules(input);
  vector<long> seeds = init_seeds(input[0]);
  for (long seedValue : seeds)
  {
    for (int i = 0; i < 7; i++)
    {
      cout << "i: " << i;
      cout << " Value: " << seedValue << endl;
      for (Rule r : arr[i])
      {
        if (r.upper >= seedValue && seedValue >= r.lower)
        {
          seedValue += r.diff;
          break;
        }
      }
    }
    if (seedValue < min)
    {
      min = seedValue;
    }
    cout << endl;
  }
  return min;
}

int solve2(vector<string> input)
{
  array<vector<Rule>, 7> arr = init_rules(input);
  vector<Seed> seeds = init_seeds_object(input[0]);
  for (long seed = 0; seed < 1000000000; seed++)
  {
    long seedValue = seed;
    for (int i = 6; i >= 0; i--)
    {
      for (Rule r : arr[i])
      {
        if (r.destination <= seedValue && r.destination + r.length > seedValue)
        {
          seedValue = seedValue + r.source - r.destination;
          break;
        }
      }
    }
    if (is_in_seeed_range(seedValue, seeds))
    {
      return seed;
    }
  }

  return -1;
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