#include<bits/stdc++.h>
using namespace std;

class Graph {

private:


public:

	set<pair<int, int> > E;

	vector<vector<int> > adjList;

	Graph() {

		adjList.resize(101);
	}

	double get_clusterNum(int u) {

		int n = adjList.at(u).size();

		if (n <= 1)	return 0;

		int max_edges = (n + 1) * n / 2;
		int cnt_edge = n;

		for (int i = 0; i < n; i++) {

			int from = adjList.at(u).at(i);

			for (int j = i + 1; j < n; j++) {

				int to = adjList.at(u).at(j);

				if (E.find({ from, to }) != E.end())	cnt_edge++;
			}
		}

		double ret = (double)cnt_edge / (double)max_edges;

		return ret;
	}

	vector<int> linked_components() {

		map<int, int> linkedComponents;

		for (int u = 1; u <= 100; u++) {

			int reps_u = get_reps(u);

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

	void add_edge(int u, int v) {

		adjList.at(u).push_back(v);
		adjList.at(v).push_back(u);

		E.insert({ u, v });
		E.insert({ v, u });
	}

	int get_reps(int v) {

		int min_adj = v;
		for (int i = 0; i < (int)adjList.at(v).size(); i++) {

			min_adj = min(adjList.at(v).at(i), min_adj);
		}

		if (min_adj == v)	return v;

		return get_reps(min_adj);
	}
};

int main() {

	Graph g = Graph();

	ifstream ifs{ "edge.txt" };

	int cnt = 0;
	while (cnt < 181) {

		int vi, vj;
		ifs >> vi >> vj;

		g.add_edge(vi, vj);

		++cnt;
	}

	for (int i = 1; i <= 10; i++) {

		auto ans = g.get_clusterNum(i);

		cout << ans << endl;
	}

	return 0;
}