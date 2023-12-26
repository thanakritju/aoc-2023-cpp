#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>
#include <algorithm>
#include <map>

#define VERBOSE

using namespace std;

int dp[100][100][100] = {{{0}}};

bool check_list(string line, vector<int> expected)
{
  vector<int> nums;
  int count = 0;
  int i = 0;
  for (char c : line)
  {
    if (c == '#')
    {
      count++;
    }
    else
    {
      if (count > 0)
      {
        nums.push_back(count);
        if (expected[i] != count)
        {
          return false;
        }
        i++;
      }
      count = 0;
    }
  }
  if (count > 0)
  {
    nums.push_back(count);
    if (expected[i] != count)
    {
      return false;
    }
  }
  return nums == expected;
}

bool should_search(string line, vector<int> expected)
{
  vector<int> nums;
  int count = 0;
  for (char c : line)
  {
    if (c == '?')
    {
      break;
    }
    if (c == '#')
    {
      count++;
    }
    else
    {
      if (count > 0)
      {
        nums.push_back(count);
      }
      count = 0;
    }
  }

  int i = 0;
  for (int num : nums)
  {
    if (num != expected[i])
    {
      return false;
    }
    i++;
  }

  return true;
}

int search(string t, vector<int> nums)
{
  int index = t.find('?');
  if (index == -1)
  {
    if (check_list(t, nums))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    string newstring(t);
    newstring[index] = '#';
    bool should_search1 = should_search(newstring, nums);

    string newstring2(t);
    newstring2[index] = '.';
    bool should_search2 = should_search(newstring2, nums);

    if (!should_search1 && should_search2)
    {
      return search(newstring2, nums);
    }
    if (should_search1 && !should_search2)
    {
      return search(newstring, nums);
    }
    if (should_search1 && should_search2)
    {
      return search(newstring, nums) + search(newstring2, nums);
    }
    else
    {
      return 0;
    }
  }
}

int search_v2(string s, vector<int> nums, int n)
{
  string substring(s);
  if (substring.size() == 0)
  {
    if (nums.size() == n)
    {
      return 1;
    }
    return 0;
  }
  if (nums.size() == n)
  {
    for (int x = 0; x < substring.size(); x++)
    {
      if (substring[x] == '#')
      {
        return 0;
      }
    }
  }
  int sum = -1;
  for (int i = n; i < nums.size(); i++)
  {
    sum += nums[i] + 1;
  }
  if (substring.size() < sum)
  {
    return 0;
  }

  if (substring[0] == '.')
  {
    return search_v2(s.substr(1), nums, n);
  }

  if (substring[0] == '#')
  {
    int run = nums[n];
    for (int i = 0; i < run; i++)
    {
      if (substring[i] == '.')
      {
        return 0;
      }
    }
    if (substring[run] == '#')
    {
      return 0;
    }
    return search_v2(s.substr(run), nums, n + 1);
  }
  string newstring1 = '#' + substring.substr(1);
  string newstring2 = '.' + substring.substr(1);

  return search_v2(newstring1, nums, n);
}

int get_arrangement(string line)
{
  stringstream ss(line);
  string puzzle;
  string numstring;
  ss >> puzzle;
  ss >> numstring;
  stringstream numss(numstring);
  vector<int> nums;

  while (getline(numss, numstring, ','))
  {
    nums.push_back(stoi(numstring));
  }
  return search_v2(puzzle, nums, 0);
}

int get_arrangement_5(string line)
{
  stringstream ss(line);
  string puzzle;
  string numstring;
  ss >> puzzle;
  ss >> numstring;
  stringstream numss(numstring);
  vector<int> nums;
  vector<int> new_nums;
  string new_puzzle = "";
  new_puzzle += puzzle;
  new_puzzle += '?';
  new_puzzle += puzzle;
  new_puzzle += '?';
  new_puzzle += puzzle;
  new_puzzle += '?';
  new_puzzle += puzzle;
  new_puzzle += '?';
  new_puzzle += puzzle;

  while (getline(numss, numstring, ','))
  {
    nums.push_back(stoi(numstring));
  }
  new_nums.insert(new_nums.end(), nums.begin(), nums.end());
  new_nums.insert(new_nums.end(), nums.begin(), nums.end());
  new_nums.insert(new_nums.end(), nums.begin(), nums.end());
  new_nums.insert(new_nums.end(), nums.begin(), nums.end());
  new_nums.insert(new_nums.end(), nums.begin(), nums.end());
  cout << "new_puzzle: " << new_puzzle << endl;
  cout << "new_nums: ";
  for (int n : new_nums)
  {
    cout << n << " ";
  }
  cout << endl;

  return search(new_puzzle, new_nums);
}

int solve(vector<string> input)
{
  int sum = 0;
  for (string line : input)
  {
    sum += get_arrangement(line);
  }
  return sum;
}

int solve2(vector<string> input)
{
  int sum = 0;
  for (string line : input)
  {
    sum += get_arrangement_5(line);
  }
  return sum;
}

int test()
{
  cout << get_arrangement("???.### 1,1,3") << endl;
  assert(search("???.###", {1, 1, 3}) == 1);
  assert(get_arrangement(".?..?????..##???.??? 1,4,2,1,1,1") == 4);
  assert(get_arrangement_5("???.### 1,1,3") == 1);
  assert(get_arrangement_5("?###???????? 3,2,1") == 506250);
  assert(get_arrangement("???.### 1,1,3") == 1);
  assert(get_arrangement(".??..??...?##. 1,1,3") == 4);
  assert(get_arrangement("?#?#?#?#?#?#?#? 1,3,1,6") == 1);
  assert(get_arrangement("????.#...#... 4,1,1") == 1);
  assert(get_arrangement("????.######..#####. 1,6,5") == 4);
  assert(get_arrangement("?###???????? 3,2,1") == 10);
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
  int ans2 = solve2(lines);
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