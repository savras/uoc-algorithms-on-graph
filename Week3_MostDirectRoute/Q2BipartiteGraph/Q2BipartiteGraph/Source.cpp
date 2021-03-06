/*
 * This solution doesn't handle isolated or island nodes.
 * To do so, we need to loop through all of adj.
 */
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(const vector<vector<int>> &adj) {
	int adjSize = adj.size();
	vector<int> color(adjSize, 0);
	queue<int> q;

	q.emplace(0);
	color[0] = 1;
	int bipartiteState = -1;	// This will flip for each alternating neighbour
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (size_t i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			if (color[v] == 0) {
				q.emplace(adj[u][i]);
				color[v] = bipartiteState;
			}
			else {
				if (color[v] == color[u]) {
					return 0;
				}
			}
		}
		bipartiteState *= -1;
	}

	return 1;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	std::cout << bipartite(adj);
}
