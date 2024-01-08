/*
A dictionary stores keywords and its meanings. Provide facility for
adding new keywords, deleting keywords, updating values of any
entry. Provide facility to display whole data sorted in ascending /
Descending order. Also find how many maximum comparisons may
require for finding any keyword. Use Binary Search Tree for
implementation.*/
#include <iostream>
using namespace std;

class Node {
private:
  string word;
  string meaning;
  Node *left;
  Node *right;

public:
  Node(string word, string meaning) {
    this->word = word;
    this->meaning = meaning;
    left = right = NULL;
  }
  friend class Dictionary;
};

class Stack {
private:
  int top;
  Node *arr[30];

public:
  Stack() { top = -1; }

  void push(Node *node) {
    top++;
    arr[top] = node;
  }

  void pop() { top--; }

  Node *Top() { return arr[top]; }

  bool isempty() {
    if (top == -1) {
      return 1;
    }
    return 0;
  }
};

class Dictionary {
private:
  Node *root;

public:
  Dictionary() { root = NULL; }

  void insert(string word, string meaning) {
    Node *new_node = new Node(word, meaning);
    if (root == NULL) {
      root = new_node;
      return;
    }

    Node *curr = root;

    while (curr != NULL) {
      if (word < curr->word) {
        if (curr->left == NULL) {
          curr->left = new_node;
          break;
        } else {
          curr = curr->left;
        }
      } else {
        if (curr->right == NULL) {
          curr->right = new_node;
          break;
        } else {
          curr = curr->right;
        }
      }
    }
  }

  void update(string key, string new_meaning) {
    Node *curr = root;

    if (curr->word == key) {
      curr->meaning = new_meaning;
      cout << "Meaning updated..." << endl;
      return;
    }

    while (curr != NULL) {
      if (key < curr->word) {
        curr = curr->left;
        if (curr->word == key) {
          curr->meaning = new_meaning;
          cout << "Meaning updated..." << endl;
          return;
        } else {
          curr = curr->left;
        }
      } else {
        curr = curr->right;
        if (curr->word == key) {
          curr->meaning = new_meaning;
          cout << "Meaning updated..." << endl;
          return;
        } else {
          curr = curr->right;
        }
      }
    }
    cout << "Word not found..." << endl;
  }

  void inorder() {
    Stack st;
    Node *curr = root;

    while (!st.isempty() || curr != NULL) {
      while (curr != NULL) {
        st.push(curr);
        curr = curr->left;
      }

      curr = st.Top();
      st.pop();

      cout << curr->word << " : " << curr->meaning << endl;
      curr = curr->right;
    }
  }

  void inorder_recursive(Node *node) {
    if (node == NULL) {
      return;
    }

    inorder_recursive(node->left);
    cout << node->word << " : " << node->meaning << endl;
    inorder_recursive(node->right);
  }
  void call_inorder() { inorder_recursive(root); }

  void deleteWord(string word) { root = deleteNode1(root, word); }

  Node *deleteNode(Node *root, string word) {
    Node *curr = root;
    Node *prev = NULL;
    while (curr != NULL && curr->word != word) {
      prev = curr;
      if (curr->word > word) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    if (curr == NULL) {
      cout << "Element not present..." << endl;
      return root;
    }

    // ATMOST ONE CHILD
    if (curr->left == NULL || curr->right == NULL) {
      Node *newCurr;

      if (curr->left == NULL) {
        newCurr = curr->right;
      } else {
        newCurr = curr->left;
      }

      if (prev == NULL) {
        return root;
      }

      if (curr == prev->left) {
        prev->left = newCurr;
      } else {
        prev->right = newCurr;
      }

      delete curr;
      cout << "Word deleted..." << endl;
      return root;
    } else {
      // BOTH CHILD
      Node *p = NULL;
      Node *temp = curr->right;
      while (temp->left != NULL) {
        p = temp;
        temp = temp->left;
      }

      if (p != NULL) {
        p->left = temp->right;
      } else {
        curr->right = temp->right;
      }

      curr->word = temp->word;
      curr->meaning = temp->meaning;

      delete temp;
      cout << "Word deleted" << endl;
    }
    return root;
  }

  Node *deleteNode1(Node *root, string word) {
    Node *parent = NULL;
    Node *curr = root;

    while (curr != NULL && curr->word != word) {
      parent = curr;
      if (curr->word > word) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    if (curr == NULL) {
      cout << "Not found..." << endl;
    }

    if (curr->left == NULL || curr->right == NULL) {
      Node *newCurr;

      if (curr->left == NULL) {
        newCurr = curr->right;
      } else {
        newCurr = curr->left;
      }

      if (parent == NULL) {
        return root;
      }

      if (curr == parent->left) {
        parent->left = newCurr;
      } else {
        parent->right = newCurr;
      }

      delete curr;
      return root;
    } else {
      Node *p = NULL;
      Node *temp = curr->right;

      while (temp->left != NULL) {
        p = temp;
        temp = temp->left;
      }

      if (p == NULL) {
        curr->right = temp->right;
      } else {
        p->left = temp->right;
      }

      curr->word = temp->word;
      curr->meaning = temp->meaning;
    }

    return root;
  }
};

int main() {
  cout << "Hello World!\n";
  Dictionary d;

  d.insert("nn", "oobvjre");
  d.insert("aa", "qoobvjre");
  d.insert("uu", "qoobvjre");
  d.insert("yy", "qoobvjre");
  d.insert("yz", "qoobvjre");
  d.insert("zz", "vjre");
  d.insert("pp", "qoobvjre");
  d.insert("add", "qoobvjre");
  // d.insert("yty", "qoobvjre");
  d.insert("tt", "qoobvjre");
  d.insert("v", "qoobvjre");

  bool flag = true;

  while (flag) {
    cout << "----------------------------------" << endl;
    cout << "1. Add new word.\n2. Display all words.\n3. Update a word.\n4. "
            "Delete a word.\n5.exit"
         << endl;
    cout << "----------------------------------" << endl;

    int choice;
    cout << "Enter your choice : ";
    cin >> choice;

    if (choice == 1) {
      string word, meaning;
      cout << "Enter word : ";
      cin >> word;
      cout << "Enter meaning : ";
      cin >> meaning;

      d.insert(word, meaning);
    } else if (choice == 2) {
      d.inorder();
    } else if (choice == 3) {
      string key, new_meaning;
      cout << "Enter a word to update : ";
      cin >> key;
      cout << "Enter new meaning : ";
      cin >> new_meaning;

      d.update(key, new_meaning);
    } else if (choice == 4) {
      string key;
      cout << "Enter a word to delete : ";
      cin >> key;

      d.deleteWord(key);
    } else if (choice == 5) {
      cout << "Exited..." << endl;
      flag = false;
    }
  }
}