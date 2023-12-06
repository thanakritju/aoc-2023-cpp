#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>

int count(std::string_view data)
{
  return 77;
}

int test()
{
  assert(count("treb7uchet") == 77);
  std::cout << "Execution continues past the first assert\n";
  assert(count("pqr3stu8vwx") == 38);
  std::cout << "Execution continues past the second assert\n";
  assert(count("a1b2c3d4e5f") == 15);
  std::cout << "Execution continues past the third assert\n";
  assert(count("1abc2") == 12);
  std::cout << "Execution continues past the forth assert\n";
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
  while (std::getline(file, line))
  {
    std::cout << line << " ";
  }
  std::cout << "\n";
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