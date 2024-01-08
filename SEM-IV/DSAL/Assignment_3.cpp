// ThreadedBinaryTree | Deletion not working properly 
/*Create an inordered threaded binary search tree. Perform inorder,
preorder traversals without recursion and deletion of a node. Analyze
time and space complexity of the algorithm.
*/

#include <iostream>
using namespace std;

// 0 = False = child
// 1 = True = Thread

class Node {
public:
  int data;
  bool lthread, rthread;
  Node *left;
  Node *right;
  Node(int data) {
    this->data = data;
    lthread = rthread = true;
    left = right = NULL;
  }
};

class ThreadedBinaryTree {
public:
  Node *root;
  ThreadedBinaryTree() { root = NULL; }

  /*---INSERTION---*/
  void insertNode(int data) {
    // First Node
    if (root == NULL) {
      root = new Node(data);
      return;
    }

    Node *current = root;
    Node *parent = NULL;

    while (current != NULL) {
      parent = current;
      Node *newNode = new Node(data); // Created new Node

      if (data < current->data) {
        // If lthread is a child then just move left
        if (current->lthread == false) {
          current = current->left;
        } else {
          newNode->left = parent->left;
          newNode->right = parent;
          parent->left = newNode;
          parent->lthread = false;
        }
      } else if (data > current->data) {
        // if 0 then move right
        if (current->rthread == false) {
          current = current->right;
        } else {
          newNode->left = parent;
          newNode->right = parent->right;
          parent->right = newNode;
          parent->rthread = false;
        }
      } else {
        return;
      }
    }
  }

  Node *inorderSuccessor(Node *current) {
    // If there's a thread
    if (current->rthread) {
      return current->right;
    } else {
      // Go right
      current = current->right;
      // after right, traverse through the left
      while (!current->lthread) {
        current = current->left;
      }
      return current;
    }
  }

  void inorder() {
    Node *current = root;
    // Traverse to the leftmost node
    while (current->lthread == false) {
      current = current->left;
    }

    // Print nodes in ascending order
    while (current != NULL) {
      cout << current->data << " ";
      current = inorderSuccessor(current);
    }
  }

  void preorder() {
    if (root == NULL) {
      return;
    }

    Node *curr = root;

    while (curr != NULL) {
      cout << curr->data << " ";

      if (!curr->lthread) {
        curr = curr->left;
      } else { // All about RIGHT
        if (!curr->rthread) {
          curr = curr->right;
        } else {
          while (curr != NULL && (curr->lthread || curr->rthread)) {
            if (curr->rthread) {
              curr = curr->right;
            } else {
              curr = curr->left;
            }
          }
        }
        if (curr != NULL) {
          curr = curr->right;
        }
      }
    }
  }

  void deleteNode(int key) {
    Node *current = root;
    Node *parent = nullptr;
    bool found = false;

    // Find the node to be deleted
    while (current != nullptr) {
      if (key == current->data) {
        found = true;
        break;
      }

      parent = current;

      if (key < current->data) {
        if (current->lthread) {
          break;
        }
        current = current->left;
      } else {
        if (current->rthread) {
          break;
        }
        current = current->right;
      }
    }

    if (!found) {
      cout << "Node with key " << key << " not found." << endl;
      return;
    }

    // Case 1: Node to be deleted is a leaf node
    if (current->lthread && current->rthread) {
      if (parent == nullptr) {
        root = nullptr;
        // If curr is a left child
      } else if (current == parent->left) {
        parent->lthread = true;
      } else { // If curr is right child
        parent->rthread = true;
      }
      delete current;
    }
    // Case 2: Node to be deleted has a single child
    else if (current->lthread) {
      Node *successor = current->right;
      Node *predecessor = current;
      while (!successor->lthread) {
        predecessor = successor;
        successor = successor->left;
      }

      current->data = successor->data;
      if (successor->rthread) {
        current->right = successor->right;
        current->rthread = true;
      } else {
        predecessor->left = successor->right;
      }

      delete successor;
    } else if (current->rthread) {
      Node *successor = current->left;
      Node *predecessor = current;
      while (!successor->rthread) {
        predecessor = successor;
        successor = successor->right;
      }

      current->data = successor->data;
      if (successor->lthread) {
        current->left = successor->left;
        current->lthread = true;
      } else {
        predecessor->left = successor->left;
      }
      delete successor;
    }
    // Case 3: Node to be deleted has two children
    else {
      Node *successor = current->right;
      Node *parentSuccessor = current;
      while (!successor->lthread) {
        parentSuccessor = successor;
        successor = successor->left;
      }

      current->data = successor->data;

      if (successor->rthread) {
        if (parentSuccessor == current) {
          parentSuccessor->right = successor->right;
          parentSuccessor->rthread = true;
        } else {
          parentSuccessor->left = successor->right;
          parentSuccessor->lthread = true;
        }
      } else {
        if (parentSuccessor == current) {
          parentSuccessor->right = successor->left;
        } else {
          parentSuccessor->left = successor->right;
        }
      }
      delete successor;
    }
  }
};

int main() {
  ThreadedBinaryTree tbt;
  tbt.insertNode(50);
  tbt.insertNode(20);
  tbt.insertNode(60);
  tbt.insertNode(10);
  tbt.insertNode(40);
  tbt.insertNode(30);
  tbt.insertNode(25);
  tbt.insertNode(35);

  tbt.inorder();
  cout << endl;
  tbt.preorder();

  tbt.deleteNode(20);

  cout << endl;
  tbt.inorder();

  return 0;
}
