#include<bits/stdc++.h>
using namespace std;

const int VERTEX_SIZE = 100;

class Graph {
public:

	vector<vector<int> > adjList;

	Graph() {

		adjList.resize(VERTEX_SIZE + 1);
	}

	int getDiameter() {

		auto u = getMostFarVertex(1);

		auto v = getMostFarVertex(u.first);

		return v.second;
	}

	pair<int, int> getMostFarVertex(int u) {

		vector<char> visited(VERTEX_SIZE + 1, false);

		queue<pair<int, int> > Q;

		Q.push({ u, 0 });
		visited.at(u) = true;

		pair<int, int> far_vertex = { 0, 0 };

		while (!Q.empty()) {

			auto ele = Q.front();	Q.pop();

			int v = ele.first;
			int d = ele.second;

			if (far_vertex.second < d)	far_vertex = ele;

			for (int i = 0; i < (int)adjList.at(v).size(); i++) {

				if (visited.at(adjList.at(v).at(i)) == false) {

					visited.at(adjList.at(v).at(i)) = true;
					Q.push({ adjList.at(v).at(i), d + 1 });
				}
			}
		}

		return far_vertex;
	}

	double getAveOfClusterCoefficient() {

		double ret = 0.0;

		for (int u = 1; u <= VERTEX_SIZE; u++) {

			ret += getCluterCoefficient(u);
		}

		return (VERTEX_SIZE / 100);
	}

	double getCluterCoefficient(int u) {

		int n = adjList.at(u).size();

		if (n <= 1)	return 0;

		int max_num_edge = (n + 1) * n / 2;
		int cnt_edge = n;

		for (int i = 0; i < n; i++) {

			int from = adjList.at(u).at(i);

			for (int j = i + 1; j < n; j++) {

				int to = adjList.at(u).at(j);

				if (find(adjList.at(from).begin(), adjList.at(from).end(), to) != adjList.at(from).end()) {

					cnt_edge++;
				}
			}
		}

		double ret = (double)cnt_edge / (double)max_num_edge;

		return ret;
	}

	vector<int> getLinkedComponents() {

		map<int, int> linkedComponents;

		for (int u = 1; u <= 100; u++) {

			int reps_u = getRepresentative(u);

			if (linkedComponents.find(reps_u) == linkedComponents.end()) {

				linkedComponents.insert({ reps_u, 1 });
			}
			else {

				linkedComponents.at(reps_u)++;
			}
		}

		vector<int> ret;
		for (auto itr = linkedComponents.begin(); itr != linkedComponents.end(); itr++) {

			ret.push_back((*itr).second);
		}

		sort(ret.rbegin(), ret.rend());

		return ret;
	}

	void addEdge(int u, int v) {

		adjList.at(u).push_back(v);
		adjList.at(v).push_back(u);
	}

	int getRepresentative(int v) {

		int min_adj = v;
		for (int i = 0; i < (int)adjList.at(v).size(); i++) {

			min_adj = min(adjList.at(v).at(i), min_adj);
		}

		if (min_adj == v)	return v;

		return getRepresentative(min_adj);
	}
};

int main() {

	Graph g = Graph();

	ifstream ifs{ "edge.txt" };

	int cnt = 0;
	while (g.getLinkedComponents().size() > 1) {

		++cnt;

		int vi, vj;
		ifs >> vi >> vj;

		g.addEdge(vi, vj);
	}

	int diameter_prev = g.getDiameter();

	while (cnt < 4950) {

		++cnt;

		int vi, vj;
		ifs >> vi >> vj;

		g.addEdge(vi, vj);

		int d = g.getDiameter();

		if (d < diameter_prev) {

			diameter_prev = d;

			cout << cnt << " " << d << endl;
		}
	}

	return 0;
}