#include <iostream>
using namespace std;

void update_aug(Node* root) {
  if(root == NULL) return;
  if(root->left == NULL && root->right == NULL) {
    root->height = 1;
    root->max = root->value;
    return;
  }
  if(root->left == NULL) {
    root->height = root->right->height + 1;
    root->max = max(root->right->max, root->value);
    return;
  }
  if(root->right == NULL) {
    root->height = root->left->height + 1;
    root->max = max(root->left->max, root->value);
    return;
  }
  root->height = max(root->left->height, root->right->height) + 1;
  root->max = max(max(root->left->max, root->right->max), root->value);
  return;
}

void normalize_tree(Node* root) {
  if(root == NULL) return;
  normalize_tree(root->left);
  normalize_tree(root->right);
  update_aug(root);
  return;
}

Node * rotate_left(Node* root) {
  Node* right = root->right;
  root->right = right->left;
  right->left = root;
  update_aug(root);
  update_aug(right);
  return right;
}

Node * rotate_right(Node* root) {
  Node* left = root->left;
  root->left = left->right;
  left->right = root;
  update_aug(root);
  update_aug(left);
  return left;
}

Node * join(Node* left, Node* mid, Node* right) {
  if(left == NULL && right == NULL) {
    update_aug(mid);
    return mid;
  }
  int bal = (right != NULL ? right->height : 0)
    - (left != NULL ? left->height : 0);

  if(bal <= -1) {
    left->right = join(left->right, mid, right);
    if(left->get_balance() == 2) {
      if(left->right->get_balance() == -1) {
        left->right = rotate_right(left->right);
      }
      return rotate_left(left);
    } else {
      update_aug(left);
      return left;
    }
  } else if(bal >= 1) {
    right->left = join(left, mid, right->left);
    if(right->get_balance() == -2) {
      if(right->left->get_balance() == 1) {
        right->left = rotate_left(right->left);
      }
      return rotate_right(right);
    } else {
      update_aug(right);
      return(right);
    }
  } else {
    mid->left = left;
    mid->right = right;
    update_aug(mid);
    return mid;
  }
}

Node* insert(Node* root, Node* k) {
  if(root == NULL) {
    update_aug(k);
    return(k);
  }
  Node* root1 = new Node(root->key, root->value);
  if(k->key < root->key)
    return(join(insert(root->left, k), root1, root->right));
  if(k->key > root->key)
    return(join(root->left, root1, insert(root->right, k)));
  return root;
}

class SplitReturnType {
  public:
    Node* l;
    bool found;
    Node* r;
    SplitReturnType(Node* n_l, bool n_found, Node* n_r) {
      l = n_l;
      found = n_found;
      r = n_r;
    }
};

SplitReturnType* split(Node* root, Node* k) {
  if(root == NULL)
    return(new SplitReturnType(NULL, false, NULL));

  Node* root1 = new Node(root->key, root->value);
  Node *l, *r;
  bool found;

  if(k->key < root->key) {
    SplitReturnType *left_split = split(root->left, k);
    l = left_split->l;
    r = join(left_split->r, root1, root->right);
    found = left_split->found;
  } else if(k->key > root->key) {
    SplitReturnType *right_split = split(root->right, k);
    l = join(root->left, root1, right_split->l);
    r = right_split->r;
    found = right_split->found;
  } else {
    l = root->left;
    r = root->right;
    found = true;
  }
  return(new SplitReturnType(l, found, r));
}

SplitReturnType* split_last(Node* root) {
  if(root == NULL)
    return(new SplitReturnType(NULL, false, NULL));
  Node* root1 = new Node(root->key, root->value);
  if(root->right == NULL)
    return(new SplitReturnType(root->left, true, root1));
  SplitReturnType* right_split = split_last(root->right);
  return(new SplitReturnType(
    join(root->left, root1, right_split->l),
    right_split->found,
    right_split->r));
}

Node* join2(Node* left, Node* right) {
  SplitReturnType* last_split = split_last(left);
  return(join(last_split->l, last_split->r, right));
}

Node* delete_node(Node* root, Node* k) {
  if(root == NULL) return root;
  if(k->key < root->key) 
    return(join(
      delete_node(root->left, k),
      new Node(root->key, root->value),
      root->right));
  if(k->key > root->key)
    return(join(
      root->left,
      new Node(root->key, root->value),
      delete_node(root->right, k)));
  return(join2(root->left, root->right));
}

Node* seq_build_sorted(Node* A, size_t n) {
  if(n == 0) return NULL;
  if(n == 1) return A;
  size_t mid = n/2;
  Node *l, *r;
  l = seq_build_sorted(A, mid);
  r = seq_build_sorted(A+mid+1, n-mid-1);
  return join(l, A+mid, r);
}

Node* seq_union(Node* root1, Node* root2) {
  if(root1 == NULL) return root2;
  if(root2 == NULL) return root1;
  Node *l, *r;
  SplitReturnType *left_tree_split = split(root1, root2);
  l = seq_union(left_tree_split->l, root2->left);
  r = seq_union(left_tree_split->r, root2->right);
  return join(l, new Node(root2->key, root2->value), r);
}

Node* seq_intersection(Node* root1, Node* root2) {
  if(root1 == NULL || root2 == NULL) return NULL;
  Node *l, *r;
  SplitReturnType *left_tree_split = split(root1, root2);
  l = seq_intersection(left_tree_split->l, root2->left);
  r = seq_intersection(left_tree_split->r, root2->right);
  if(left_tree_split->found) return(join(l, new Node(root2->key, root2->value), r));
  return(join2(l, r));
}

Node* seq_difference(Node* root1, Node* root2) {
  if(root1 == NULL) return(NULL);
  if(root2 == NULL) return(root1);
  Node *l, *r;
  SplitReturnType *left_tree_split = split(root1, root2);
  l = seq_difference(left_tree_split->l, root2->left);
  r = seq_difference(left_tree_split->r, root2->right);
  return(join2(l, r));
}
