/* Beginning with an empty binary tree, Construct binary tree by inserting
the values in the order given. After constructing a binary tree perform
following operations on it-
 Perform in order / pre order and post order traversal
 Change a tree so that the roles of the left and right pointers are
swapped at every node
 Find the height of tree
 Copy this tree to another [operator=]
 Count number of leaves, number of internal nodes.
 Erase all nodes in a binary tree.
(implement both recursive and non-recursive methods)*/

#include <iostream>
using namespace std;

template <class T> class Queue {
  T arr[100];
  int rear, front;

public:
  Queue() { rear = front = -1; }

  bool isEmpty() { return front == -1 || front >= rear; }

  void enqueue(T data) {
    if (front == -1) {
      front = 0;
      rear = 1;
      arr[front] = data;
      return;
    }
    arr[rear] = data;
    rear++;
    return;
  }

  T dequeue() {
    if (isEmpty()) {
      cout << "Empty..." << endl;
      return NULL;
    }

    T data = arr[front];
    front++;
    return data;
  }
};

template <class T> class Stack {
  T arr[100];
  int top = -1;

public:
  bool isEmpty() { return top == -1; }

  void push(T data) {
    top++;
    arr[top] = data;
  }

  void pop() { top--; }

  T get_top() { return arr[top]; }
};

class Node {
  int data;
  Node *left, *right;

public:
  Node(int data) {
    this->data = data;
    left = right = NULL;
  }

  friend class BinaryTree;
};

class BinaryTree {
  Node *root;

public:
  BinaryTree() { root = NULL; }

  void insert() {
    Queue<Node *> q;
    int data;
    cout << "Enter root : ";
    cin >> data;

    root = new Node(data);
    q.enqueue(root);

    while (!q.isEmpty()) {
      Node *curr = q.dequeue();

      int data;
      cout << "Enter left child of " << curr->data << " : ";
      cin >> data;

      if (data != -1) {
        curr->left = new Node(data);
        q.enqueue(curr->left);
      }

      cout << "Enter right child of " << curr->data << " : ";
      cin >> data;

      if (data != -1) {
        curr->right = new Node(data);
        q.enqueue(curr->right);
      }
    }
  }

  void inorder() {

    if (root == NULL) {
      cout << "Tree Empty..." << endl;
      return;
    }
    Node *curr = root;

    Stack<Node *> st;

    while (!st.isEmpty() || curr != NULL) {
      while (curr != NULL) {
        st.push(curr);
        curr = curr->left;
      }

      curr = st.get_top();
      st.pop();
      cout << curr->data << " ";
      curr = curr->right;
    }
  }

  void preorder() {
    Stack<Node *> st;

    Node *curr = root;

    while (!st.isEmpty() || curr != NULL) {

      if (curr != NULL) {
        cout << curr->data << " ";
        st.push(curr);
        curr = curr->left;
      } else {
        curr = st.get_top();
        st.pop();
        curr = curr->right;
      }
    }
  }

  void get_height() { cout << "Height = " << height(root) << endl; }

  int height(Node *node) {
    if (node == NULL || node->left == NULL && node->right == NULL) {
      return 0;
    }

    int left = height(node->left);
    int right = height(node->right);

    return max(left, right) + 1;
  }

  void internalNodes() {
    Queue<Node *> q;
    q.enqueue(root);
    int count = 0;

    while (!q.isEmpty()) {
      Node *curr = q.dequeue();
      if (curr->left != NULL || curr->right != NULL) {
        count++;
      }

      if (curr->left != NULL) {
        q.enqueue(curr->left);
      }

      if (curr->right != NULL) {
        q.enqueue(curr->right);
      }
    }

    cout << count << endl;
  }

  void leafNodes() {
    Queue<Node *> q;
    q.enqueue(root);
    int count = 0;

    while (!q.isEmpty()) {
      Node *curr = q.dequeue();

      if (curr->left == NULL && curr->right == NULL) {
        count++;
      }

      if (curr->left != NULL) {
        q.enqueue(curr->left);
      }
      if (curr->right != NULL) {
        q.enqueue(curr->right);
      }
    }

    cout << count << endl;
  }

  void mirror() {
    Node *curr = root;
    Queue<Node *> q;

    q.enqueue(curr);

    while (!q.isEmpty()) {
      curr = q.dequeue();

      Node *temp = curr->left;
      curr->left = curr->right;
      curr->right = temp;

      if (curr->left != NULL) {
        q.enqueue(curr->left);
      }
      if (curr->right != NULL) {
        q.enqueue(curr->right);
      }
    }
  }

  void erase(Node *node) {
    if (node == NULL) {
      return;
    }

    erase(node->left);
    erase(node->right);

    delete node;
  }

  void call_erase() {
    erase(root);
    root = NULL;
  }

  BinaryTree &operator=(BinaryTree &new_tree) {
    root = copyTree(new_tree.root);
    return *this;
  }

  Node *copyTree(Node *node) {
    if (node == NULL) {
      return NULL;
    }

    Node *new_node = new Node(node->data);
    new_node->left = copyTree(node->left);
    new_node->right = copyTree(node->right);

    return new_node;
  }
};

int main() {
  BinaryTree bt;
  bt.insert();
  bt.inorder();
  cout << endl;
  bt.preorder();
  cout << endl;

  bt.internalNodes();

  bt.leafNodes();

  bt.get_height();

  BinaryTree bt1;
  bt1 = bt;

  cout << endl << endl;
  bt1.inorder();

  bt1.call_erase();

  cout << endl << endl;
  bt1.inorder();

  bt.mirror();
  cout << endl;
  bt.inorder();
}
