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

long possible_way_to_win(long time, long distance)
{
  long count = 0;
  for (long i = 0; i < time; i++)
  {
    if (i * (time - i) > distance)
    {
      count++;
    };
  }
  return count;
}

int solve(vector<string> input)
{
  std::stringstream times(input[0]);
  string time;
  times >> time;
  std::stringstream distances(input[1]);
  string distance;
  distances >> distance;
  long ans = 1;

  while (times >> time)
  {
    distances >> distance;
    cout << "Time: " << time << " Distance: " << distance << endl;
    ans *= possible_way_to_win(stol(time), stol(distance));
  }

  return ans;
}

int solve2(vector<string> input)
{
  std::stringstream times(input[0]);
  string timeToken;
  string time = "";
  times >> timeToken;
  std::stringstream distances(input[1]);
  string distanceToken;
  string distance = "";
  distances >> distanceToken;

  while (times >> timeToken)
  {
    distances >> distanceToken;
    time += timeToken;
    distance += distanceToken;
  }

  return possible_way_to_win(stol(time), stol(distance));
}

int test()
{
  assert(possible_way_to_win(7, 9) == 4);
  assert(possible_way_to_win(15, 40) == 8);
  assert(possible_way_to_win(30, 200) == 9);
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