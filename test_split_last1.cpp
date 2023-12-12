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

  SplitReturnType *split_res = split_last(root);

  cout << "Split Tree:\n";
  print_tree(split_res->l);
  cout << "Last Node:\n";
  print_tree(split_res->r);
  exit(0);
}
