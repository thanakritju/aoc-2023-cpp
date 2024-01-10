#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <map>

#define VERBOSE
using namespace std;

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

int countV1(std::string data)
{
  std::map<std::string, int> map = {{"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}};

  size_t firstIndex = INT_MAX;
  size_t lastIndex = 0;
  size_t firstValue = 0;
  size_t lastValue = 0;
  for (auto const &imap : map)
  {
    std::size_t found = data.find(imap.first);
    do
    {
      if (found <= static_cast<size_t>(firstIndex))
      {
        firstIndex = static_cast<int>(found);
        firstValue = imap.second;
      }
      if (found >= static_cast<size_t>(lastIndex) && found < data.length())
      {
        lastIndex = static_cast<int>(found);
        lastValue = imap.second;
      }

      found = data.find(imap.first, found + 1);
#ifdef VERBOSE
      std::cout << "key " << imap.first << "\n";
      std::cout << "found " << found << "\n";
      std::cout << "firstValue " << firstValue << "\n";
      std::cout << "lastValue " << lastValue << "\n";
      std::cout << "firstIndex " << firstIndex << "\n";
      std::cout << "lastIndex " << lastIndex << "\n";
      std::cout << "data.length() " << data.length() << "\n";
#endif
    } while (found != std::string::npos);
  }

  return firstValue * 10 + lastValue;
}

int countV2(std::string data)
{

  std::cout << "Input: " << data;
  std::map<std::string, int> map = {{"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

  size_t firstIndex = INT_MAX;
  size_t lastIndex = 0;
  size_t firstValue = 0;
  size_t lastValue = 0;
  for (auto const &imap : map)
  {
    std::size_t found = data.find(imap.first);
    do
    {
#ifdef VERBOSE
      std::cout << "key " << imap.first << "\n";
      std::cout << "found " << found << "\n";
      std::cout << "firstValue " << firstValue << "\n";
      std::cout << "lastValue " << lastValue << "\n";
      std::cout << "firstIndex " << firstIndex << "\n";
      std::cout << "lastIndex " << lastIndex << "\n";
      std::cout << "data.length() " << data.length() << "\n";
#endif
      if (found <= static_cast<size_t>(firstIndex))
      {
        firstIndex = static_cast<int>(found);
        firstValue = imap.second;
      }
      if (found >= static_cast<size_t>(lastIndex) && found <= data.length())
      {
        lastIndex = static_cast<int>(found);
        lastValue = imap.second;
      }

      found = data.find(imap.first, found + 1);

    } while (found != std::string::npos);
  }

  std::cout << " Output: " << firstValue * 10 + lastValue << "\n";
  return firstValue * 10 + lastValue;
}

int test()
{
  std::cout << "Got " << countV2("4") << "\n";

  assert(count("pqr3stu8vwx") == 38);
  std::cout << "Execution continues past the 1 assert\n";
  assert(count("treb7uchet") == 77);
  std::cout << "Execution continues past the 2 assert\n";
  assert(countV2("7pqrstsixteen") == 76);
  std::cout << "Execution continues past the 3 assert\n";
  assert(countV2("eightwothree") == 83);
  std::cout << "Execution continues past the 4 assert\n";
  assert(countV2("two1nine") == 29);
  std::cout << "Execution continues past the 5 assert\n";
  assert(countV2("eightnine2eightnineeight") == 88);
  std::cout << "Execution continues past the 6 assert\n";
  assert(countV2("threeghtcbbllbpnxqxljhnztsx37eight2") == 32);
  std::cout << "Execution continues past the 7 assert\n";
  assert(countV2("tg112qhrmt") == 12);
  std::cout << "Execution continues past the 8 assert\n";
  assert(countV2("eightnine2eightnineeight") == 88);
  std::cout << "Execution continues past the 9 assert\n";
  assert(countV2("4r") == 44);
  std::cout << "Execution continues past the 10 assert\n";

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
  int sum2 = 0;
  while (std::getline(file, line))
  {
    sum += count(line);
    sum1 += countV1(line);
    sum2 += countV2(line);
  }
  std::cout << "The part 1.1 answer is " << sum << "\n";
  std::cout << "The part 1.2 answer is " << sum1 << "\n";
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