#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isCyclicKahn(vector<vector<int>>& adj, vector<int>& cycle) {
    int n = adj.size();
    vector<int> in_degree(n, 0);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (adj[i][j])
                in_degree[j]++;

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (in_degree[i] == 0)
            q.push(i);

    int visitedCount = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cycle.push_back(node);
        visitedCount++;

        for (int i = 0; i < n; ++i) {
            if (adj[node][i]) {
                in_degree[i]--;
                if (in_degree[i] == 0)
                    q.push(i);
            }
        }
    }

    return visitedCount != n; 
}

int main() {
    vector<vector<int>> adj = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}  // 0 → 1 → 2 → 0 (cycle)
    };

    vector<int> cycle;
    if (isCyclicKahn(adj, cycle)) {
        cout << "Cycle found (BFS/Kahns Algorithm). Not a topological sort:" << endl;
        for (int i : cycle)
            cout << i << " ";
        cout << endl;
    } else {
        cout << "No cycle found (BFS/Kahns Algorithm). Topological sort:" << endl;
        for (int i : cycle)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}
