#include <iostream>
#include "table2.h"
using namespace std;
using namespace main_savitch_12B;

struct bundle
{
  int key;
  string value;
};

int main()
{
  bool found;
  bundle result;
  table<bundle> myTable;
  myTable.insert({1, "one"});
  myTable.insert({812, "two"});
  cout << myTable.is_present(1) << " " << myTable.size() << endl;
  table<bundle> secondTable(myTable);
  secondTable.find(1,found,result);
  cout << found << result.value << endl;
  secondTable = myTable;
  myTable.remove(1);
  secondTable.find(1,found,result);
  cout << found << result.value << endl;
  myTable.find(812,found,result);
  cout << found << result.value << endl;
  myTable.remove(1);
  myTable.find(812,found,result);
  cout << found << result.value << endl;
  myTable.remove(812);
  myTable.find(812,found,result);
  cout << found << result.value << endl;
  myTable.find(1,found,result);
  cout << found << result.value << endl;
  return 0;
}
