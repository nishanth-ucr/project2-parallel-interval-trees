#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "get_time.h"
#include "interval_tree.h"
#include "interval_trees_seq.h"
#include "interval_trees_par.h"
#include "interval_tree_utils.h"

int main(int argc, char* argv[]) {
  Node* root = new Node(15, 30);

  Node* right = new Node(18, 20);
    right->left = new Node(16, 20);
    right->right = new Node(19, 32);
  
  Node* left = new Node(10, 20);
    left->left = new Node(8, 18);
    left->right = new Node(12, 14);
  
      left->left->left = new Node(6, 16);
      left->left->right = new Node(9, 19);
      left->right->left = new Node(11, 26);
      left->right->right = new Node(13, 23);

        left->right->right->right = new Node(14, 24);

  normalize_tree(left);
  normalize_tree(right);
  
  cout << "Left Tree:" << endl;
  print_tree(left);

  cout << "Mid Node:" << endl;
  print_tree(root);

  cout << "Right Tree:" << endl;
  print_tree(right);

  root = join(left, root, right);
  
  cout << "Joined Tree:" <<endl;
  print_tree(root);
  exit(0);
}
