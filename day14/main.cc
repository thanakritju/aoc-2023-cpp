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

string sort(string s)
{
  string ns = "";
  int countO = 0;
  int count = 0;
  for (char c : s)
  {
    if (c == 'O')
    {
      countO++;
    }
    if (c == '#')
    {
      ns += string(countO, 'O');
      ns += string(count, '.');
      ns += '#';
      count = 0;
      countO = 0;
    }
    if (c == '.')
    {
      count++;
    }
  }
  ns += string(countO, 'O');
  ns += string(count, '.');
  return ns;
}

vector<string> sort_all(vector<string> input)
{
  vector<string> vs;
  for (string s : input)
  {
    vs.push_back(sort(s));
  }
  return vs;
}

vector<string> rotate_clockwise(vector<string> input)
{
  vector<string> vs;
  for (string _ : input)
  {
    vs.push_back("");
  }

  for (string s : input)
  {
    int row = 0;
    for (char c : s)
    {
      vs[row] = c + vs[row];
      row++;
    }
  }

  return vs;
}

int count_load(vector<string> input)
{
  int n = input.size();
  int load = 0;
  for (string s : input)
  {
    int j = n;
    for (char c : s)
    {
      if (c == 'O')
      {
        load += j;
      }
      j--;
    }
  }
  return load;
}

void print(vector<string> input)
{
  for (string s : input)
  {
    cout << s << endl;
  }
  cout << endl;
}

long solve(vector<string> input)
{
  return count_load(sort_all(rotate_clockwise(rotate_clockwise(rotate_clockwise(input)))));
}

long solve2(vector<string> input)
{
  return 0;
}

int test()
{
  cout << sort("O.OO#....#") << endl;
  assert(sort("O.") == "O.");
  assert(sort(".O") == "O.");
  assert(sort("O.OO#....#") == "OOO.#....#");
  assert(sort("O.OO#..O.#") == "OOO.#O...#");
  assert(sort("O.OO#..O.#.O") == "OOO.#O...#O.");
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