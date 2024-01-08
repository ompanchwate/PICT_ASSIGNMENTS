/* Consider telephone book database of N clients. Make use of a hash table 
implementation to quickly look up client‘s telephone number. Make use of two 
collision handling techniques and compare them using number of comparisons 
required to find a set of telephone numbers (Note: Use linear probing with 
replacement and without replacement) */

#include <iostream>
using namespace std;

class DataItem {
  long mobno;
  string name;

public:
  DataItem() {
    this->mobno = -1;
    this->name = "";
  }

  friend class HashTable;
};

class HashTable {
  DataItem hashTable[10];

public:
  void withoutreplacement(long mobno, string name) {
    int key = mobno % 10;
    if (hashTable[key].mobno == -1) {
      hashTable[key].name = name;
      hashTable[key].mobno = mobno;
    } else {
      int i = key + 1;
      while (hashTable[i].mobno != -1) {
        i = (i + 1) % 10;
        if (i == key) {
          cout << "Table full..." << endl;
          break;
        }
      }
      hashTable[i].mobno = mobno;
      hashTable[i].name = name;
    }
  }

  void withreplacement(long mobno, string name) {
    int key = mobno % 10;
    // The index is empty simply add it
    if (hashTable[key].mobno == -1) {
      hashTable[key].mobno = mobno;
      hashTable[key].name = name;
      // The existing element is not at its correct position
    } else if (hashTable[key].mobno % 10 != key) {
      DataItem temp;
      temp.name = hashTable[key].name;
      temp.mobno = hashTable[key].mobno;

      hashTable[key].name = name;
      hashTable[key].mobno = mobno;

      int i = key + 1;
      while (hashTable[i].mobno != -1) {
        if (i == key) {
          cout << "Full" << endl;
          break;
        } else {
          i = (i + 1) % 10;
        }
      }
      hashTable[i].mobno = temp.mobno;
      hashTable[i].name = temp.name;
    } else {
      // Linear prob
      int i = key + 1;
      while (hashTable[i].mobno != -1) {
        if (i == key) {
          cout << "Full" << endl;
          break;
        } else {
          i = (i + 1) % 10;
        }
      }
      hashTable[i].mobno = mobno;
      hashTable[i].name = name;
    }
  }

  void search(long mobno) {
    bool found = false;
    int key = mobno % 10;
    if (hashTable[key].mobno == mobno) {
      found = true;
      cout << "Found" << endl;
      cout << hashTable[key].name << " : " << hashTable[key].mobno << endl;
    } else {
      int i = key + 1;
      while (hashTable[i].mobno != mobno) {
        i = (i + 1) % 10;
        if (hashTable[i].mobno == mobno) {
          found = true;
        }
      }

      if (found) {
        cout << "Found" << endl;
        cout << hashTable[i].name << " : " << hashTable[i].mobno << endl;
      } else {
        cout << "Not found" << endl;
      }
    }
  }

  void display() {
    for (int i = 0; i < 10; i++) {
      cout << i + 1 << ")   " << hashTable[i].name << " : "
           << hashTable[i].mobno << endl;
    }
  }
};

int main() {
  HashTable ht;
  ht.withoutreplacement(999944494, "Om");
  ht.withoutreplacement(999944494, "aa");
  ht.withoutreplacement(999944495, "bb");
  ht.withoutreplacement(999954492, "cc");
  ht.withoutreplacement(999944482, "dd");
  ht.withoutreplacement(999944493, "ee");
  ht.withoutreplacement(999944497, "ff");
  ht.withoutreplacement(999944490, "Om");
  ht.withoutreplacement(999944499, "Om");
  ht.withoutreplacement(999944492, "Om");

  // ht.withreplacement(999944494, "Om");
  // ht.withreplacement(999944494, "aa");
  // ht.withreplacement(999944495, "bb");
  // ht.withreplacement(999944492, "cc");
  // ht.withreplacement(999944482, "dd");
  // ht.withreplacement(999944493, "ee");
  // ht.withreplacement(999944497, "ff");
  // ht.withreplacement(999944490, "Om");
  // ht.withreplacement(999944499, "Om");
  // ht.withreplacement(999944492, "Om");
  // ht.withreplacement(999944492, "Om");

  ht.display();

  cout << endl << endl;
  ht.search(999944492);
}