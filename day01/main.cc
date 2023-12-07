#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <ctype.h>
#include <map>

int count(std::string data)
{
  int first = 0;
  int last;
  for (char &c : data)
  {
    if (isdigit(c))
    {
      if (!first)
      {
        first = c - '0';
      }
      last = c - '0';
    }
  }
  return first * 10 + last;
}

int countV2(std::string data)
{
  std::map<std::string, int> map = {{"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  size_t firstIndex = INT_MAX;
  size_t lastIndex = 0;
  size_t firstValue = 0;
  size_t lastValue = 0;
  for (auto const &imap : map)
  {
    std::size_t found = data.find(imap.first);
    while (true)
    {
      if (found < firstIndex)
      {
        firstIndex = found;
        firstValue = imap.second;
      }
      if (found > lastIndex && found < data.length())
      {
        lastIndex = found;
        lastValue = imap.second;
      }
      std::size_t found = data.find(imap.first, found + 1);
      std::cout << "key " << imap.first << "\n";
      std::cout << "found " << found << "\n";
      std::cout << "firstValue " << firstValue << "\n";
      std::cout << "lastValue " << lastValue << "\n";
      std::cout << "firstIndex " << firstIndex << "\n";
      std::cout << "lastIndex " << lastIndex << "\n";
      std::cout << "data.length() " << data.length() << "\n";
      if (found == std::string::npos)
      {
        break;
      }
    }
  }

  return firstValue * 10 + lastValue;
}

int test()
{
  std::cout << "Got " << countV2("eightnine2eightnineeight") << "\n";

  // assert(count("pqr3stu8vwx") == 38);
  // std::cout << "Execution continues past the 1 assert\n";
  // assert(count("treb7uchet") == 77);
  // std::cout << "Execution continues past the 2 assert\n";
  // assert(countV2("7pqrstsixteen") == 76);
  // std::cout << "Execution continues past the 3 assert\n";
  // assert(countV2("eightwothree") == 83);
  // std::cout << "Execution continues past the 4 assert\n";
  // assert(countV2("two1nine") == 29);
  // std::cout << "Execution continues past the 5 assert\n";
  // assert(countV2("eightnine2eightnineeight") == 88);
  // std::cout << "Execution continues past the 6 assert\n";
  // assert(countV2("threeghtcbbllbpnxqxljhnztsx37eight2") == 32);
  // std::cout << "Execution continues past the 7 assert\n";
  // assert(countV2("tg112qhrmt") == 12);
  // std::cout << "Execution continues past the 8 assert\n";

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

  std::string line;
  int sum = 0;
  int sum2 = 0;
  while (std::getline(file, line))
  {
    sum += count(line);
    sum2 += countV2(line);
  }
  std::cout << "The part 1 answer is " << sum << "\n";
  std::cout << "The part 2 answer is " << sum2 << "\n";

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