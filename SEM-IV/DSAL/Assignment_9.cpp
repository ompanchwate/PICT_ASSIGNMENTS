/* AVL Tree */

#include <iostream>
using namespace std;

class Node {
  int val;
  Node *right;
  Node *left;

public:
  Node() {
    val = 0;
    right = NULL;
    left = NULL;
  }
  Node(int v) {
    val = v;
    left = NULL;
    right = NULL;
  }
  friend class AVL;
};

class AVL {
  Node *root;

public:
  AVL() { root = NULL; }

  Node *get_root() { return root; }

  void set_root(Node *root) { this->root = root; }

  // balancing height of tree
  int find_height(Node *root) {
    if (root == NULL)
      return 0;

    int left_height = find_height(root->left);
    int right_height = find_height(root->right);

    return max(left_height, right_height) + 1;
  }

  int difference(Node *node) {

    int left_height = find_height(node->left);
    int right_height = find_height(node->right);

    return left_height - right_height;
  }

  Node *ll_rotate(Node *node) {

    Node *temp_root = node->left;

    node->left = temp_root->right;
    temp_root->right = node;

    return temp_root;
  }

  Node *rr_rotate(Node *node) {

    Node *temp_root = node->right;

    node->right = temp_root->left;
    temp_root->left = node;

    return temp_root;
  }

  Node *lr_rotate(Node *node) {

    Node *temp_root = node->left->right;
    Node *temp_root_left = temp_root->left;
    Node *temp_root_right = temp_root->right;

    temp_root->left = node->left;
    temp_root->right = node;

    temp_root->left->right = temp_root_left;
    temp_root->right->left = temp_root_right;

    return temp_root;
  }

  Node *rl_rotate(Node *node) {

    Node *temp_root = node->right->left;
    Node *temp_root_left = temp_root->left;
    Node *temp_root_right = temp_root->right;

    temp_root->left = node;
    temp_root->right = node->right;

    temp_root->left->right = temp_root_left;
    temp_root->right->left = temp_root_right; // YET to be edited

    return temp_root;
  }

  Node *balance(Node *t) {
    int bal_fac = difference(t);
    if (bal_fac > 1) {
      if (difference(t->left) > 0) {
        t = ll_rotate(t);
      } else
        t = lr_rotate(t);
    } else if (bal_fac < -1) {
      if (difference(t->right) > 0)
        t = rl_rotate(t);
      else
        t = rr_rotate(t);
    }
    return t;
  }

  // insert
  Node *insert(Node *root, int value) {
    if (root == NULL) {
      root = new Node(value);
      return root;
    } else if (root->val > value) {
      root->left = insert(root->left, value);
      root = balance(root);
    } else if (root->val < value) {
      root->right = insert(root->right, value);
      root = balance(root);
    }
    return root;
  }

  // inorder traversal
  void inorder(Node *n) {
    if (n == NULL) {
      return;
    }
    inorder(n->left);
    cout << n->val << " ";
    inorder(n->right);
  }

  void preorder(Node *n) {
    if (n == NULL) {
      return;
    }
    cout << n->val << " ";
    preorder(n->left);
    preorder(n->right);
  }
  void postorder(Node *t) {
    if (t == NULL) {
      return;
    }
    postorder(t->left);
    postorder(t->right);
    cout << t->val << " ";
  }
};

int main() {
  AVL b;
  int ch, k, keyCnt, key;
  do {
    cout << endl
         << endl
         << "Menu" << endl
         << "1. Insert" << endl
         << "2. Inorder" << endl
         << "3. Preorder" << endl
         << "4. Postorder" << endl
         << "5. Exit" << endl;
    cout << "Enter you choice: ";
    cin >> ch;

    switch (ch) {
    case 1:
      cout << "\nINSERTION\n";
      cout << "Enter key to insert:";
      cin >> key;

      b.set_root(b.insert(b.get_root(), key));
      break;
    case 2:
      cout << "\nINORDER\n";
      b.inorder(b.get_root());
      break;
    case 3:
      cout << "\nPREORDER\n";
      b.preorder(b.get_root());
      break;
    case 4:
      cout << "\nPOSTORDER\n";
      b.postorder(b.get_root());
      break;
    case 5:
      cout << "\nEXITED!!!!";
      break;
    default:
      cout << "Wrong choice entered!!!!";
      break;
    }
  } while (ch != 5);

  //	cout<<"Hello World";
}