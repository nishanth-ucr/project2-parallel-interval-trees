#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "get_time.h"
#include "interval_tree.h"
#include "interval_trees_seq.h"
#include "interval_trees_par.h"
#include "interval_tree_utils.h"

int main(int argc, char* argv[]) {
  size_t n = 1e7;
  int rounds = 3;

  Node *seq_node_array, *par_node_array;
  double par_total_time = 0, seq_total_time = 0;
  for(int i = 0; i <= rounds; i++) {
    seq_node_array = generate_random_node_array(0, n, n);
    par_node_array = generate_random_node_array(0, n, n);

    parlay::timer seq_t;
    seq_build_sorted(seq_node_array, n);
    seq_t.stop();

    parlay::timer par_t;
    par_build_sorted(par_node_array, n);
    par_t.stop();

    if(i == 0) {
      cout << "Warmup seq running time: " << seq_t.total_time() << endl;
      cout << "Warmup par running time: " << par_t.total_time() << endl;
    } else {
      cout << "Round" << i << " seq running time: " << seq_t.total_time() << endl;
      cout << "Round" << i << " par running time: " << par_t.total_time() << endl;
      seq_total_time += seq_t.total_time();
      par_total_time += par_t.total_time();
    }
    cout << "--------------------------------------" << endl;
  }

  cout << "Average seq running time: " << (seq_total_time / rounds) << endl;
  cout << "Average par running time: " << (par_total_time / rounds) << endl;

  exit(0);
}
