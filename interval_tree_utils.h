#include <iostream>
using namespace std;

void print_tree(Node* root, int left_padding = 0) {
  if(root == NULL) return;
  for(int i = 0; i< left_padding; i++) cout << "| ";
  cout << "[" << root->key << ", " << root->value << "] ";
  cout << "max: " << root->max << ", ";
  cout << "height: " << root->height << ", ";
  cout << "balance: " << root->get_balance() << endl;
  for(int i = 0; i< left_padding; i++) cout << "| ";
  cout << (root->left != NULL ? "| " : "  ");
  cout << (root->right != NULL ? "\\" : "") << endl;
  print_tree(root->right, left_padding + 1);
  print_tree(root->left, left_padding);
}

Node* generate_random_node_array(size_t min_start, size_t max_start, size_t n, size_t step = 1) {
    size_t* min_array = (size_t*)malloc(n * sizeof(size_t));
    size_t* max_array = (size_t*)malloc(n * sizeof(size_t));
    for(size_t i = 0; i < n; i++) {
        min_array[i] = min_start + step * i;
        max_array[i] = max_start + step * i;
    }
    // random_shuffle(max_array[0], max_array[n-1]);
    Node* node_array = (Node*)malloc(n * sizeof(Node));
    for(size_t i = 0; i < n; i++) {
        node_array[i].key = min_array[i];
        node_array[i].value = max_array[i];
        update_aug(&node_array[i]);
    }
    return node_array;
}