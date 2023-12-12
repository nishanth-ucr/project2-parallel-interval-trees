class Node {
  public:
    long long key;
    long long value;
    long long max;
    long long height;
    Node* left;
    Node* right;
    Node(long long n_key, long long n_value) {
      key = n_key;
      value = n_value;
      max = n_value;
      height = 1;
    }
    Node(long long n_key, long long n_value, long long n_max) {
      key = n_key;
      value = n_value;
      max = n_max;
      height = 1;
    }
    Node(long long n_key, long long n_value, long long n_max, long long n_height) {
      key = n_key;
      value = n_value;
      max = n_max;
      height = n_height;
    }
    long long get_balance() {
      return((right != NULL ? right->height : 0) - (left != NULL ? left->height : 0));
    }
};
