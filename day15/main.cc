#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>
#include <map>

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
    sum += my_hash(token);
  };
  return sum;
}

long solve2(vector<string> input)
{
  long sum = 0;
  map<int, vector<pair<string, int>>> m;
  stringstream ss(input[0]);
  string token;
  while (getline(ss, token, ','))
  {
    string sub_token;
    stringstream sstoken(token);
    if (token.find('=') != -1)
    {
      getline(sstoken, sub_token, '=');
      string key = sub_token;
      getline(sstoken, sub_token, '=');
      int value = stoi(sub_token);
      cout << "inserting... key: " << key << " value: " << value << endl;

      int i = 0;
      bool found = false;
      for (pair<string, int> each : m[my_hash(key)])
      {
        if (each.first == key)
        {
          each.second = value;
          found = true;
          break;
        }
        i++;
      }
      if (!found)
      {
        m[my_hash(key)].push_back({key, value});
      }
      else
      {
        m[my_hash(key)][i] = {m[my_hash(key)][i].first, value};
      }
    }
    else
    {
      getline(sstoken, sub_token, '-');
      string key = sub_token;
      cout << "removing... key: " << key << endl;
      int i = 0;
      bool found = false;
      for (pair<string, int> each : m[my_hash(key)])
      {
        if (each.first == key)
        {
          found = true;
          break;
        }
        i++;
      }
      if (found)
      {
        m[my_hash(key)].erase(m[my_hash(key)].begin() + i);
      }
    }
  };
  for (pair<int, vector<pair<string, int>>> p : m)
  {
    int i = 1;
    for (pair<string, int> each : p.second)
    {
      cout << p.first + 1 << " " << i << " " << each.second << endl;
      sum += (p.first + 1) * i * each.second;
      i++;
    }
  }
  return sum;
}

int test()
{
  cout << my_hash("HASH") << endl;
  assert(my_hash("HASH") == 52);
  assert(my_hash("rn") == 0);
  assert(my_hash("qp") == 1);
  assert(my_hash("ot") == 3);
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