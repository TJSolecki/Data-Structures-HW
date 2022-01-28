#include <iostream>
#include <string>
#include <stack>
#include "bintree.h"
#include "bag6.h"
using namespace std;
using namespace main_savitch_10;

/* 1.) The equation that calculates the number of possible BSTs of n nodes is called calatan's number. The equation
is: c(n) = the summation from i = 1 to n of (c(n-i)*c(i-1)). We can use recursion to solve this equation and get the
number of possible BSTs with 3 nodes. In this case our base cases would be c(0) = 1 and c(1) = 1. When compute this
the first step to find the answer of c(3) recursivly would be to find c(3-1) which would be c(2). We would then go to
find c(2) which would be c(1) (which is a base case and equals 1) and multiply it by c(0) (which is also a base case
equals 1). Then we would have 1*1 which equals 1. Then we add this to c(2-2) * c(2-1) which equals c(0) * c(1) which
are both base cases and would equal 1 as 1 * 1 = 1. When we add the results we get that c(2) = 2. We then multiply this
by c(1-1) which is c(0) which is a base case and equals 1. We then multiply 2 by 1 and get 2. We then add this 2 to the
product of c(3-2) and c(2-1) which is c(1) * c(1) which are both base cases which equal one so the answer is 1 as 1 * 1 = 1.
We then add this to 2 and get 3. We then add c(3-3) * c(3-1) to 3. c(0) is a base case which equals 1 and c(2) we would
find recursivly like we did before and get 2. We then add 1 * 2 to 3 and get our final answer of 5 possible combinations.
To find the possible amount of combinations for 4 we can use the same recursive technique and we get the answer 14.
*/
binary_tree_node<string>* prefixToTree(string prefix);
void printString(const string& str) { cout << str << " "; } // used to test the prefixToTree function

int main()
{
  inorder(printString, prefixToTree("+ 10 / * 3 5 - 16 4"));
  cout << endl;
  // The rest of the code is testing for the count, insert, and erase functions within the bag class
  bag<int> test;
  test.insert(2);
  test.insert(0);
  test.insert(0);
  test.insert(3);
  test.insert(-1);
  test.insert(0);
  test.insert(0);
  test.insert(-1);
  test.insert(1);
  test.printBag();
  cout << endl;
  cout << "there are " << test.count(0) << " 0(s)" << endl;
  cout << test.erase(0) << " 0(s) erased"<< endl;
  test.printBag();
  cout << endl;
  cout << "there are " << test.count(0) << " 0(s)" << endl;
  return 0;
}

binary_tree_node<string>* prefixToTree(string prefix)
{
  size_t size = prefix.length(), i = 0;
  stack<binary_tree_node<string>*> expressions, final;
  string temp = "";
  while(size > i) // this while loop stores the expression passed into prefix and stores it in a stack called expressions
  {
    if(isdigit(prefix[i]))
    {
      while(isdigit(prefix[i])) // makes it so that numbers with multiple digits are stored as 1 string
      {
        temp += prefix[i];
        i++;
      }
      expressions.push(new binary_tree_node<string>(temp));
      temp = "";
    }
    else if(prefix[i] == ' ') // ignores spaces in input
    {
      i++;
    }
    else // pushes symbols and letters onto the stack
    {
      temp = prefix[i];
      expressions.push(new binary_tree_node<string>(temp));
      temp = "";
      i++;
    }
  }
  while(!expressions.empty()) // processes the data stored in "expressions" and stores it in a final stack
  {
    string test = expressions.top()->data(); // stores the data in the current node from the stack being processed
    if(isdigit(test[0]) || isalpha(test[0])) // pushes numbers and letters onto the final stack
    {
      final.push(expressions.top());
      expressions.pop();
    }
    else // if the item being processed is a symbol the program takes the last two nodes on the final stack and makes them the node with the symbol's children
    {
      expressions.top()->set_left(final.top());
      final.pop();
      expressions.top()->set_right(final.top());
      final.pop();
      final.push(expressions.top());
      expressions.pop();
    }
  }
  return final.top(); // at the end of the program there is only one node left on the final stack and it is the head_ptr to the binary expression tree
}
