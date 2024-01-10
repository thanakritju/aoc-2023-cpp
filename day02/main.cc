#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>

// #define VERBOSE
using namespace std;

int possible_to_reveal(std::string input)
{
  std::stringstream ss(input);
  std::string token;
  std::getline(ss, token, ':');
  std::stringstream gameStream(token);
  std::string gameLabel;
  std::getline(gameStream, gameLabel, ' ');
  std::getline(gameStream, gameLabel, ' ');

#ifdef VERBOSE
  std::cout << "Game: " << gameLabel << std::endl;
#endif

  while (std::getline(ss, token, ';'))
  {
    std::stringstream gameStream(token);
    std::string itemStr;
    while (std::getline(gameStream, itemStr, ','))
    {
      std::stringstream itemStream(itemStr);
      std::string color;
      std::string quantity;

      itemStream >> quantity;
      itemStream >> color;

#ifdef VERBOSE
      std::cout << std::stoi(quantity) << " " << color << "; ";
#endif

      if (color == "blue" && std::stoi(quantity) > 14)
      {
        return 0;
      }
      if (color == "green" && std::stoi(quantity) > 13)
      {
        return 0;
      }
      if (color == "red" && std::stoi(quantity) > 12)
      {
        return 0;
      }
    }

#ifdef VERBOSE
    std::cout << std::endl;
#endif
  }

  return std::stoi(gameLabel);
}

int possible_to_reveal_v2(std::string input)
{
  std::stringstream ss(input);
  std::string token;
  std::getline(ss, token, ':');
  std::stringstream gameStream(token);
  std::string gameLabel;
  std::getline(gameStream, gameLabel, ' ');
  std::getline(gameStream, gameLabel, ' ');
  int maxRed = 0;
  int maxGreen = 0;
  int maxBlue = 0;

#ifdef VERBOSE
  std::cout << "Game: " << gameLabel << std::endl;
#endif

  while (std::getline(ss, token, ';'))
  {
    std::stringstream gameStream(token);
    std::string itemStr;
    while (std::getline(gameStream, itemStr, ','))
    {
      std::stringstream itemStream(itemStr);
      std::string color;
      std::string quantity;
      int quantityInt;

      itemStream >> quantity;
      itemStream >> color;
      quantityInt = std::stoi(quantity);

#ifdef VERBOSE
      std::cout << quantityInt << " " << color << "; ";
#endif

      if (color == "blue" && quantityInt > maxBlue)
      {
        maxBlue = quantityInt;
      }
      if (color == "green" && quantityInt > maxGreen)
      {
        maxGreen = quantityInt;
      }
      if (color == "red" && quantityInt > maxRed)
      {
        maxRed = quantityInt;
      }
    }

#ifdef VERBOSE
    std::cout << std::endl;
#endif
  }

  return maxBlue * maxGreen * maxRed;
}

int test()
{
  assert(possible_to_reveal("Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue") == 2);
  assert(possible_to_reveal_v2("Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red") == 1560);
  assert(possible_to_reveal("Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red") == 0);
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

  std::string line;
  int sum = 0;
  int sum1 = 0;
  while (std::getline(file, line))
  {
    sum += possible_to_reveal(line);
    sum1 += possible_to_reveal_v2(line);
  }
  std::cout << "The part 1 answer is " << sum << "\n";
  std::cout << "The part 2 answer is " << sum1 << "\n";

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