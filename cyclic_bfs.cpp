#include <iostream>
#include <queue>
using namespace std;

const int N = 3; // Number of nodes
int adj[N][N] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 0, 0} // 0 → 1 → 2 → 0 (cycle)
};

int main() {
    int in_degree[N] = {0};

    // Step 1: Compute in-degrees
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (adj[i][j])
                in_degree[j]++;

    // Step 2: Add nodes with 0 in-degree to queue
    queue<int> q;
    for (int i = 0; i < N; i++)
        if (in_degree[i] == 0)
            q.push(i);

    int visitedCount = 0;
    int topoOrder[N]; // To store the topological order
    int index = 0;

    // Step 3: Kahn's Algorithm
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder[index++] = node;
        visitedCount++;

        for (int i = 0; i < N; i++) {
            if (adj[node][i]) {
                in_degree[i]--;
                if (in_degree[i] == 0)
                    q.push(i);
            }
        }
    }

    // Step 4: Check if all nodes were visited
    if (visitedCount != N) {
        cout << "Cycle found (BFS / Kahn’s Algorithm)." << endl;
    } else {
        cout << "No cycle found (BFS / Kahn’s Algorithm)." << endl;
        cout << "Topological order: ";
        for (int i = 0; i < N; i++)
            cout << topoOrder[i] << " ";
        cout << endl;
    }

    return 0;
}
