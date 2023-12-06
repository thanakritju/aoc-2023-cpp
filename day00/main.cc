#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>

int test()
{
  assert(1);
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