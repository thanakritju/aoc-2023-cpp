#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>

#define VERBOSE

using namespace std;

long long shoelace(vector<pair<long long, long long>> nums)
{
  vector<long long> xs;
  vector<long long> ys;
  int count = nums.size();
  long long sum = 0;
  for (pair p : nums)
  {
    xs.push_back(p.first);
    ys.push_back(p.second);
  }
  for (int i = 0; i < count; ++i)
  {
    sum += xs[i] * ys[(i + 1) % count];
    sum -= ys[i] * xs[(i + 1) % count];
  }

  return abs(sum) / 2;
}

long long picks_theorem(long long area, long long count)
{
  return area + 1 - count / 2;
}

long solve(vector<string> input)
{
  long sum = 0;
  vector<pair<long long, long long>> nums;
  long long x = 0;
  long long y = 0;
  for (string line : input)
  {
    stringstream ss(line);
    string direction;
    string value;
    ss >> direction;
    ss >> value;
    long valueInt = stoi(value);
    sum += valueInt;
    if (direction == "D")
    {
      y -= valueInt;
    }
    if (direction == "U")
    {
      y += valueInt;
    }
    if (direction == "L")
    {
      x -= valueInt;
    }
    if (direction == "R")
    {
      x += valueInt;
    }

    nums.push_back({x, y});
  }

  return sum + picks_theorem(shoelace(nums), sum);
}

long long solve2(vector<string> input)
{

  long long sum = 0;
  vector<pair<long long, long long>> nums;
  long long x = 0;
  long long y = 0;
  for (string line : input)
  {
    stringstream ss(line);
    stringstream ss2;
    char direction;
    string hex;
    unsigned int valueInt = 0;
    ss >> hex;
    ss >> hex;
    ss >> hex;
    direction = hex[7];
    ss2 << std::hex << hex.substr(2, 5);
    ss2 >> valueInt;
    // cout << "direction: " << direction << " hex: " << hex.substr(2, 5) << " v: " << valueInt << endl;
    sum += valueInt;
    if (direction == '1')
    {
      y -= valueInt;
    }
    if (direction == '3')
    {
      y += valueInt;
    }
    if (direction == '2')
    {
      x -= valueInt;
    }
    if (direction == '0')
    {
      x += valueInt;
    }

    nums.push_back({x, y});
  }
  cout << "sum: " << sum << " shoelace(nums): " << shoelace(nums) << " picks_theorem(shoelace(nums), sum): " << picks_theorem(shoelace(nums), sum) << endl;

  return sum + picks_theorem(shoelace(nums), sum);
}

int test()
{
  cout << picks_theorem(8, 5) << endl;
  assert(shoelace({{2, 1}, {1, 3}, {4, 2}, {6, 4}, {5, 0}}) == 8);
  assert(picks_theorem(8, 5) == 6);
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
  long long ans2 = solve2(lines);
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