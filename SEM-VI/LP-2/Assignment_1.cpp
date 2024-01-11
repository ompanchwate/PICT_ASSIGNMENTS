#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<char>> adjacencyListDFS;
    vector<unordered_map<char, int>> adjacencyListBFS;

public:
    Graph(int v) : vertices(v), adjacencyListDFS(v), adjacencyListBFS(v) {}

    void addEdgeDFS(char src, char dest) {
        adjacencyListDFS[src - 'A'].push_back(dest);
    }

    void addEdgeBFS(char src, char dest, int weight) {
        adjacencyListBFS[src - 'A'][dest] = weight;
        adjacencyListBFS[dest - 'A'][src] = weight;  // Assuming an undirected graph
    }

    void DFS(char src, char dest, vector<bool>& visited, stack<char>& pathStack) {
        visited[src - 'A'] = true;
        pathStack.push(src);

        if (src == dest) {
            // Print the path
            vector<char> path;
            stack<char> tempStack = pathStack;
            while (!tempStack.empty()) {
                path.push_back(tempStack.top());
                tempStack.pop();
            }

            for(int i=path.size()-1; i >= 0; i--) {
                cout<<path[i]<<" ";
            }
            cout << endl;
        } else {
            for (char neighbor : adjacencyListDFS[src - 'A']) {
                if (!visited[neighbor - 'A']) {
                    DFS(neighbor, dest, visited, pathStack);
                }
            }
        }

        // Backtrack
        visited[src - 'A'] = false;
        pathStack.pop();
    }

    void recursiveBFS(char src, int k, unordered_map<char, int>& distance, queue<char>& q, unordered_set<char>& visited) {
        if (q.empty()) {
            return;
        }

        char current_node = q.front();
        q.pop();

        for (const auto& neighbor : adjacencyListBFS[current_node - 'A']) {
            char next_node = neighbor.first;
            int weight = neighbor.second;

            if (!visited.count(next_node)) {
                visited.insert(next_node);
                distance[next_node] = distance[current_node] + weight;

                if (distance[next_node] <= k) {
                    cout << next_node << " ";
                }

                q.push(next_node);
            }
        }

        recursiveBFS(src, k, distance, q, visited);
    }

    void printAllPaths(char src, char dest) {
        vector<bool> visited(vertices, false);
        stack<char> pathStack;

        cout << "All paths from " << src << " to " << dest << " are:\n";
        DFS(src, dest, visited, pathStack);
    }

    void printNodesAtDistance(char src, int k) {
        unordered_map<char, int> distance;
        queue<char> q;
        unordered_set<char> visited;

        q.push(src);
        visited.insert(src);

        cout << "Users from "<< src << " in a range of " << k<< " are: "<<endl;
        recursiveBFS(src, k, distance, q, visited);
        cout << endl;
    }
};

int main() {
    // Create a graph
    Graph graph(26); // Assuming only uppercase alphabets are used
    graph.addEdgeDFS('A', 'B');
    graph.addEdgeDFS('A', 'C');
    graph.addEdgeDFS('B', 'D');
    graph.addEdgeDFS('B', 'E');
    graph.addEdgeDFS('C', 'F');
    graph.addEdgeDFS('E', 'F');

    graph.addEdgeBFS('A', 'B', 1);
    graph.addEdgeBFS('A', 'C', 2);
    graph.addEdgeBFS('B', 'D', 3);
    graph.addEdgeBFS('B', 'E', 1);
    graph.addEdgeBFS('C', 'F', 2);
    graph.addEdgeBFS('E', 'F', 1);

    char source = 'A';
    char destination = 'F';
    int k = 2;

    int choice;
    cout << "Choose operation:\n1. DFS - Print all paths\n2. BFS - Print nodes at distance\n3. Exit";
    cin >> choice;

    switch(choice) {
        case 1:
            graph.printAllPaths(source, destination);
            break;
        case 2:
            graph.printNodesAtDistance(source, k);
            break;
        case 3: break;
        default:
            cout << "Invalid choice\n";
    }

    return 0;
}
