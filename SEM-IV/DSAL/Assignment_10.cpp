/*  ---HEAP SORT---
  Arrange the STUDENTS according to their RANK
*/

#include <iostream>
using namespace std;

class Student {
public:
  string name;
  int rank;

  Student(string &name, int rank) {
    this->name = name;
    this->rank = rank;
  }
};

class MaxHeap {
private:
  Student **heap;
  int capacity; // MAX number of data that can be stored
  int size;     // Current no. of data present

  int parent(int i) { return (i / 2); }       // Returns index of parent
  int leftChild(int i) { return 2 * i + 1; }  // Returns index of left child
  int rightChild(int i) { return 2 * i + 2; } // Returns index of right child

  // Swapping the ojects for Heapifying
  void swap(Student *&a, Student *&b) {
    Student *temp = a;
    a = b;
    b = temp;
  }

  void maxHeapify(int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int largest = i;

    // if rank of left is greater than the current largest one then largest=
    // left
    if (left < size && heap[left]->rank > heap[largest]->rank)
      largest = left;

    // if rank of right is greater than the current largest one then largest=
    // right
    if (right < size && heap[right]->rank > heap[largest]->rank)
      largest = right;

    if (largest != i) {
      swap(heap[i], heap[largest]);
      maxHeapify(largest);
    }
  }

public:
  MaxHeap(int capacity) {
    this->capacity = capacity; // Total students
    heap = new Student *[capacity];
    size = 0;
  }

  void insert(Student *student) {
    if (size == capacity) // If array is full
      return;

    size++;               // Total size
    int curr = size - 1;  // Current Index
    heap[curr] = student; // Add the student in an Array

    // If the node is not a root node && if the rank of a current node is
    // greater than its parent then simply swap and make curr as parent
    while (curr > 0 && heap[curr]->rank > heap[parent(curr)]->rank) {
      swap(heap[curr], heap[parent(curr)]);
      curr = parent(curr);
    }

    // In insert() we have put the largest number at the ROOT
  }

  // Extracting the largest number(ROOT)
  Student *extractMax() {
    if (size == 0)
      return nullptr;

    Student *maxStudent = heap[0];
    heap[0] = heap[size - 1]; // last element of heap array at the root
    size--;
    maxHeapify(0);

    return maxStudent;
  }
};

// Getting the pointer of the student array
void heapSort(Student *arr[], int n) {
  MaxHeap maxHeap(n);

  // Build max heap
  for (int i = 0; i < n; i++)
    maxHeap.insert(arr[i]);

  // Extract max elements and place them at the end of the array as we want the
  // RANKS in ascending order
  for (int i = 0; i < n; i++)
    arr[i] = maxHeap.extractMax(); // It changes the sequence of student array
                                   // as it is a pointer
}

int main() {
  int numStudents;
  cout << "Number of students : ";
  cin >> numStudents;

  Student *students[numStudents];

  // Taking input of all the students
  for (int i = 0; i < numStudents; i++) {
    string name;
    int rank;
    cout << "Enter name and rank of Student " << i + 1 << " : ";
    cin >> name >> rank;
    students[i] = new Student(name, rank);
  }

  heapSort(students, numStudents);

  cout << "\n\nSorted student data (Descending order of ranks):" << endl;
  for (int i = 0; i < numStudents; i++)
    cout << "Rank " << students[i]->rank << " : " << students[i]->name << endl;

  return 0;
}

/* ALGORITHM
1. Create Objects
2. call the heapSort()
3. heapSort(object_array, total_studs){
    3.1 create array of Student objects
    3.2 insert each elemet into an Array. (put maximum element at the ROOT(0th
index)) 3.3 Call the extractMax() for making the array as sorted
  }
4. extractMax(){
call the
}
*/