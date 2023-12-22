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

int get_next(vector<int> numbers)
{
  vector<int> next_numbers;
  if (adjacent_find(numbers.begin(), numbers.end(), not_equal_to<>()) == numbers.end())
  {
    return numbers[0];
  }
  for (int i = 1; i < numbers.capacity(); i++)
  {
    next_numbers.push_back(numbers[i] - numbers[i - 1]);
  }

  return numbers.back() + get_next(next_numbers);
}

int solve(vector<string> input)
{
  int sum = 0;
  for (string line : input)
  {
    vector<int> numbers;
    stringstream ss(line);
    string each;
    while (ss >> each)
    {
      numbers.push_back(stoi(each));
    }
    sum += get_next(numbers);
  }
  return sum;
}

int solve2(vector<string> input)
{
  int sum = 0;
  for (string line : input)
  {
    vector<int> numbers;
    stringstream ss(line);
    string each;
    while (ss >> each)
    {
      numbers.push_back(stoi(each));
    }
    reverse(numbers.begin(), numbers.end());
    sum += get_next(numbers);
  }
  return sum;
}

int test()
{
  vector<int> v = {-5, -5, -5, -2};
  assert(v.back() == -2);
  assert(get_next({0, 0}) == 0);
  assert(get_next({1, 1}) == 1);
  assert(get_next({-5, -5, -5}) == -5);
  assert(get_next({1, 3, 6, 10, 15, 21}) == 28);
  assert(get_next({10, 13, 16, 21, 30, 45}) == 68);
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