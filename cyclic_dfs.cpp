#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

bool dfs(int node, vector<vector<int>>& adj, vector<bool>& visited,
         vector<bool>& recStack, vector<int>& parent, int& cycle_end) {
    visited[node] = true;
    recStack[node] = true;

    for (int neighbor = 0; neighbor < adj.size(); neighbor++) {
        if (adj[node][neighbor]) {
            if (!visited[neighbor]) {
                parent[neighbor] = node;
                if (dfs(neighbor, adj, visited, recStack, parent, cycle_end))
                    return true;
            } else if (recStack[neighbor]) {
                parent[neighbor] = node;
                cycle_end = neighbor;
                return true;
            }
        }
    }

    recStack[node] = false;
    return false;
}

void printCycleDFS(vector<int>& parent, int start) {
    vector<int> cycle;
    int current = parent[start];
    cycle.push_back(start);

    while (current != start) {
        cycle.push_back(current);
        current = parent[current];
    }
    cycle.push_back(start);

    reverse(cycle.begin(), cycle.end());
    cout << "Cycle found (DFS): ";
    for (int node : cycle)
        cout << node << " ";
    cout << endl;
}

int main() {
    vector<vector<int>> adj = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}  // 0 → 1 → 2 → 0 (cycle)
    };

    int n = adj.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<int> parent(n, -1);
    int cycle_end = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, adj, visited, recStack, parent, cycle_end)) {
                printCycleDFS(parent, cycle_end);
                return 0;
            }
        }
    }

    cout << "No cycle found (DFS)." << endl;
    return 0;
}
