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
  string expression, dummy;
  bool cont = true;
  while(cont)
  {
    cout << "Would you like to convert infix to prefix or prefix to infix?\nFor prefix to infix enter 1 and for infix to prefix enter 2.\n";
    cin >> choice;
    while(choice != 1 && choice != 2) // error handling
    {
      cout << "You did not enter 1 or 2\n";
      cout << "For prefix to infix enter 1 and for infix to prefix enter 2.\n";
      cin >> choice;
    }
    if(choice == 1)
    {
      cout << "Enter a prefix equation\n";
      getline(cin, dummy);
      getline(cin, expression);
      string answer2 = prefixToInfix(expression);
      cout << answer2 << endl;
    }
    if(choice == 2)
    {
      cout << "Enter an infix equation\n";
      getline(cin, dummy);
      getline(cin, expression);
      string answer = infixToPrefix(expression);
      cout << answer << endl;
    }
    cout << "Would you like to convert another equation? If yes enter 1, if no enter 0.\n";
    cin >> choice;
    while(choice != 1 && choice != 0) // error handling
    {
      cout << "You did not enter 1 or 0\n";
      cout << "Please enter 1 to continue the program or 0 to stop\n";
      cin >> choice;
    }
    if(choice == 1) cont = true;
    else cont = false;
  }
  return 0;
}

string prefixToInfix(string expression)
{
  stack<string> start; // stores the initial expression passed in so that it can be easily be read backwards
  stack<string> final; // stores the infix conversion of the expression passed in
  int size = expression.size(), i = 0; // i is used to index through the expression passed in and size is used to prevent multilple calls to expression.size()
  vector<string> store; // this vector is used to store the
  string symbols = "*/+-", temp = "";
  while(size > i) // this while loop stores the expression passed in into the start stack while accounting for spaces and numbers with multiple digits
  {
    if(isdigit(expression[i]))
    {
      while(isdigit(expression[i])) // makes it so that numbers with multiple digits are stored as 1 string
      {
        temp += expression[i];
        i++;
      }
      start.push(temp);
      temp = "";
    }
    else if(expression[i] == ' ') // ignores spaces in input
    {
      i++;
    }
    else // pushes symbols onto stack
    {
      temp = expression[i];
      start.push(temp);
      temp = "";
      i++;
    }
  }
  expression = "";
  while(!start.empty())
  {
    temp = start.top();
    start.pop();
    if(symbols.find(temp) == -1) // checks to see if the current string in temp is symbol. If it isn't it pushes it onto to the final stack
    {
      final.push(temp);
    }
    else // if temp is symbol
    {
      for(size_t i = 0; i < 2; i++) // grabs last two numbers or expressions in the final stack and stores them into a vector
      {
        store.push_back(final.top());
        final.pop();
      }
      final.push("(" + store[0] + temp + store[1] + ")"); // pushes the two numbers or expressions just stored in the vector along with the symbol in temp and some parentheses onto the final stack
      store.clear();
    }
  }
  while(!final.empty()) // returns the data in final stack to the string "expression"
  {
    expression += final.top();
    final.pop();
  }
  return expression;
}

string infixToPrefix(string expression)
{
  string pemdas = ")/*+-"; // used to check if a string is a symbol by using a find function
  string temp = ""; // stores the current character being processed
  int size = expression.size(), i = 0;
  bool inParen = false; // checks to see if the characters being processed are inside parentheses
  stack<string> start, symbol, final;
  while (size > i) // this while loop stores the expression passed in into the start stack while accounting for spaces and numbers with multiple digits
  {
    if (isdigit(expression[i]))
     {
       while (isdigit(expression[i])) // makes it so that numbers with multiple digits are stored as 1 string
       {
         temp += expression[i];
         i++;
       }
       start.push(temp);
       temp = "";
      }
    else if (expression[i] == ' ') // ignores spaces in input
    {
      i++;
    }
    else // pushes symbols onto stack
    {
      temp = expression[i];
      start.push(temp);
      temp = "";
      i++;
    }
  }
  expression = ""; // set to empty string so we can store the answer in it later and return it with the final function
  while(!start.empty())
  {
    temp = start.top();
    start.pop();
    if(temp == ")")
    {
      inParen = true;
    }
    if(pemdas.find(temp) == -1 && temp != "(") // if the character we are currently on is not a math symbol
    {
      final.push(temp);
    }
    else if(pemdas.find(temp) != -1 && temp != "(")
    {
      if(symbol.empty())
      {
        symbol.push(temp);
      }
      // these two else if statements make it so that the math symbols are placed in the correct order
      else if((temp == "+" || temp == "-") && (symbol.top() == "+" || symbol.top() == "-" || symbol.top() == "/" || symbol.top() == "*"))
      {
        while(!symbol.empty() && symbol.top() != ")" && !(symbol.top() == "+" || symbol.top() == "-"))
        {
          final.push(symbol.top());
          symbol.pop();
        }
        symbol.push(temp);
      }
      else if((temp == "*" || temp == "/") && (symbol.top() == "*" || symbol.top() == "/"))
      {
        while(!symbol.empty() && symbol.top() != ")" && !(symbol.top() == "*" || symbol.top() == "/"))
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
    else if(temp == "(") // accounts for if parentheses are used
    {
      while(!symbol.empty() && symbol.top() != ")") // pushes all symbols in the symbol stack onto the final stack excluding the parentheses
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
    expression += final.top() + " ";
    final.pop();
  }
  return expression;
}
