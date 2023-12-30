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

struct platform
{
  int length;
  map<pair<int, int>, bool> map;
};

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

vector<string> rotate_cclockwise(vector<string> input)
{
  vector<string> vs;
  int n = input.size() - 1;
  for (string _ : input)
  {
    vs.push_back("");
  }

  for (string s : input)
  {
    int row = n;
    for (char c : s)
    {
      vs[row] = vs[row] + c;
      row--;
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

platform init(vector<string> input)
{
  platform p;
  map<pair<int, int>, bool> m;
  int i = 0;
  for (string s : input)
  {
    int j = 0;
    for (char c : s)
    {
      if (c == 'O')
      {
        m[{i, j}] = false;
      }
      if (c == '#')
      {
        m[{i, j}] = true;
      }
      j++;
    }
    i++;
  }
  p.map = m;
  p.length = input.size();
  return p;
}

platform sort(platform p, string direction)
{
  platform np;
  map<pair<int, int>, bool> m;
  if (direction == "north")
  {
    for (int i = 0; i < p.length; i++)
    {
      int indexSharp = -1;
      int countO = 0;
      for (int j = 0; j < p.length; j++)
      {
        if (p.map.find({j, i}) != p.map.end())
        {
          if (!p.map[{j, i}])
          {
            countO++;
          }
          if (p.map[{j, i}])
          {
            m[{j, i}] = true;
            for (int x = indexSharp + 1; x < indexSharp + countO + 1; x++)
            {
              m[{x, i}] = false;
            }
            countO = 0;
            indexSharp = j;
          }
        }
      }
      for (int x = indexSharp + 1; x < indexSharp + countO + 1; x++)
      {
        m[{x, i}] = false;
      }
    }
  }

  if (direction == "west")
  {
    for (int i = 0; i < p.length; i++)
    {
      int indexSharp = -1;
      int countO = 0;
      for (int j = 0; j < p.length; j++)
      {
        if (p.map.find({i, j}) != p.map.end())
        {
          if (!p.map[{i, j}])
          {
            countO++;
          }
          if (p.map[{i, j}])
          {
            m[{i, j}] = true;
            for (int x = indexSharp + 1; x < indexSharp + countO + 1; x++)
            {
              m[{i, x}] = false;
            }
            countO = 0;
            indexSharp = j;
          }
        }
      }
      for (int x = indexSharp + 1; x < indexSharp + countO + 1; x++)
      {
        m[{i, x}] = false;
      }
    }
  }

  if (direction == "south")
  {
    for (int i = 0; i < p.length; i++)
    {
      int countO = 0;
      for (int j = 0; j < p.length; j++)
      {
        if (p.map.find({j, i}) != p.map.end())
        {
          if (!p.map[{j, i}])
          {
            countO++;
          }
          if (p.map[{j, i}])
          {
            m[{j, i}] = true;
            for (int x = j - 1; x > j - countO - 1; x--)
            {
              m[{x, i}] = false;
            }
            countO = 0;
          }
        }
      }
      for (int x = p.length - 1; x > p.length - countO - 1; x--)
      {
        m[{x, i}] = false;
      }
    }
  }

  if (direction == "east")
  {
    for (int i = 0; i < p.length; i++)
    {
      int indexSharp = -1;
      int countO = 0;
      for (int j = 0; j < p.length; j++)
      {
        if (p.map.find({i, j}) != p.map.end())
        {
          if (!p.map[{i, j}])
          {
            countO++;
          }
          if (p.map[{i, j}])
          {
            m[{i, j}] = true;
            for (int x = j - 1; x > j - countO - 1; x--)
            {
              m[{i, x}] = false;
            }
            countO = 0;
            indexSharp = j;
          }
        }
      }
      for (int x = p.length - 1; x > p.length - countO - 1; x--)
      {
        m[{i, x}] = false;
      }
    }
  }

  np.map = m;
  np.length = p.length;
  return np;
}

long count_load(platform p)
{
  long sum = 0;
  for (int i = 0; i < p.length; i++)
  {
    for (int j = 0; j < p.length; j++)
    {
      if (p.map.find({i, j}) != p.map.end())
      {
        if (!p.map[{i, j}])
        {
          sum += p.length - i;
        }
      }
    }
  }
  return sum;
}

void print(platform p)
{

  for (int i = 0; i < p.length; i++)
  {
    for (int j = 0; j < p.length; j++)
    {
      if (p.map.find({i, j}) != p.map.end())
      {
        if (!p.map[{i, j}])
        {
          cout << "O";
        }
        else
        {
          cout << "#";
        }
      }
      else
      {
        cout << ".";
      }
    }
    cout << endl;
  }
  cout << endl;
}

long solve(vector<string> input)
{
  platform p = init(input);
  return count_load(sort(p, "north"));
}

long solve2(vector<string> input)
{
  platform p = init(input);
  for (int i = 0; i < 200; i++)
  {
    p = sort(p, "north");
    p = sort(p, "west");
    p = sort(p, "south");
    p = sort(p, "east");
    cout << i << " " << count_load(p) << endl;
  }
  return count_load(p);
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