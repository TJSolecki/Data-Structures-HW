#include <iostream>
#include "bintree.h"
#include <vector>
#include <algorithm>
using namespace std;
using namespace main_savitch_10;

template<class Item>
void binTreeToHeap(binary_tree_node<Item>*& root_ptr); // takes in a binary tree and heapafies it
template<class Item, class BTNode>
void inorderInsertVector(vector<Item>& vec, BTNode* node_ptr); // helper function for binTreeToHeap. This function stores the values from a binary tree into a vector
template<class Item>
void vectorToBinNodeHeap(vector<Item> vec, binary_tree_node<Item>*& root_ptr, const size_t index); // helper function for binTreeToHeap. This function takes in a sorted array and returns a complete binary tree which follows the rules of a heap

int main()
{
  binary_tree_node<int>* root_ptr = new binary_tree_node<int>(10);
  root_ptr->set_left(new binary_tree_node<int>(4));
  root_ptr->set_right(new binary_tree_node<int>(1));
  root_ptr->left()->set_right(new binary_tree_node<int>(40));
  root_ptr->left()->right()->set_left(new binary_tree_node<int>(40));
  binTreeToHeap(root_ptr);
  print(root_ptr, 3); // used for testing. The second parameter is the depth of the tree

  return 0;
}

template<class Item>
void vectorToBinNodeHeap(vector<Item> vec, binary_tree_node<Item>*& root_ptr, const size_t index)
{
  if(index >= vec.size()) // checks for base case which is that the index given is not in the vector
  {
    root_ptr = NULL;
    return;
  }
  root_ptr = new binary_tree_node<Item>(vec[index]); // creates new node with the current index of the vector's value
  vectorToBinNodeHeap(vec, root_ptr->left(), index * 2 + 1); // recursive call which creates the left child node
  vectorToBinNodeHeap(vec, root_ptr->right(), index * 2 + 2); // recursive call whihc creates the right child node
}

template<class Item>
void binTreeToHeap(binary_tree_node<Item>*& root_ptr)
{
  if(root_ptr == NULL) return; // in case the binary tree passed in is empty
  vector<Item> vec;
  inorderInsertVector(vec, root_ptr); // stores values inside the binary tree passed in into vec
  tree_clear(root_ptr); // deletes the old tree
  root_ptr = NULL;
  sort(vec.begin(), vec.end()); // sorts the vector from least to greatest
  reverse(vec.begin(), vec.end()); // reverses the vector so that it is now sorted from greatest to least
  vectorToBinNodeHeap(vec, root_ptr, 0); // converts the vector into a binary tree which follows the rules of a heap
}

template<class Item, class BTNode>
void inorderInsertVector(vector<Item>& vec, BTNode* node_ptr) // recursive function that stores the values inside a binary tree into a vector
{
    if (node_ptr != NULL)
    {
        inorderInsertVector(vec, node_ptr->left());
        vec.push_back(node_ptr->data());
        inorderInsertVector(vec, node_ptr->right());
    }
}
