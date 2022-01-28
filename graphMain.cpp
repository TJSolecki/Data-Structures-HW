#include <iostream>
#include "graph.h"
#include <vector>

using namespace std;
using namespace main_savitch_15;

int main()
{
  graph<char> myGraph;
  myGraph.add_vertex('A');
  myGraph.add_vertex('B');
  myGraph.add_vertex('C');
  myGraph.add_vertex('D');
  myGraph.add_vertex('E');
  myGraph.add_vertex('F');
  myGraph.add_vertex('G');
  myGraph.add_edge(0, 1);
  //myGraph.add_edge(1, 0);
  myGraph.add_edge(0, 2);
  //myGraph.add_edge(2, 0);

  myGraph.add_edge(2, 1);
  //myGraph.add_edge(1, 2);
  myGraph.add_edge(1, 3);
  //myGraph.add_edge(3, 1);
  myGraph.add_edge(1, 4);
//  myGraph.add_edge(4, 1);
  myGraph.add_edge(4, 3);
//  myGraph.add_edge(3, 4);
  myGraph.add_edge(4, 6);
//  myGraph.add_edge(6, 4);
  myGraph.add_edge(6, 3);
//  myGraph.add_edge(3, 6);
  myGraph.add_edge(3, 5);
//  myGraph.add_edge(5, 3);

  cout << myGraph.longestDistance('A', 'D') << endl;

  return 0;
}
