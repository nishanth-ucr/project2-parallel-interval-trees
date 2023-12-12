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
  size_t n = 6;
  int key, value;
  Node* A = (Node*)malloc(n * sizeof(Node));
  Node* B = (Node*)malloc(n * sizeof(Node));
  for(size_t i = 0; i < 3*n/2; i++) {
    key = rand() % 100;
    value = rand() % 200;
    while(value <= key) {
      value = rand() % 200;
    }
    if(i < n) {
      A[i].key = key;
      A[i].value = value;
      A[i].height = 1;
      A[i].max = value;
    }

    if(i >= n/2) {
      B[i - n/2].key = key;
      B[i - n/2].value = value;
      B[i - n/2].height = 1;
      B[i - n/2].max = value;
    }
  }

  sort(A, A + n, [&](Node a, Node b) {
    return a.key < b.key;
  });

  sort(B, B + n, [&](Node a, Node b) {
    return a.key < b.key;
  });

  Node* root1 = par_build_sorted(A, n);
  Node* root2 = par_build_sorted(B, n);

  cout << "\nInitial Left Tree:\n";
  print_tree(root1);

  cout << "\nInitial Right Tree:\n";
  print_tree(root2);

  Node* root = par_union(root1, root2);

  cout << "\nJoined Tree:\n";
  print_tree(root);

  exit(0);
}
