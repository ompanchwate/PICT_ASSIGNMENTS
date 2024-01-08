/* epresent a given graph using adjacency list to perform DFS and BFS. Use the 
map of the area around the college as the graph. Identify the prominent land 
marks as nodes and perform DFS and BFS on that. */

#include <iostream>
using namespace std;

template <class T> class Stack {
  T arr[30];
  int top;

public:
  Stack() { top = -1; }

  void push(T data) {
    top++;
    arr[top] = data;
  }

  void pop() { top--; }

  bool isempty() { return top == -1; }

  T Top() { return arr[top]; }
};

template <class T> class Queue {
private:
  T arr[100];
  int front, rear;

public:
  Queue() { front = rear = -1; }

  bool isempty() { return front == -1 || front >= rear; }

  bool isfull() { return front > rear; }

  void enqueue(T data) {

    if (isfull()) {
      cout << "Queue full" << endl;
      return;
    }

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
    T data = arr[front];
    front++;
    return data;
  }
};

class Node {
  string place;
  Node *next;

public:
  Node(string place) {
    this->place = place;
    next = NULL;
  }
  friend class Graph;
};

class Graph {
  int nv;
  Node **vertices;

public:
  Graph() {
    cout << "Enter the number of vertices : ";
    cin >> nv;
    vertices = new Node *[nv];
  }

  int getIndex(string place) {
    for (int i = 0; i < nv; i++) {
      if (vertices[i]->place == place)
        return i;
    }
    return -1;
  }

  void create() {
    // Reading all the vertices
    for (int i = 0; i < nv; i++) {
      string place;
      cout << "Enter the place : ";
      cin >> place;
      Node *curr = new Node(place);
      vertices[i] = curr;
    }

    cout << "----------\nEnter -1 if nothing is connected\n------------"
         << endl;
    // Reading connected vertices
    for (int i = 0; i < nv; i++) {
      Node *temp = vertices[i]; // vertice (same for the next whole loop )
      Node *curr = vertices[i];

      for (int j = 0; j < nv - 1; j++) {
        string place;
        cout << "Enter the place to which " << temp->place
             << " is connected : ";
        cin >> place;

        // if input is -1 then break
        if (place == "-1") {
          break;
        }

        int index = getIndex(place);

        if (index == -1) {
          break;
        }

        Node *new_node = new Node(place);
        curr->next = new_node;
        curr = curr->next;
      }
    }
  }

  void display() {
    for (int i = 0; i < nv; i++) {
      cout << vertices[i]->place << " --> ";

      Node *temp = vertices[i]->next;
      while (temp != NULL) {
        cout << temp->place << " -> ";
        temp = temp->next;
      }

      cout << endl;
    }
  }

  void bfs(string startPlace) {
    bool visited[nv];

    // Visited array
    for (int i = 0; i < nv; i++) {
      visited[i] = false;
    }

    Queue<Node *> q;
    int startIndex = getIndex(startPlace);

    if (startIndex == -1) {
      cout << "Start vertex not present" << endl;
      return;
    }

    Node *startNode = vertices[startIndex];
    visited[startIndex] = true; // Make 1st index as Visited
    q.enqueue(startNode);

    while (!q.isempty()) {
      Node *curr = q.dequeue();
      cout << curr->place << " ";

      Node *temp = curr->next;
      while (temp != NULL) {
        int index = getIndex(temp->place);
        if (index != -1 && !visited[index]) {
          visited[index] = true;
          q.enqueue(vertices[index]);
        }
        temp = temp->next;
      }
    }
  }

  // USE STACK
  void dfs(string startPlace) {
    bool visited[nv];
    for (int i = 0; i < nv; i++) {
      visited[i] = false;
    }

    int startIndex = getIndex(startPlace);
    if (startIndex == -1) {
      cout << "Place does not exist" << endl;
      return;
    }

    Stack<Node *> st;

    st.push(vertices[startIndex]);

    while (!st.isempty()) {
      Node *curr = st.Top();
      st.pop();

      // If the index of the curr->place is not visited then print it and make
      // it TRUE
      if (!visited[getIndex(curr->place)]) {
        cout << curr->place << " ";
        visited[getIndex(curr->place)] = true;
      }

      Node *temp = curr->next;
      while (temp != NULL) {
        int index = getIndex(temp->place);
        if (index != -1 && !visited[index]) {
          st.push(vertices[index]);
        }
        temp = temp->next;
      }
    }
  }
};

int main() {
  Graph g;
  g.create();
  g.display();
  cout << endl << endl;

  g.bfs("c");
  cout << endl << endl;
  g.dfs("c");
}