#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>
#include <map>
#include <regex>

#define VERBOSE

using namespace std;

typedef vector<string> Rule;
typedef map<string, Rule> Workflows;
struct Rating
{
  short x;
  short m;
  short a;
  short s;
  short sum;

  short get_value(char c)
  {
    if (c == 'x')
    {
      return x;
    }
    if (c == 'm')
    {
      return m;
    }
    if (c == 'a')
    {
      return a;
    }
    if (c == 's')
    {
      return s;
    }
  }
};

regex pattern1("(\\w+)\\{(.*)\\}");
regex pattern2("\\{x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)\\}");
regex pattern3("(\\w+)([><])(\\d+):(\\w+)");

string get_next(Rule rule, Rating rating)
{
  smatch match;
  for (string each : rule)
  {
    if (each.find(':') != -1)
    {
      if (std::regex_search(each, match, pattern3))
      {
        char key = match.str(1)[0];
        string operation = match.str(2);
        int value = stoi(match.str(3));
        string direction = match.str(4);
        if (operation == ">")
        {
          if (rating.get_value(key) > value)
          {
            return direction;
          }
          else
          {
            continue;
          }
        }
        if (operation == "<")
        {
          if (rating.get_value(key) < value)
          {
            return direction;
          }
          else
          {
            continue;
          }
        }
      }
      else
      {
        std::cerr << "No match found." << std::endl;
        throw std::runtime_error("No match found.");
      }
    }
    else
    {
      return each;
    }
  }
  throw std::runtime_error("No match found.");
}

long solve(vector<string> input)
{
  smatch match;
  bool found = false;
  Workflows w;
  vector<Rating> ratings;
  for (string line : input)
  {
    if (line.empty())
    {
      found = true;
      continue;
    }
    if (!found)
    {
      if (std::regex_search(line, match, pattern1))
      {
        string key;
        key = match.str(1);
        string rules;
        rules = match.str(2);
        stringstream ss(rules);
        string rule;
        Rule r;
        while (getline(ss, rule, ','))
        {
          r.push_back(rule);
        }
        w[key] = r;
      }
      else
      {
        std::cerr << "No match found." << std::endl;
        throw std::runtime_error("No match found.");
      }
    }
    else
    {
      if (std::regex_search(line, match, pattern2))
      {
        Rating r;
        r.x = stoi(match.str(1));
        r.m = stoi(match.str(2));
        r.a = stoi(match.str(3));
        r.s = stoi(match.str(4));
        r.sum = r.x + r.m + r.a + r.s;
        ratings.push_back(r);
      }
      else
      {
        std::cerr << "No match found." << std::endl;
        throw std::runtime_error("No match found.");
      }
    }
  }

  long sum;

  for (Rating r : ratings)
  {
    string s = "in";

    while (s != "A" && s != "R")
    {
      s = get_next(w[s], r);
    }
    if (s == "A")
    {
      sum += r.sum;
    }
  }

  return sum;
}

long solve2(vector<string> input)
{
  return 0;
}

int test()
{
  Rating r;
  r.x = 787;
  r.m = 2655;
  r.a = 1222;
  r.s = 2876;
  assert(get_next({"s<1351:px", "qqz"}, r) == "qqz");
  r.s = 0;
  assert(get_next({"s<1351:px", "qqz"}, r) == "px");
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