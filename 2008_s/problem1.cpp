#include<bits/stdc++.h>
using namespace std;

class Graph {

private:


public:

	vector<vector<int> > adjList;

	Graph() {

		adjList.resize(101);
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

	auto ans = g.linked_components();

	for (auto& e : ans) {

		cout << e << endl;
	}

	return 0;
}