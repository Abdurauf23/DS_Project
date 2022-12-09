#include <bits/stdc++.h>
using namespace std;

int NO_PARENT = -1;

// Funciton to print shortest path using parents array
void print_path(int current_vertex, vector<int> parents) {

	// if source node has been processed
	if (current_vertex == NO_PARENT) {
		return;
	}

	print_path(parents[current_vertex], parents);
	cout << current_vertex << "->";
}

// Funciton to print distances and shortest paths
void print_solution(int start_vertex, vector<int> distances,
					vector<int> parents) {
	int n_vertices = distances.size();
	cout << "Vertex\t Distance\tPath";

	for (int vertex_index = 0; vertex_index < n_vertices; vertex_index++) {
		if (vertex_index != start_vertex) {
			cout << endl
				 << start_vertex << " to " << vertex_index << " \t\t ";
			cout << distances[vertex_index] << "\t\t";
			print_path(vertex_index, parents);
		}
	}
}

// Main function that implements Dijkstra's algo
void find_path(vector<vector<int>> adjacency_matrix,
			   int start_vertex) {
	int n_vertices = adjacency_matrix[0].size();

	// shortest_distance[] holds the
	// the shortest distance from source to 
	// all vertices
	vector<int> shortest_distance(n_vertices);

	// added[] holds indexes of vertices that
	// are included shortest distance from src to
	// all veritces
	vector<bool> added(n_vertices);

	// Initially all distances = infinity
	// And all added[] elements are false
	for (int vertex_index = 0; vertex_index < n_vertices;
		 vertex_index++) {
		shortest_distance[vertex_index] = INT_MAX;
		added[vertex_index] = false;
	}

	// Distance from initial point to itself = 0
	shortest_distance[start_vertex] = 0;

	// Parent array holdsshortest path tree
	vector<int> parents(n_vertices);

	// The starting vertex does not
	// have a parent
	parents[start_vertex] = NO_PARENT;

	// Main loop that fins the shortest 
	// distance from source to all vertices
	for (int i = 1; i < n_vertices; i++) {

		// Pick the minimum distance vertex
		// from the set of vertices not yet
		// processed. nearest_vertex is
		// always equal to startNode in
		// first iteration.
		int nearest_vertex = -1;
		int shortestDistance = INT_MAX;
		for (int vertex_index = 0; vertex_index < n_vertices;
			 vertex_index++) {
			if (!added[vertex_index] && shortest_distance[vertex_index] < shortestDistance) {
				nearest_vertex = vertex_index;
				shortestDistance = shortest_distance[vertex_index];
			}
		}

		// Mark the picked vertex as processed
		added[nearest_vertex] = true;

		// Update dist value of the
		// adjacent vertices of the
		// picked vertex.
		for (int vertex_index = 0; vertex_index < n_vertices;
			 vertex_index++) {
			int edgeDistance = adjacency_matrix[nearest_vertex][vertex_index];

			if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortest_distance[vertex_index])) {
				parents[vertex_index] = nearest_vertex;
				shortest_distance[vertex_index] = shortestDistance + edgeDistance;
			}
		}
	}

	print_solution(start_vertex, shortest_distance, parents);
}

int main() {
	vector<vector<int>> adjacency_matrix = {
		{0,1,1,4,0},
		{1,0,0,2,0},
		{1,0,0,1,2},
		{4,2,1,0,4},
		{0,0,2,4,0}
	};
	find_path(adjacency_matrix, 1);
	cout << endl;
	return 0;
}