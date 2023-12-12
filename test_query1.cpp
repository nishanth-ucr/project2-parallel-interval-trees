#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "get_time.h"
#include "interval_tree.h"
#include "interval_trees_seq.h"
#include "interval_trees_par.h"
#include "interval_tree_utils.h"

int main(int argc, char* argv[]) {
  size_t n = 7;
  Node* A = (Node*)malloc(n * sizeof(Node));
  A[0] = *(new Node(10, 18));
  A[1] = *(new Node(8, 13));
  A[2] = *(new Node(12, 16));
  A[3] = *(new Node(7, 9));
  A[4] = *(new Node(9, 11));
  A[5] = *(new Node(11, 14));
  A[6] = *(new Node(15, 21));

  sort(A, A + n, [&](Node a, Node b) {
    return a.key < b.key;
  });

  Node* root = par_build_sorted(A, n);

  cout << "Initial Tree:\n";
  print_tree(root);
 
  root = par_query(root, 11, 13);

  cout << "Queried tree:\n";
  print_tree(root);

  exit(0);
}
