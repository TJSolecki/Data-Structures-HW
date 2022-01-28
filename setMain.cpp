#include "set.h"

using namespace std;
using namespace main_savitch_10;

int main()
{
  set<int> testo, testbo;
  for(int i = 1; i < 22; i++)
  {
    testo.insert(i);
  }
  for(int i = 22; i < 44; i++)
  {
    testbo.insert(i);
  }
  testo = testbo;
  testo.print(0);
  testbo.erase(30);
  testbo.print(0);
  for(int i = 0; i < 23; i++)
  {
    cout << testo.count(i) << endl;
  }
  for(int i = 0; i > 0; i--)
  {
    testo.erase(i);
    testo.print(0);
  }
  testo.clear();
  testo.print(0);
  cout << testo.empty() << endl;
  cout << testbo.empty() << endl;
  return 0;
}
