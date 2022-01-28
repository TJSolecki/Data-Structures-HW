#include <iostream>
#include "doubletsGraph.h"
#include <unordered_set>
#include <fstream>

using namespace std;
using namespace main_savitch_15;

void solve(string first, string second, const unordered_set<string>& dictionary);

int main()
{
  unordered_set<string> dictionary;
  ifstream in;
  in.open("knuth.txt");
  string temp;
  while(in >> temp) dictionary.insert(temp);
  in.close();
  solve("black","white", dictionary);
  cout << endl;
  solve("tears", "smile", dictionary);
  cout << endl;
  solve("small", "giant", dictionary);
  cout << endl;
  solve("stone", "money", dictionary);
  cout << endl;
  solve("amigo", "signs", dictionary);
  cout << endl;
  solve("amino", "right", dictionary);
  cout << endl;
  solve("angel", "devil", dictionary);
  return 0;
}

void solve(string first, string second, const unordered_set<string>& dictionary)
{
  graph<string> connections;
  unordered_set<string> used;
  vector<string> next;
  next.push_back(first);
  connections.add_vertex(first);
  used.insert(first);
  bool done = false;
  for(int i = 0; i < next.size(); i++)
  {
    string curr = next[i];

    for(string str : dictionary)
    {
      if(str != curr && !done)
      {
        int numMatch = 0;
        for(int j = 0; j < 5; j++)
        {
          if(curr[j] == str[j]) numMatch++;
        }
        if(numMatch == 4)
        {
          if(used.find(str) == used.end())
          {
            used.insert(str);
            next.push_back(str);
            connections.add_vertex(str);
            connections.add_edge(curr, str);
            connections.add_edge(str, curr);
          }
          if(str == second)
          {
            done = true;
            i = next.size() + 1;
          }
        }
      }

    }
  }
  if(!done)
  {
    cout << "There are no solutions for " << first << " and " << second << endl;
    return;
  }
  vector<string> result = connections.shortest_path(first, second);
  for(string i : result)
  {
    cout << i << endl;
  }
}
