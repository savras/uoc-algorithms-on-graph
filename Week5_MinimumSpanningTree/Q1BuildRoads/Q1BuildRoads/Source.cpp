/*
 * Note for Prim's: dist array does not give the shortest distance for the MST. It is used in the algorithm
 * to indicate the shortest edge from a vertex. To get the shorest path (all edge weight) we
 * need to get the cost for all edges/paths in the parent array.
 */
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <functional>

using std::vector;
using std::priority_queue;
using std::pair;
using std::sqrt;
using std::make_pair;
using std::greater;

double length_of_segments(const int &p1, const int &p2, const vector<int> &x, const vector<int> &y) {
	double weight = sqrt(pow((x[p1] - x[p2]), 2) + pow((y[p1] - y[p2]),2));
	return weight;
}

void build_cost(vector<vector<double>> &cost, const vector<int> &x, const vector<int> &y) {
	int size = x.size();
	for (size_t i = 0; i < size; i++) {
		for (size_t p = i + 1; p < size; p++) {
			double weight = length_of_segments(i, p, x, y);
			cost[i][p] = cost[p][i] = weight;
		}
	}
}

// Kruskal's
double minimum_distance_kruskal(vector<int> x, vector<int> y) {
	return 0.0;
}

double calc_minimum_distance(vector<vector<double>> cost, const vector<int> &prev) {
	double result = 0.0;
	for (size_t i = 1; i < prev.size(); i++) {
		result += cost[prev[i]][i];
	}

	return result;
}

// Prim's using priority heap
double minimum_distance_prim(vector<int> x, vector<int> y) {
	int size = x.size();
	vector<bool> primTreeSet(size, false);	// Vertices in the tree that the algorithm builds.
	vector<int> prev(size, -1);	// parent of a vertex in MST.
	vector<vector<double>> cost(size, vector<double>(size, 0));
	build_cost(cost, x, y);	
	
	vector<double> dist(size, INT_MAX);	
	dist[0] = 0.0;
	
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> H;	// Min heap STL.
	H.push(make_pair(0.0, 0));
	
	while (!H.empty()) {
		int u = H.top().second;	// vertex index is stored as second value.
		H.pop();
		primTreeSet[u] = true;

		double d = dist[u];
		for (size_t v = 0; v < size; v++) {
			if (primTreeSet[v]) { continue; }
			double c = cost[u][v];
			if (c < dist[v]) {
				dist[v] = c;
				prev[v] = u;
				H.push(make_pair(c, v));
			}
		}
	}

	return calc_minimum_distance(cost, prev);
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::setprecision(10) << minimum_distance_prim(x, y) << std::endl;
}
