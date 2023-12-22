#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>
#include <regex>
#include <map>
#include <numeric>

#define VERBOSE

using namespace std;

struct Node
{
  string left;
  string value;
  string right;
};

Node parse(string line)
{
  regex pattern(R"((\w{3}) = \((\w{3}), (\w{3})\))");
  smatch match;
  if (std::regex_search(line, match, pattern))
  {
    Node t;
    t.value = match.str(1);
    t.left = match.str(2);
    t.right = match.str(3);
    return t;
  }
  else
  {
    std::cerr << "No match found." << std::endl;
    throw std::runtime_error("No match found.");
  }
}

int count(string instructions, map<string, Node> map, string startingNode, string endNode)
{
  int steps = 0;
  string node = startingNode;
  bool found = false;
  while (!found)
  {
    for (char instruction : instructions)
    {
      if (instruction == 'L')
      {
        node = map[node].left;
      }
      if (instruction == 'R')
      {
        node = map[node].right;
      }
      steps++;
      if (node.ends_with(endNode))
      {
        found = true;
        break;
      }
    }
  }
  return steps;
}

int solve(vector<string> input)
{
  string instructions = input[0];
  map<string, Node> map;
  for (auto it = input.begin() + 2; it != input.end(); ++it)
  {
    Node n = parse(*it);
    map[n.value] = n;
  }

  return count(instructions, map, "AAA", "ZZZ");
}

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

long long int lcm_all(std::vector<int> &numbers)
{
  long long int result = 1;
  for (int num : numbers)
  {
    cout << num << " ";
    result = (result * num) / gcd(num, result);
  }
  cout << endl;
  return result;
}

long long int solve2(vector<string> input)
{
  string instructions = input[0];
  map<string, Node> map;
  vector<string> startingNodes;
  vector<int> counts;
  for (auto it = input.begin() + 2; it != input.end(); ++it)
  {
    Node n = parse(*it);
    map[n.value] = n;
    if (n.value.ends_with('A'))
    {
      startingNodes.push_back(n.value);
    }
  }

  for (string n : startingNodes)
  {
    cout << n << " ";
    counts.push_back(count(instructions, map, n, "Z"));
  }
  cout << endl;

  return lcm_all(counts);
}

int test()
{
  Node n = parse("CQN = (GPT, QRH)");
  assert(n.value == "CQN");
  assert(n.left == "GPT");
  assert(n.right == "QRH");
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
  long long int ans2 = solve2(lines);
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