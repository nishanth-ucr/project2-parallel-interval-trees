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

  cout << "Initial Tree:" << endl;
  print_tree(root);

  for(int i = 0; i < 10; i++) {
    int key = rand() % 10000;
    int value = rand() % 20000;
    while(value <= key) {
      value = rand() % 20000;
    }
    root = insert(root, new Node(key, value));
  }
  
  cout << "After Inserting 10 intervals:" << endl;
  print_tree(root);
  exit(0);
}
