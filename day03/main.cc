#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>

// #define VERBOSE

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

int get_number(int i, std::array<char, 140> arr)
{
  std::string str = "";
  if (!isdigit(arr[i]))
  {
    return 0;
  }
  else
  {
    str += arr[i];
    int iright = i + 1;
    int ileft = i - 1;
    while (isdigit(arr[iright]))
    {
      str = str + arr[iright];
      iright += 1;
    }
    while (isdigit(arr[ileft]))
    {
      str = arr[ileft] + str;
      ileft -= 1;
    }
  }
  return std::stoi(str);
}

int get_number(int i, int j, std::array<std::array<char, 140>, 140> arr)
{
#ifdef VERBOSE
  std::cout << "\nget_number" << std::endl;
  std::cout << "i " << i << std::endl;
  std::cout << "j " << j << std::endl;
#endif
  return get_number(j, arr[i]);
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
#ifdef VERBOSE
            std::cout << "i " << i << " ";
            std::cout << "get_number " << get_number(jstart, jend, arr[i]) << "\n";
#endif
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

#ifdef VERBOSE
        std::cout << "i " << i << " ";
        std::cout << "get_number " << get_number(jstart, jend, arr[i]) << "\n";
#endif
        sum += get_number(jstart, jend, arr[i]);
      }
      foundDigit = 0;
    }
  }

  return sum;
}

int is_gear(char c)
{
  if (c == '*')
  {
    return 1;
  }
  return 0;
}

int find_numbers(int i, int j, std::array<std::array<char, 140>, 140> arr)
{
  int count = 0;
  int ans = 1;
  // left
  if (j - 1 >= 0 && get_number(i, j - 1, arr))
  {
    count += 1;
    ans *= get_number(i, j - 1, arr);
  }
  // right
  if (j + 1 < 140 && get_number(i, j + 1, arr))
  {
    count += 1;
    ans *= get_number(i, j + 1, arr);
  }

  // bottom
  if (i + 1 < 140)
  {
    if (isdigit(arr[i + 1][j]))
    {
      if (get_number(i + 1, j, arr))
      {
        count += 1;
        ans *= get_number(i + 1, j, arr);
      }
    }
    else
    {
      if (j - 1 >= 0 && isdigit(arr[i + 1][j - 1]) && get_number(i + 1, j - 1, arr))
      {
        count += 1;
        ans *= get_number(i + 1, j - 1, arr);
      }

      if (j + 1 < 140 && isdigit(arr[i + 1][j + 1]) && get_number(i + 1, j + 1, arr))
      {
        count += 1;
        ans *= get_number(i + 1, j + 1, arr);
      }
    }
  }
  // top
  if (i - 1 >= 0)
  {
    if (isdigit(arr[i - 1][j]))
    {
      if (get_number(i - 1, j, arr))
      {
        count += 1;
        ans *= get_number(i - 1, j, arr);
      }
    }
    else
    {
      if (j - 1 >= 0 && isdigit(arr[i - 1][j - 1]) && get_number(i - 1, j - 1, arr))
      {
        count += 1;
        ans *= get_number(i - 1, j - 1, arr);
      }

      if (j + 1 < 140 && isdigit(arr[i - 1][j + 1]) && get_number(i - 1, j + 1, arr))
      {
        count += 1;
        ans *= get_number(i - 1, j + 1, arr);
      }
    }
  }
#ifdef VERBOSE
  std::cout << "\nfound gear" << std::endl;
  std::cout << "i " << i << std::endl;
  std::cout << "j " << j << std::endl;
  std::cout << "count " << count << std::endl;
  std::cout << "ans " << ans << std::endl;
#endif
  if (count == 2)
  {
    return ans;
  }
  return 0;
}

int solve2(std::vector<std::string> input)
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
  for (int i = 0; i < 140; ++i)
  {
    for (int j = 0; j < 140; ++j)
    {
      if (is_gear(arr[i][j]))
      {
        sum += find_numbers(i, j, arr);
      }
    }
  }

  return sum;
}

int test()
{
  std::cout << "get_number " << get_number(5, 7, parse("467..114..")) << "\n";
  std::cout << "get_number " << get_number(0, 2, parse("467..114..")) << "\n";
  assert(get_number(5, 7, parse("467..114..")) == 114);
  assert(get_number(0, 2, parse("467..114..")) == 467);
  assert(get_number(0, 2, parse("467..114..")) == 467);
  assert(get_number(0, parse("467..114..")) == 467);
  assert(get_number(1, parse("467..114..")) == 467);
  assert(get_number(2, parse("467..114..")) == 467);
  assert(get_number(3, parse("467..114..")) == 0);
  assert(get_number(5, parse("467..114..")) == 114);
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