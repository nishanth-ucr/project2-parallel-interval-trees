# Project 2 for CS214: Parallel Implementation of Interval Trees
## File Structure
+ ``interval_tree.h`` contains the node representation of interval trees.
+ ``interval_tree_utils.h`` contains utils to print the tree and to generate random interval tree.
+ ``interval_trees_seq.h`` contains all the sequential operations like ```rotations, join, insert, split, split_last, join2, delete_node, seq_build_sorted, seq_union, seq_intersection, seq_difference```.
+ ``interval_trees_par.h`` contains all the parallel operations like ```par_build_sorted, par_union, par_intersection, par_difference, par_filter, par_query```.
+ All other files beginning with ```test_``` has the corresponding testing programs.

## Compiling the Code
A Makefile is given in the directory, simply use ``make`` to compile the code. If you're compiling the code on a M-series Mac, add the ``MXMAC=1`` option:  
```bash
make MXMAC=1  
```
All the executable files from the testing programs will be generated.

## Running the Code
Run each of the executable files to run the corresponding testing programs.
