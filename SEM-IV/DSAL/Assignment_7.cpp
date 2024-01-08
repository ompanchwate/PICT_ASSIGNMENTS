// PRIM'S ALGORITHM 
#include <iostream>
using namespace std;

#define MAX_VERTICES 100
#define MAX_WEIGHT 99999

// MST = Minimmum Spanning Tree
class Graph {
  int vertices;
  int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];

public:
  Graph(int vertices) {
    this->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
      for (int j = 0; j < vertices; j++) {
        adjacency_matrix[i][j] = 0;
      }
    }
  }

  void add_edge(int u, int v, int weight) {
    // Simple arr[u][v] and reciprocal arr[v][u]
    adjacency_matrix[u][v] = weight;
    adjacency_matrix[v][u] = weight;
  }

  void display() {
    // Display the whole matrix
    cout << "Adjacency Matrix:\n";
    for (int i = 1; i < vertices; i++) {
      for (int j = 1; j < vertices; j++) {
        cout << adjacency_matrix[i][j] << " ";
      }
      cout << std::endl;
    }
  }

  // Prims Algorithm
  void prim_mst() {
    bool visited[vertices]; // Maintain visited vertices.
    int sum = 0;

    for (int i = 0; i < vertices; i++)
      visited[i] = false;
    

    cout << "MST using PRIM'S : " << endl;
    cout << "EDGES"
         << "\t"
         << "WEIGHT" << endl;

    //( vertices-1) as the no. of edges in minimum spanning tree is n-1
    for (int k = 0; k < vertices - 1; k++) {
      int min = MAX_WEIGHT; // For comparison
      visited[1] = true;    // let 1st vertix be visited
      int r = 0;            // Row of the MST which we have to display
      int c = 0;            // Column of the MST which we have to display

      // For iterating through the rows
      for (int i = 1; i < vertices; i++) {
        if (visited[i]) {
          // Finding the edge with the minimum weight using indexes
          // Iterating through the columns
          for (int j = 1; j < vertices; j++) {
            if (min > adjacency_matrix[i][j]) {
              if (!visited[j] && adjacency_matrix[i][j] != 0) {
                min = adjacency_matrix[i][j];
                r = i;
                c = j;
              }
            }
          }
        }
      }
      // Displaying the MST
      sum = sum + adjacency_matrix[r][c];
      cout << r << "->" << c << "\t  " << adjacency_matrix[r][c];
      cout << "\n";
      visited[c] = true;
    }
    cout << "--------------------" << endl;
    cout << "Total = " << sum << endl;
  }
};

int main() {
  Graph g(7);
  g.add_edge(1, 2, 6);
  g.add_edge(1, 3, 1);
  g.add_edge(1, 4, 5);
  g.add_edge(2, 5, 3);
  g.add_edge(2, 3, 5);
  g.add_edge(3, 4, 5);
  g.add_edge(3, 5, 6);
  g.add_edge(3, 6, 4);
  g.add_edge(4, 6, 2);
  g.add_edge(5, 6, 6);

  g.display();
  cout << "\n\n";

  g.prim_mst();

  return 0;
}



// KRUSHKAL's implementation
/*
  1. insert the source, destination and weight
  2. Call KrushkalMST()
  3. initialixe parent[] with -1
  4. Sort the edges by weight
  5. Run the loop upto vertices-1
  6. Find the parent of the source and destination of currentEdge
  7. If parent of source is not equal to the parent of destination then
  8. union the distinct sets
  9.
*/

/*
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX_VERTICES = 1000;
const int MAX_EDGES = 10000;

class Edge {
public:
  int src, dest, weight;
};

class Graph {
public:
  int numVertices, numEdges;
  Edge edges[MAX_EDGES];

  Graph(int v) {
    numVertices = v;
    numEdges = 0;
  }

  void addEdge(int src, int dest, int weight) {
    edges[numEdges].src = src;
    edges[numEdges].dest = dest;
    edges[numEdges].weight = weight;
    numEdges++;
  }

  void sortEdgesByWeight() {
    sort(edges, edges + numEdges,
         [](const Edge &a, const Edge &b) { return a.weight < b.weight; });
  }

  int findParent(int parent[], int vertex) {
    if (parent[vertex] == -1)
      return vertex;
    return findParent(parent, parent[vertex]);
  }

  void unionSets(int parent[], int x, int y) {
    int xParent = findParent(parent, x);
    int yParent = findParent(parent, y);
    parent[xParent] = yParent;
  }

  void kruskalMST() {
    Edge mst[MAX_VERTICES];
    int parent[MAX_VERTICES];
    int mstSize = 0;

    for (int i = 0; i < numVertices; i++)
      parent[i] = -1;

    sortEdgesByWeight();

    int edgeCount = 0;
    // numVertices -1    => As there should be 1 vertex less than the original
    // graph to avoid cycle.
    for (int i = 0; edgeCount < numVertices - 1 && i < numEdges; i++) {
      Edge currentEdge = edges[i];

      // Find the parent for Source and Destination
      int srcParent = findParent(parent, currentEdge.src);
      int destParent = findParent(parent, currentEdge.dest);

      // If parent of source and destination is not same
      if (srcParent != destParent) {
        mst[mstSize++] = currentEdge;
        unionSets(parent, srcParent, destParent);
        edgeCount++;
      }
    }

    // Displaying the spanning tree.
    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < mstSize; i++) {
      cout << mst[i].src << " -- " << mst[i].dest << " : " << mst[i].weight
           << endl;
    }
  }
};

int main() {
  int numVertices, numEdges;
  cout << "Enter the number of vertices: ";
  cin >> numVertices;
  cout << "Enter the number of edges: ";
  cin >> numEdges;

  Graph graph(numVertices);

  cout << "Enter the edges in the format (source destination weight):" << endl;
  for (int i = 0; i < numEdges; i++) {
    int src, dest, weight;
    cin >> src >> dest >> weight;
    graph.addEdge(src, dest, weight);
  }

  graph.kruskalMST();

  return 0;
} */