/* Implement all the functions of a dictionary (ADT) using open hashing technique:
separate chaining using linked list
Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be 
comparable, and Keys must be unique. Standard Operations: Insert(key, value), 
Find(key), Delete(key) */
#include <iostream>
using namespace std;

class hashnode {

  string word;
  string meaning;
  hashnode *next;

public:
  hashnode(string x, string y) {
    word = x;
    meaning = y;
    next = NULL;
  }

  hashnode() {
    word = " ";
    meaning = " ";
    next = NULL;
  }
  friend class hashtable;
};

class hashtable {
  hashnode *table[10];
  int table_size = 10;

public:
  hashtable() {
    for (int i = 0; i < 10; i++) {
      table[i] = NULL;
    }
  }

  // Gives the key by calculating the ASCII value and finding modulo by 10
  int hash(string word) {
    int ascii = 0;
    for (int i = 0; word[i] != '\0'; i++) {
      ascii = ascii + word[i];
    }
    return (ascii % table_size);
  }

  void insert(string word1, string meaning1) {
    int hash_val = hash(word1);
    hashnode *prev = NULL;
    hashnode *entry = table[hash_val];
    while (entry != NULL) {
      prev = entry;
      entry = entry->next;
    }

    if (entry == NULL) {
      entry = new hashnode(word1, meaning1);
      if (prev == NULL) {
        table[hash_val] = entry;
      } else {
        prev->next = entry;
      }
    } else {
      entry->meaning = meaning1;
    }
  }

  void display() {
    for (int i = 0; i < table_size; i++) {

      hashnode *temp = table[i];
      while (temp != NULL) {
        cout << temp->word << " - " << temp->meaning << endl;
        cout << endl;
        temp = temp->next;
      }
    }
  }

  void remove(string word1) {
    int hash_val = hash(word1);
    hashnode *entry = table[hash_val];
    hashnode *prev = NULL;
    if (entry == NULL) {
      cout << "No Element found a " << word1 << endl;
      return;
    } else {

      if (entry->word == word1) {
        entry = entry->next;
        delete (table[hash_val]);
        table[hash_val] = entry;
        entry = NULL;
      } else {
        while (entry->word != word1 && entry != NULL) {
          prev = entry;
          entry = entry->next;
        }
        if (entry->word == word1) {
          prev->next = entry->next;
          delete (entry);
          entry = NULL;
        }
      }
    }
  }

  int find(string word) {
    int cmp = 1, label = 0;
    int key1 = hash(word);
    while (table[key1] != NULL) {
      if (table[key1]->word == word) {
        label = 1;
        cout << "Element found!" << endl;
        break;
      } else {
        cmp++;
        table[key1] = table[key1]->next;
      }
    }
    if (label == 1)
      return cmp;
    else
      cout << "Element not found!" << endl;
    return -1;
  }
};
int main() {
  hashtable s;
  bool flag = true;
  while (flag) {
    cout << "----------Menu---------" << endl;
    cout << "1)Add word to the dictionary" << endl;
    cout << "2)Display dictionary" << endl;
    cout << "3)Search word in dictionary" << endl;
    cout << "4)Delete word from dictionary" << endl;
    cout << "5)Exit" << endl;
    cout << endl;
    cout << "Enter your choice" << endl;
    int ch;
    cin >> ch;

    switch (ch) {

    case 1: {
      cout << "Enter number of words you want to add" << endl;
      int n;
      cin >> n;
      string word, meaning;
      for (int i = 0; i < n; i++) {
        cout << "Enter " << i + 1 << " word" << endl;
        cin >> word;
        cout << "Enter meaning of " << word << endl;
        cin >> meaning;
        s.insert(word, meaning);
      }
    } break;

    case 2:
      cout << "Words and Meanings " << endl;
      s.display();
      break;

    case 3:

    {
      cout << "Enter word to be search" << endl;
      string word;
      cin >> word;
      int cmp;
      cmp = s.find(word);
      if (cmp == -1) {
        cout << word << " not present in dictionary" << endl;
      } else {
        cout << word << " present in dictionary" << endl;
        cout << "NO of comparisons " << cmp << endl;
      }
    } break;

    case 4: {
      cout << "Enter word to be delete" << endl;
      string word;
      cin >> word;
      s.remove(word);
      cout << word << " deleted" << endl;
      break;
    }

    case 5:
      cout << "BY BY" << endl;
      flag = false;
      break;
    }
  }
  return 0;
}