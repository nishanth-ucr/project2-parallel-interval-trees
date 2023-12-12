#include "parallel.h"

using namespace parlay;

Node* par_build_sorted(Node* A, size_t n) {
  if(n < 1000) {
    return seq_build_sorted(A, n);
  }
  size_t mid = n/2;
  Node *l, *r;
  auto f1 = [&]() {
    l = par_build_sorted(A, mid);
  };
  auto f2 = [&]() {
    r = par_build_sorted(A+mid+1, n-mid-1);
  };
  par_do(f1, f2);
  return join(l, A+mid, r);
}

Node* par_union(Node* root1, Node* root2) {
  if(root1 == NULL) return root2;
  if(root2 == NULL) return root1;
  if(root1->height + root2->height < 1000) {
    return seq_union(root1, root2);
  }
  Node *l, *r;
  SplitReturnType *left_tree_split = split(root1, root2);
  auto f1 = [&]() {
    l = par_union(left_tree_split->l, root2->left);
  };
  auto f2 = [&]() {
    r = par_union(left_tree_split->r, root2->right);
  };
  par_do(f1, f2);
  return join(l, new Node(root2->key, root2->value), r);
}

Node* par_intersection(Node* root1, Node* root2) {
  if(root1 == NULL || root2 == NULL) return NULL;
  if(root1->height + root2->height < 1000) {
    return seq_intersection(root1, root2);
  }
  Node *l, *r;
  SplitReturnType *left_tree_split = split(root1, root2);
  auto f1 = [&]() {
    l = par_intersection(left_tree_split->l, root2->left);
  };
  auto f2 = [&]() {
    r = par_intersection(left_tree_split->r, root2->right);
  };
  par_do(f1, f2);
  if(left_tree_split->found)
    return(join(l, new Node(root2->key, root2->value), r));
  return(join2(l, r));
}

Node* par_difference(Node* root1, Node* root2) {
  if(root1 == NULL) return(NULL);
  if(root2 == NULL) return(root1);
  if(root1->height + root2->height < 1000) {
    return seq_difference(root1, root2);
  }
  Node *l, *r;
  SplitReturnType *left_tree_split = split(root1, root2);
  auto f1 = [&]() {
    l = par_difference(left_tree_split->l, root2->left);
  };
  auto f2 = [&]() {
    r = par_difference(left_tree_split->r, root2->right);
  };
  par_do(f1, f2);
  return(join2(l, r));
}

Node* par_filter(
  Node* root,
  function<bool(Node*)> ignore_node,
  function<bool(Node*)> ignore_tree) {

  if(root == NULL) return root;
  if(ignore_tree(root))
    return NULL;

  Node *l, *r;  
  auto f1 = [&]() {
    l = par_filter(root->left, ignore_node, ignore_tree);
  };
  auto f2 = [&]() {
    r = par_filter(root->right, ignore_node, ignore_tree);
  };
  par_do(f1, f2);

  if(ignore_node(root))
    return(join2(l, r));

  return(join(l, new Node(root->key, root->value), r));
}

Node* par_query(Node* root, long long low, long long high) {
  SplitReturnType *root_split = split(root, new Node(high, high+1));
  return par_filter(
    root_split->l,
    [&low](Node* node) -> bool {
      return(node->value <= low);
    },
    [&low](Node* node) -> bool {
      return(node->max <= low);
    }
  );
}

// Node* par_multi_insert(Node* root, Node* A, size_t n) {
//   if(root == NULL) return(par_build_sorted(A, n));
//   if(n == 0) return(root);
//   size_t m = binary_search(A, n, root);
//   Node *l, *r;
//   auto f1 = [&]() { l = par_multi_insert(root->left, A, m); };
//   auto f2 = [&]() { r = par_multi_insert(root->right, A + m, n - m); };
//   par_do(f1, f2);
//   return(join(l, new Node(root->key, root->value), r));
// }
