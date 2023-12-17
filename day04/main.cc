#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>

#define VERBOSE

int how_many_cards_won(std::string line)
{
  int count = 0;
  std::stringstream ss(line);
  std::string token;
  std::getline(ss, token, ':');
  std::getline(ss, token, ':');
  std::stringstream numbers(token);
  std::string wining_numbers;
  std::vector<int> wining_numbers_vec;
  std::getline(numbers, wining_numbers, '|');
  std::stringstream wining_numbers_ss(wining_numbers);
  std::string number;
  while (wining_numbers_ss >> number)
  {
    wining_numbers_vec.push_back(std::stoi(number));
  }

  std::string hands;
  std::vector<int> hands_vec;
  std::getline(numbers, hands, '|');
  std::stringstream hands_ss(hands);
  while (hands_ss >> number)
  {
    auto it = std::find(wining_numbers_vec.begin(), wining_numbers_vec.end(), std::stoi(number));
    if (it != wining_numbers_vec.end())
    {
      count += 1;
    }
  }
  return count;
}

int solve(std::vector<std::string> input)
{
  int sum = 0;
  for (const auto &line : input)
  {
    int count = how_many_cards_won(line);
    if (count > 0)
    {
      sum += std::pow(2, count - 1);
    }
  }
  return sum;
}

int solve2(std::vector<std::string> input)
{
  int sum = 0;
  std::array<int, 200> cardTimesMap;
  for (int i = 0; i < 200; i++)
  {
    cardTimesMap[i] = 1;
  }

  int row = 0;
  for (const auto &line : input)
  {
    int count = how_many_cards_won(line);
    if (count > 0)
    {
      for (int i = 1; i <= count; i++)
      {
        if (count + i < 200)
        {
          cardTimesMap[row + i] = cardTimesMap[row + i] + cardTimesMap[row];
        }
      }
    }
    row++;
  }

  for (int i = 0; i < row; i++)
  {
    sum += cardTimesMap[i];
  }

  return sum;
}

int test()
{
  assert(solve({"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"}) == 8);
  return 0;
}

int parse_and_run(std::string_view path)
{
  std::vector<std::string> data;
  std::fstream file(path);
  if (!file.is_open())
  {
    std::cerr << "Failed to open " << std::quoted(path) << "\n";
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line))
  {
    lines.push_back(line);
  }
  std::cout << "The part 1 answer is " << solve(lines) << "\n";
  std::cout << "The part 2 answer is " << solve2(lines) << "\n";

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