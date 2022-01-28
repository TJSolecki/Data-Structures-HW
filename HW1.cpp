#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

string infixToPrefix(string expression);
string prefixToInfix(string expression);

int main()
{
  int choice = 0;
  string expression;
  bool cont = true;
  while(cont)
  {
    cout << "Would you like to convert infix to prefix or prefix to infix?\nFor prefix to infix enter 1 and for infix to prefix enter 2.\n";
    cin >> choice;
    if(choice == 1)
    {
      cout << "Enter an equation with no spaces and only consisting of letters and math symbols (no spaces)\n";
      cin >> expression;
      string answer2 = prefixToInfix(expression);
      cout << answer2 << endl;
    }
    if(choice == 2)
    {
      cout << "Enter an equation with no spaces and only consisting of letters and math symbols (no spaces)\n";
      cin >> expression;
      string answer = infixToPrefix(expression);
      cout << answer << endl;
    }
    cout << "Would you like to convert another equation? If yes enter 1, if no enter 0.\n";
    cin >> cont;

  }
  //sample input
  /*
  string answer = infixToPrefix("(((a+b)+c)/d)");
  string answer2 = prefixToInfix("/++abcd");
  cout << answer << endl << answer2;
  */
  return 0;
}

string prefixToInfix(string expression)
{
  stack<char> start;
  stack<string> final;
  vector<string> store;
  string symbols = "*/+-", temp;
  for(size_t i = 0; i < expression.size(); i++)
  {
    start.push(expression[i]);
  }
  expression = "";
  while(!start.empty())
  {
    temp = start.top();
    start.pop();
    if(symbols.find(temp) == -1) // if temp is not a symbol
    {
      final.push(temp);
    }
    else // if temp is symbol
    {
      for(size_t i = 0; i < 2; i++)
      {
        store.push_back(final.top());
        final.pop();
      }
      final.push("(" + store[0] + temp + store[1] + ")");
      store.clear();
    }
  }
  while(!final.empty()) // returns data in final stack to the string "expression"
  {
    expression += final.top();
    final.pop();
  }
  return expression;
}

string infixToPrefix(string expression)
{
  string pemdas = ")/*+-"; // used to check if a symbol is the current character in temp
  char temp; // stores the current character being processed
  bool inParen = false; // checks to see if the characters being processed are inside parentheses
  stack<char> start, symbol, final;
  for(size_t i = 0; i < expression.size(); i++) // stores expression passesed in so it can be parsed through in reverse order
  {
    start.push(expression[i]);
  }
  expression = ""; // set to empty string so we can store the answer in it later and return it with the final function
  while(!start.empty())
  {
    temp = start.top();
    start.pop();
    if(temp == ')')
    {
      inParen = true;
    }
    if(pemdas.find(temp) == -1 && temp != '(') // if the character we are currently on is not a math symbol
    {
      final.push(temp);
    }
    else if(pemdas.find(temp) != -1 && temp != '(')
    {
      cout << temp << endl;
      if(symbol.empty())
      {
        symbol.push(temp);
      }
      // these two else if statements make it so that the math symbols are placed in the correct order
      else if(!inParen && (temp == '+' || temp == '-') && (symbol.top() == '+' || symbol.top() == '-' || symbol.top() == '/' || symbol.top() == '*'))
      {
        while(!symbol.empty() && symbol.top() != ')')
        {
          final.push(symbol.top());
          symbol.pop();
        }
        symbol.push(temp);
      }
      else if(!inParen && (temp == '*' || temp == '/') && (symbol.top() == '*' || symbol.top() == '/'))
      {
        while(!symbol.empty())
        {
          final.push(symbol.top());
          symbol.pop();
        }
        symbol.push(temp);
      }
      else
      {
        symbol.push(temp);
      }
    }
    else if(temp == '(') // accounts for if parentheses are used
    {
      while(!symbol.empty() && symbol.top() != ')') // pushes all symbols in the symbol stack onto the final stack excluding the parentheses
      {
        final.push(symbol.top());
        symbol.pop();
      }
      symbol.pop();
      inParen = false;
    }
  }
  while(!symbol.empty()) // if any symbols are left on the stack it pushes them to the final stack
  {
    final.push(symbol.top());
    symbol.pop();
  }
  while(!final.empty()) // puts the data in the final stack in a string to return to the user.
  {
    expression += final.top();
    final.pop();
  }
  return expression;
}
