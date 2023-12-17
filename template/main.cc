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

int solve(vector<string> input)
{
  return 0;
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