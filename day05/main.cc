#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>

#define VERBOSE

using namespace std;

struct Rule
{
  long lower;
  long upper;
  long diff;
};

array<vector<Rule>, 7> init_rules(vector<string> input)
{
  array<vector<Rule>, 7> arr;
  int i = -1;
  for (const auto line : input)
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

      cout << "x: " << x;
      cout << " y: " << y;
      cout << " z: " << z;
      cout << " r.lower: " << r.lower;
      cout << " r.upper: " << r.upper;
      cout << " r.diff: " << r.diff;
      arr[i].push_back(r);
    }
    cout << endl;
  }
  return arr;
}

int solve(vector<string> input)
{
  string seeds = input[0];
  stringstream seedsStream(seeds);
  string seed;
  seedsStream >> seed;
  long min = LONG_MAX;
  array<vector<Rule>, 7> arr = init_rules(input);
  while (seedsStream >> seed)
  {
    long seedValue = stol(seed);
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
  return 0;
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
    cerr << "Failed to open " << quoted(path) << "\n";
    return 1;
  }

  vector<string> lines;
  string line;
  while (getline(file, line))
  {
    lines.push_back(line);
  }
  cout << "The part 1 answer is " << solve(lines) << "\n";
  cout << "The part 2 answer is " << solve2(lines) << "\n";

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