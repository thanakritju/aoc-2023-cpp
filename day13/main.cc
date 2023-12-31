#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>

#define VERBOSE

using namespace std;

vector<string> transpose(vector<string> input)
{
  vector<string> lines;

  for (char _ : input[0])
  {
    lines.push_back("");
  }
  for (string line : input)
  {
    int j = 0;
    for (char c : line)
    {
      lines[j] += c;
      j++;
    }
  }
  return lines;
}

int get_diff_in_string(string s1, string s2)
{
  int count = 0;
  int i = 0;
  for (char _ : s1)
  {
    if (s1[i] != s2[i])
    {
      count++;
    }
    i++;
  }
  return count;
}

int find_mirror(vector<string> input)
{
  int n = input.size();
  for (int i = 0; i < n - 1; i++)
  {
    int top = i;
    int bottom = i + 1;
    bool found = true;
    while (top > -1 && bottom < n)
    {
      if (input[top] != input[bottom])
      {
        found = false;
      }
      top--;
      bottom++;
    }
    if (found)
    {
      return i + 1;
    }
  }
  return 0;
}

void print(vector<string> input)
{
  for (string s : input)
  {
    cout << s << endl;
  }
  cout << endl;
}

int find_mirror_v2(vector<string> input)
{
  int n = input.size();
  for (int i = 0; i < n - 1; i++)
  {
    int top = i;
    int bottom = i + 1;
    int count = 0;
    while (top > -1 && bottom < n)
    {
      count += get_diff_in_string(input[top], input[bottom]);
      top--;
      bottom++;
    }
    if (count == 0)
    {
      cout << "found old " << i + 1 << endl;
      print(input);
    }
    if (count == 1)
    {
      cout << "found new " << i + 1 << endl;
      print(input);
      return i + 1;
    }
  }
  return 0;
}

int count(vector<string> input)
{
  int c1 = find_mirror(input);
  int c2 = find_mirror(transpose(input));
  return 100 * c1 + c2;
}

int count_v2(vector<string> input)
{
  int c1 = find_mirror_v2(input);
  int c2 = find_mirror_v2(transpose(input));
  return 100 * c1 + c2;
}

long long solve(vector<string> input)
{
  long long sum = 0;
  vector<string> lines;
  for (string l : input)
  {
    if (l.empty())
    {
      sum += count(lines);
      lines = {};
    }
    else
    {
      lines.push_back(l);
    }
  }
  sum += count(lines);
  return sum;
}

long long solve2(vector<string> input)
{
  long long sum = 0;
  vector<string> lines;
  for (string l : input)
  {
    if (l.empty())
    {
      sum += count_v2(lines);
      lines = {};
    }
    else
    {
      lines.push_back(l);
    }
  }
  sum += count_v2(lines);
  return sum;
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