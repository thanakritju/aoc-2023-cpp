#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>

#define VERBOSE

int is_special_char(char c)
{
  if (c != '.')
  {
    return 1;
  }
  return 0;
}

int is_part_number(int jstart, int jend, int i, std::array<std::array<char, 140>, 140> arr)
{

#ifdef VERBOSE
  std::cout << "jstart: " << jstart << std::endl;
  std::cout << "jend: " << jend << std::endl;
  std::cout << "i: " << i << std::endl;
#endif

  // upper row
  if (i > 0)
  {
    for (int j = jstart - 1; j <= jend + 1; j++)
    {
      if (j < 0 || j > 139)
      {
        continue;
      }
      if (is_special_char(arr[i - 1][j]))
      {
        return 1;
      }
    }
  }
  // lower row
  if (i < 139)
  {
    for (int j = jstart - 1; j <= jend + 1; j++)
    {
      if (j < 0 || j > 139)
      {
        continue;
      }
      if (is_special_char(arr[i + 1][j]))
      {
        return 1;
      }
    }
  }

  // left
  if (jstart > 0)
  {
    if (is_special_char(arr[i][jstart - 1]))
    {
      return 1;
    }
  }
  // right
  if (jend < 139)
  {
    if (is_special_char(arr[i][jend + 1]))
    {
      return 1;
    }
  }
  return 0;
}

int get_number(int jstart, int jend, std::array<char, 140> arr)
{
  std::string str = "";
  for (int j = jstart; j <= jend; j++)
  {
    str += arr[j];
  }
  return std::stoi(str);
}

std::array<char, 140> parse(std::string line)
{
  std::array<char, 140> arr;
  for (int i = 0; i < 140; ++i)
  {
    arr[i] = '.';
  }
  for (int i = 0; line[i] != '\0'; ++i)
  {
    arr[i] = line[i];
  }
  return arr;
}

int solve(std::vector<std::string> input)
{
  int sum = 0;
  std::array<std::array<char, 140>, 140> arr;
  for (int i = 0; i < 140; ++i)
  {
    if (i < input.size())
    {
      arr[i] = parse(input.at(i));
    }
    else
    {
      arr[i] = parse("");
    }
  }

#ifdef VERBOSE
  std::cout << std::endl;
  for (int i = 0; i < 140; ++i)
  {
    for (int j = 0; j < 140; ++j)
    {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }
#endif

  for (int i = 0; i < 140; ++i)
  {
    int foundDigit = 0;
    int jstart = 0;
    int jend = 0;
    for (int j = 0; j < 140; ++j)
    {
      if (isdigit(arr[i][j]))
      {
        if (!foundDigit)
        {
          jstart = j;
          jend = j;
          foundDigit = 1;
        }
        else
        {
          jend = j;
        }
      }
      else
      {
        if (foundDigit)
        {
          if (is_part_number(jstart, jend, i, arr))
          {
            std::cout << "i " << i << " ";
            std::cout << "get_number " << get_number(jstart, jend, arr[i]) << "\n";
            sum += get_number(jstart, jend, arr[i]);
          }
          foundDigit = 0;
        }
      }
    }
    if (foundDigit)
    {
      if (is_part_number(jstart, jend, i, arr))
      {
        std::cout << "i " << i << " ";
        std::cout << "get_number " << get_number(jstart, jend, arr[i]) << "\n";
        sum += get_number(jstart, jend, arr[i]);
      }
      foundDigit = 0;
    }
  }

  return sum;
}

int solve2(std::vector<std::string> input)
{
  return 0;
}

int test()
{
  std::cout << "get_number " << get_number(5, 7, parse("467..114..")) << "\n";
  std::cout << "get_number " << get_number(0, 2, parse("467..114..")) << "\n";
  assert(get_number(5, 7, parse("467..114..")) == 114);
  assert(get_number(0, 2, parse("467..114..")) == 467);
  std::cout << "get_number " << get_number(137, 139, parse("....136*755...@.950......................173.............95..........+...............2.877.......*668......+..+.........918*.......62....571")) << "\n";
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