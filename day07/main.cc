#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <string_view>
#include <fstream>
#include <ranges>
#include <sstream>
#include <map>
#include <set>

#define VERBOSE

using namespace std;

struct Hand
{
  string cards;
  int value;
};

enum HandType
{
  HighCard = 0,
  OnePair = 1,
  TwoPair = 2,
  ThreeKind = 3,
  FullHouse = 4,
  FourKind = 5,
  FiveKind = 6
};

HandType get_type(string card)
{
  map<char, int> charToCount;
  map<int, int> countToCount;
  for (char c : card)
  {
    charToCount[c]++;
  }

  for (const auto &pair : charToCount)
  {
    countToCount[pair.second]++;
  }

  if (countToCount[5] == 1)
  {
    return FiveKind;
  }

  if (countToCount[4] == 1)
  {
    return FourKind;
  }

  if (countToCount[3] == 1)
  {
    if (countToCount[2] == 1)
    {
      return FullHouse;
    }
    return ThreeKind;
  }

  if (countToCount[2] == 1)
  {
    return OnePair;
  }

  if (countToCount[2] == 2)
  {
    return TwoPair;
  }

  return HighCard;
}

HandType get_best_type(string card)
{
  HandType ht = get_type(card);
  set<char> replacingString;
  for (char c : card)
  {
    if (c != 'J')
    {
      replacingString.insert(c);
    }
  }

  size_t pos = card.find('J');
  if (pos != std::string::npos)
  {
    for (char c : replacingString)
    {
      string newcard(card);
      newcard[pos] = c;
      HandType new_ht = get_best_type(newcard);
      if (new_ht > ht)
      {
        ht = new_ht;
      }
    }
  }

  return ht;
}

bool compare(string card1, string card2)
{
  map<char, int> charToValue = {
      {'A', 0},
      {'K', 1},
      {'Q', 2},
      {'J', 3},
      {'T', 4},
      {'9', 5},
      {'8', 6},
      {'7', 7},
      {'6', 8},
      {'5', 9},
      {'4', 10},
      {'3', 11},
      {'2', 12},
  };
  HandType h1 = get_type(card1);
  HandType h2 = get_type(card2);
  if (h1 == h2)
  {
    for (int i = 0; i < 5; i++)
    {
      if (charToValue[card1[i]] < charToValue[card2[i]])
      {
        return true;
      }
      else if (charToValue[card1[i]] > charToValue[card2[i]])
      {
        return false;
      }
    }
    return true;
  }
  return h1 > h2;
}

bool compare_v2(string card1, string card2)
{
  map<char, int> charToValue = {
      {'A', 0},
      {'K', 1},
      {'Q', 2},
      {'T', 3},
      {'9', 4},
      {'8', 5},
      {'7', 6},
      {'6', 7},
      {'5', 8},
      {'4', 9},
      {'3', 10},
      {'2', 11},
      {'J', 12},
  };
  HandType h1 = get_best_type(card1);
  HandType h2 = get_best_type(card2);
  if (h1 == h2)
  {
    for (int i = 0; i < 5; i++)
    {
      if (charToValue[card1[i]] < charToValue[card2[i]])
      {
        return true;
      }
      else if (charToValue[card1[i]] > charToValue[card2[i]])
      {
        return false;
      }
    }
    return true;
  }
  return h1 > h2;
}

bool compare_hand(Hand h1, Hand h2)
{
  return !compare(h1.cards, h2.cards);
}

bool compare_hand_v2(Hand h1, Hand h2)
{
  return !compare_v2(h1.cards, h2.cards);
}

int solve(vector<string> input)
{
  vector<Hand> hands;
  for (string line : input)
  {
    stringstream ss(line);
    string token;
    Hand h;
    ss >> h.cards;
    ss >> token;
    h.value = stoi(token);
    hands.push_back(h);
  }

  sort(hands.begin(), hands.end(), compare_hand);

  long sum = 0;
  int i = 1;
  for (Hand h : hands)
  {
    cout << "i: " << i << " value: " << h.value << endl;
    sum += i * h.value;
    i++;
  }
  return sum;
}

int solve2(vector<string> input)
{
  vector<Hand> hands;
  for (string line : input)
  {
    stringstream ss(line);
    string token;
    Hand h;
    ss >> h.cards;
    ss >> token;
    h.value = stoi(token);
    hands.push_back(h);
  }

  sort(hands.begin(), hands.end(), compare_hand_v2);

  long sum = 0;
  int i = 1;
  for (Hand h : hands)
  {
    cout << "i: " << i << " value: " << h.value << endl;
    sum += i * h.value;
    i++;
  }
  return sum;
}

int test()
{
  cout << get_best_type("AAAAQ") << endl;
  assert(get_type("AKQJ2") == 0);
  assert(get_type("AAQJ2") == 1);
  assert(get_type("AAQJQ") == 2);
  assert(get_type("AAAJQ") == 3);
  assert(get_type("AAAQQ") == 4);
  assert(get_type("AAAAQ") == 5);
  assert(get_type("AAAAA") == 6);
  assert(get_type("AAAAA") > get_type("AAAAQ") == true);
  assert(get_type("AKQJ2") > get_type("AAAAQ") == false);
  assert(!compare("32T3K", "T55J5"));
  assert(compare("33332", "2AAAA"));
  assert(compare("33332", "33332"));
  assert(compare("77888", "77788"));
  assert(get_best_type("AAAAQ") == 5);
  assert(get_best_type("AAAAJ") == 6);
  assert(get_best_type("AAAJJ") == 6);
  assert(get_best_type("QJJQ2") == 5);
  assert(!compare_v2("JKKK2", "QQQQ2"));
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