#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3; // Number of nodes (adjustable)
int adj[N][N] = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 0, 0} // 0 → 1 → 2 → 0 (cycle)
};

bool visited[N];
bool recStack[N];
int parent[N];

bool dfs(int node, int& cycle_end) {
    visited[node] = true;
    recStack[node] = true;

    for (int neighbor = 0; neighbor < N; neighbor++) {
        if (adj[node][neighbor]) {
            if (!visited[neighbor]) {
                parent[neighbor] = node;
                if (dfs(neighbor, cycle_end))
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

void printCycle(int start) {
    int cycle[N], idx = 0;
    cycle[idx++] = start;

    int current = parent[start];
    while (current != start && idx < N) {
        cycle[idx++] = current;
        current = parent[current];
    }
    cycle[idx++] = start;

    reverse(cycle, cycle + idx);
    cout << "Cycle found (DFS): ";
    for (int i = 0; i < idx; i++)
        cout << cycle[i] << " ";
    cout << endl;
}

int main() {
    fill(visited, visited + N, false);
    fill(recStack, recStack + N, false);
    fill(parent, parent + N, -1);

    int cycle_end = -1;

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            if (dfs(i, cycle_end)) {
                printCycle(cycle_end);
                return 0;
            }
        }
    }

    cout << "No cycle found (DFS)." << endl;
    return 0;
}
