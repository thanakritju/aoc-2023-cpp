#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <ranges>
#include <sstream>
#include <map>
#include <queue>

#define VERBOSE

using namespace std;

enum ModuleType
{
  Broadcast,
  Flipflop,
  Conjunction,
  Button,
};

struct Module
{
  ModuleType type;
  bool on = false;          // for flipflop
  map<string, bool> memory; // for conjuction
  vector<string> destinations;

  void print()
  {
    std::cout << "Type: ";
    switch (type)
    {
    case Flipflop:
      std::cout << "Flipflop";
      break;
    case Broadcast:
      std::cout << "Broadcast";
      break;
    case Conjunction:
      std::cout << "Conjunction";
      break;
    case Button:
      std::cout << "Button";
      break;
    default:
      std::cout << "Unknown";
    }

    std::cout << "\nOn: " << (on ? "true" : "false");

    std::cout << "\nMemory:\n";
    for (const auto &entry : memory)
    {
      std::cout << "  " << entry.first << ": " << (entry.second ? "true" : "false") << "\n";
    }

    std::cout << "Destinations:\n";
    for (const auto &destination : destinations)
    {
      std::cout << "  " << destination << "\n";
    }

    std::cout << "----------------\n";
  }

  vector<tuple<string, bool, string>> next(string previousKey, string currentKey, int currentPulse)
  {
    vector<tuple<string, bool, string>> v;

    if (type == Broadcast)
    {
      for (string each : destinations)
      {
        v.push_back({currentKey, false, each});
      }
    }

    if (type == Flipflop)
    {
      if (!currentPulse)
      {
        on = !on;
        for (string each : destinations)
        {
          v.push_back({currentKey, on, each});
        }
      }
    }

    if (type == Conjunction)
    {
      if (memory.count(previousKey) > 0)
      {
        memory[previousKey] = currentPulse;
      }
      bool nextPulse = true;
      for (pair<string, bool> p : memory)
      {
        nextPulse &= p.second;
      }

      for (string each : destinations)
      {
        v.push_back({currentKey, !nextPulse, each});
      }
    }

    return v;
  }

  std::size_t hash() const
  {
    std::size_t hashValue = 0;
    hashValue ^= std::hash<ModuleType>{}(type) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
    for (const auto &str : destinations)
    {
      hashValue ^= std::hash<std::string>{}(str) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
    }
    hashValue ^= std::hash<bool>{}(on) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
    for (const auto &pair : memory)
    {
      hashValue ^= std::hash<std::string>{}(pair.first) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
      hashValue ^= std::hash<bool>{}(pair.second) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
    }
    return hashValue;
  }

  bool operator==(const Module &other) const
  {
    return hash() == other.hash();
  }
};

bool isInitial(map<string, Module> m)
{
  for (pair<string, Module> p1 : m)
  {
    if (p1.second.type == Flipflop)
    {
      if (p1.second.on)
      {
        return false;
      }
    }
    if (p1.second.type == Conjunction)
    {
      for (pair<string, bool> p2 : p1.second.memory)
      {
        if (p2.second)
        {
          return false;
        }
      }
    }
  }
  return true;
}

void print(map<string, Module> m)
{
  for (pair<string, Module> p : m)
  {
    cout << "key " << p.first << endl;
    p.second.print();
  }
}

map<string, Module> init(vector<string> input)
{
  map<string, Module> m;
  for (string s : input)
  {
    stringstream ss(s);
    string key = "";
    string token = "";
    ss >> key;
    ss >> token;
    vector<string> destinations{};
    Module mod;
    while (getline(ss, token, ','))
    {
      if (token[0] = ' ')
      {
        destinations.push_back(token.substr(1));
      }
      else
      {
        destinations.push_back(token);
      }
    };
    mod.destinations = destinations;
    if (key == "broadcaster")
    {
      mod.type = Broadcast;
      m["broadcaster"] = mod;
    }
    else
    {
      if (key[0] == '%')
      {
        mod.type = Flipflop;
        m[key.substr(1)] = mod;
      }
      if (key[0] == '&')
      {
        mod.type = Conjunction;
        m[key.substr(1)] = mod;
      }
    }
  }

  for (pair<string, Module> p1 : m)
  {
    for (string k : p1.second.destinations)
    {
      if (m[k].type == Conjunction)
      {
        m[k].memory[p1.first] = false;
      }
    }
  }
  return m;
}

long solve(vector<string> input)
{
  map<string, Module> m = init(input);
  int times = 0;
  print(m);
  vector<pair<int, int>> v;
  int lows = 0;
  int highs = 0;
  int c = 0;
  while (true)
  {
    queue<tuple<string, bool, string>> q;
    q.push({"button", false, "broadcaster"});

    while (!q.empty())
    {
      tuple<string, bool, string> curr = q.front();
      q.pop();
      string previousKey = get<0>(curr);
      bool isHigh = get<1>(curr);
      string key = get<2>(curr);
      cout << previousKey << " -" << isHigh << "-> " << key << endl;

      if (isHigh)
      {
        highs++;
      }
      else
      {
        lows++;
      }
      for (tuple<string, bool, string> t : m[key].next(previousKey, key, isHigh))
      {
        q.push(t);
      }
    }
    cout << "lows: " << lows << " highs: " << highs << endl;
    v.push_back({lows, highs});
    c++;
    if (isInitial(m) || c > times)
    {
      break;
    }
  }
  cout << "v.size() " << v.size() << endl;
  int count = times / v.size();
  int count2 = times % v.size();
  pair<int, int> top = v.back();

  return top.first * count * top.second * count;
}

long solve2(vector<string> input)
{
  return 0;
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