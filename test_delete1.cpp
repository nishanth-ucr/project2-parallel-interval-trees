#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "get_time.h"
#include "interval_tree.h"
#include "interval_trees_seq.h"
#include "interval_trees_par.h"
#include "interval_tree_utils.h"

int main(int argc, char* argv[]) {
  srand(100);
  size_t n = 10;
  Node* A = (Node*)malloc(n * sizeof(Node));
  for(size_t i = 0; i < n; i++) {
    int key = rand() % 100;
    int value = rand() % 200;
    while(value <= key) {
      value = rand() % 200;
    }
    A[i].key = key;
    A[i].value = value;
    A[i].height = 1;
    A[i].max = value;
  }

  sort(A, A + n, [&](Node a, Node b) {
    return a.key < b.key;
  });

  Node* root = par_build_sorted(A, n);
  cout << "Initial Tree:\n";
  print_tree(root);

  Node* k = new Node(71, 180);
  cout << "Delete Node:\n";
  print_tree(k);

  root = delete_node(root, k);

  cout << "Tree after delete:\n";
  print_tree(root);

  exit(0);
}
