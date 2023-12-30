#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>

#define VERBOSE

using namespace std;

int my_hash(string s)
{
  int v = 0;
  for (char c : s)
  {
    v += c;
    v *= 17;
    v %= 256;
  }
  return v;
}

long solve(vector<string> input)
{
  stringstream ss(input[0]);
  string token;
  long sum = 0;
  while (getline(ss, token, ','))
  {
    cout << token << endl;
    sum += my_hash(token);
  };
  return sum;
}

long solve2(vector<string> input)
{
  return 0;
}

int test()
{
  cout << my_hash("HASH") << endl;
  assert(my_hash("HASH") == 52);
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