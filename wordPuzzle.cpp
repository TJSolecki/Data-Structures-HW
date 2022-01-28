#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct location
{
  int x;
  int y;
};

struct bundle
{
  string str;
  location start;
  location end;
};

void isWord(bundle bun, const unordered_set<string>& dictionary, int horiOrVeri, vector<bundle>& answers)
{
  bundle reverse = bun;
  location temp = bun.start;
  reverse.start = reverse.end;
  reverse.end = temp;
  //reverses str in reverse bundle
  for(int i = 0; i < reverse.str.length()/2; i++)
  {
    swap(reverse.str[i], reverse.str[reverse.str.length()-i-1]);
  }
  for(string word : dictionary)
  {
    if(word.length() >= 6 && bun.str.find(word) != string::npos)
    {
      cout << "found answer!\n";
      int indexStart = bun.str.find(word);
      int indexEnd = indexStart + word.length() - 1;
      if(horiOrVeri == 1) answers.push_back({word, {indexStart,bun.start.y}, {indexEnd,bun.end.y}});
      if(horiOrVeri == 2) answers.push_back({word, {bun.start.x,indexStart}, {bun.end.x,indexEnd}});
    }
    if(word.length() >= 6 && reverse.str.find(word) != string::npos)
    {
      cout << "found answer!\n";
      string temp2 = word;
      for(int i = 0; i < temp2.length()/2; i++)
      {
        swap(temp2[i], temp2[temp2.length()-i-1]);
      }
      int indexStart = bun.str.find(temp2);
      int indexEnd = indexStart + word.length() - 1;
      int endDiff = (bun.str.length() - 1) - indexEnd;
      if(horiOrVeri == 1) answers.push_back({word, {indexEnd,bun.end.y}, {indexStart,bun.start.y}});
      if(horiOrVeri == 2) answers.push_back({word, {bun.end.x ,indexEnd}, {bun.start.x,indexStart}});
    }
  }
}

void isWordDiag(bundle bun, const unordered_set<string>& dictionary, int LRorRL, vector<bundle>& answers)
{
  string reverseStr = bun.str;
  for(int i = 0; i < reverseStr.length()/2; i++)
  {
    swap(reverseStr[i], reverseStr[reverseStr.length()-i-1]);
  }
  for(string word : dictionary)
  {
    if(word.length() >= 6 && bun.str.find(word) != string::npos)
    {
      cout << "found answer!\n";
      int indexStart = bun.str.find(word);
      int indexEnd = indexStart + word.length() - 1;
      int endDiff = (bun.str.length() - 1) - indexEnd;
      if(LRorRL == 1) answers.push_back({word, {bun.start.x+indexStart,bun.start.y-indexStart}, {bun.end.x-endDiff,bun.end.y+endDiff}});
      if(LRorRL == 2) answers.push_back({word, {bun.start.x+indexStart,bun.start.y+indexStart}, {bun.end.x-endDiff,bun.end.y-endDiff}});
    }
    if(word.length() >= 6 && reverseStr.find(word) != string::npos)
    {
      cout << "found answer!\n";
      string temp2 = word;
      for(int i = 0; i < temp2.length()/2; i++)
      {
        swap(temp2[i], temp2[temp2.length()-i-1]);
      }
      int indexStart = bun.str.find(temp2);
      int indexEnd = indexStart + word.length() - 1;
      int endDiff = (bun.str.length() - 1) - indexEnd;
      if(LRorRL == 1) answers.push_back({word, {bun.end.x-endDiff,bun.end.y+endDiff}, {bun.start.x+indexStart,bun.start.y-indexStart}});
      if(LRorRL == 2) answers.push_back({word, {bun.end.x-endDiff,bun.end.y-endDiff}, {bun.start.x+indexStart,bun.start.y+indexStart}});
    }
  }
}

int main()
{
  //Storing dictionary in an unordered_set
  unordered_set<string> dictionary;
  ifstream dict;
  dict.open("words.txt");
  string temp;
  while(dict >> temp)
  {
    dictionary.insert(temp);
  }

  //Getting N and M
  ifstream puz;
  char temp2;
  int n = 0, m = 0;
  puz.open("puzzle.txt");
  getline(puz, temp);
  m++;
  for(int i = 0; i < temp.length(); i++)
  {
    if(isalpha(temp[i])) n++;
  }
  while(!puz.eof())
  {
    getline(puz, temp);
    m++;
  }
  puz.close();
  cout << "N = " << n << ", M = " << m << endl;
  //Storing puzzle in 2d array
  char table[n][m];
  puz.open("puzzle.txt");
  temp2 = ' ';
  for(int i = 0; i < m; i++)
  {
    for(int j = 0; j < n; j++)
    {
      puz.get(temp2);
      while(!isalpha(temp2))
      {
        puz.get(temp2);
      }
      table[i][j] = temp2;
    }
  }
  vector<bundle> answers;
  for(int i = 0; i < n; i++)
  {
    temp = "";
    for(int j = 0; j < m ; j++)
    {
      temp += table[i][j];
    }
    if(temp.length() >= 6)
    {
      //verticalStrings.push_back({temp, {i,0}, {i, m-1}});
      bundle curr = {temp, {i,0}, {i, m-1}};
      isWord(curr, dictionary, 2, answers);
    }
  }

  for(int i = 0; i < m; i++)
  {
    temp = "";
    for(int j = 0; j < n; j++)
    {
      temp += table[j][i];
    }
    if(temp.length() >= 6)
    {
      bundle curr = {temp, {0, i}, {n-1, i}};
      isWord(curr, dictionary, 1, answers);
    }
  }
  // checks diagonals (not working yet, all it does is print them out)
  for(int i = m-1; i >= 0; i--)
  {
    int i2 = i;
    int j = 0;
    temp = "";
    while(j < n && i2 >= 0)
    {
      temp += table[j++][i2--];
    }
    if(temp.length() >= 6) isWordDiag({temp, {0,i}, {j-1, 0}}, dictionary, 1, answers);
    else i = -1;
  }
  for(int i = 1; i < n; i++)
  {
    int i2 = i;
    int j = m-1;
    temp = "";
    while(j >= 0 && i2 < n)
    {
      temp += table[i2++][j--];
    }
    if(temp.length() >= 6) isWordDiag({temp, {i, m-1}, {i2-1, j+1}}, dictionary, 1, answers);
    else i = n;
  }

  for(int i = 0; i < n; i++)
  {
    int i2 = i;
    int j = 0;
    temp = "";
    while(i2 < n && j < m)
    {
      temp += table[i2++][j++];
    }
    if(temp.length() >= 6) isWordDiag({temp, {i, 0}, {n-1, j-1}}, dictionary, 2, answers);
    else i = n;
  }
  for(int i = 1; i < m; i++)
  {
    int i2 = i; // i2 is y
    int j = 0; // j is x
    temp = "";
    while(i2 < m && j < n)
    {
      temp += table[j++][i2++];
    }
    if(temp.length() >= 6) isWordDiag({temp, {0, i}, {j-1, i2-1}}, dictionary, 2, answers);
    else i = m;
  }
  cout << "Answers:\n";
  vector<string> sortedAnswers;
  for(bundle i : answers) sortedAnswers.push_back(i.str + ", from (" + to_string(i.start.x) + ", " + to_string(i.start.y) + ") to (" + to_string(i.end.x) + ", " + to_string(i.end.y) + ")");
  sort(sortedAnswers.begin(), sortedAnswers.end());
  for(string str : sortedAnswers) cout << str << endl;
  cout << endl;

  return 0;
}
