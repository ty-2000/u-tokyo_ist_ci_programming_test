#include<bits/stdc++.h>
using namespace std;

const int INF = 1 << 29;

class Graph {

private:


public:

	set<pair<int, int> > E;

	vector<vector<int> > adjList;

	vector<vector<int> > dists;

	Graph() {

		adjList.resize(101);
	}

	double get_distAve() {

		int sum = 0;
		int cnt_edge = 0;

		for (int u = 1; u <= 100; u++) {

			for (int v = u + 1; v <= 100; v++) {

				if (dists.at(u).at(v) < INF) {

					++cnt_edge;

					sum += dists.at(u).at(v);
				}
			}
		}

		return (double)sum / (double)cnt_edge;
	}

	void warshal_floyed() {

		dists.assign(101, vector<int>(101));

		for (int u = 1; u <= 100; u++) {

			for (int v = 1; v <= 100; v++) {

				dists.at(u).at(v) = (E.find({ u, v }) == E.end()) ? INF : 1;
			}
		}

		for (int via = 1; via <= 100; via++) {

			for (int u = 1; u <= 100; u++) {

				for (int v = 1; v <= 100; v++){

					if (u == v)	continue;

					dists.at(u).at(v) = min(dists.at(u).at(via) + dists.at(via).at(v), dists.at(u).at(v));
				}
			}
		}
	}



	double get_ave_cn() {

		double ret = 0.0;

		for (int u = 1; u <= 100; u++) {

			ret += get_clusterNum(u);
		}

		return (ret / 100);
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

	Graph g3 = Graph();

	ifstream ifs{ "edge.txt" };

	int cnt = 0;
	while (g3.linked_components().size() > 1) {

		int vi, vj;
		ifs >> vi >> vj;

		g3.add_edge(vi, vj);

		++cnt;
	}

	Graph g4 = g3;
	int cnt_100 = 0;
	while (cnt_100 < 100) {

		int vi, vj;
		ifs >> vi >> vj;

		g4.add_edge(vi, vj);

		++cnt_100;
		++cnt;
	}

	g3.warshal_floyed();
	g4.warshal_floyed();

	cout << "from 27 to 63\n";
	cout << "G3:" << g3.dists.at(27).at(63) << "  G4:" << g4.dists.at(27).at(63) << "\n";

	cout << "ave diameter\n";
	cout << "G3:" << g3.get_distAve() << "  G4:" << g4.get_distAve() << endl;

	return 0;
}