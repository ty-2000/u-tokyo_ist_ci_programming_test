#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
using namespace std;

int V_MAX = 10001;

class DynamicGraph {

public:

	vector<vector<int> > graph;
	vector<vector<int> > graph_rev;

	vector<vector<int> > Rgraph;
	vector<vector<int> > Rgraph_rev;

	set<int> V;
	set<pair<int, int> > A;
	set<int> R;

	int time = 0;

	// for problem1
	int tv = 1 << 29;
	int tr = 1 << 29;

	pair<int, int> out_max = { 0, 0 };	// val, vertexId
	pair<int, int> in_max = { 0, 0 };

	int t_cycle = 1 << 29;

	DynamicGraph() {

		graph.resize(V_MAX);
		graph_rev.resize(V_MAX);

		Rgraph.resize(V_MAX);
		Rgraph_rev.resize(V_MAX);

		V.insert(0);
		R.insert(0);
	}

	void add_va(int x, int y) {

		++time;

		// グラフに挿入
		V.insert(x);
		V.insert(y);
		A.insert({ x, y });

		graph.at(x).push_back(y);
		graph_rev.at(y).push_back(x);

		// for prob1
		if (time < tv && 1000 <= V.size())	tv = time;
		if (time < tr && 1000 <= R.size())	tr = time;

		if (out_max.first < (int)graph.at(x).size())	out_max = { graph.at(x).size(), x };
		if (in_max.first < (int)graph_rev.at(y).size()) in_max = { graph_rev.at(y).size(), y };

		// xがルート集合の要素なら、xの後続をルート集合に追加
		if (R.find(x) != R.end()) {

			dfs_makeR(x);
		}
	}

	void dfs_makeR(int u) {

		map<int, bool> visited;

		stack<int> st;

		st.push(u);

		while (!st.empty()) {

			int v = st.top();	st.pop();

			visited[v] = true;

			for (auto& e : graph.at(v)) {

				if (visited[e] == false) {

					st.push(e);
					R.insert(e);
					Rgraph_rev.at(e).push_back(v);

					if (e == 0)	t_cycle = time;
				}
			}
		}
		return;
	}

};

int main() {

	DynamicGraph dg = DynamicGraph();

	string fileName = "a.txt";
	ifstream ifs{ fileName };

	string command;
	while (getline(ifs, command)) {

		vector<string> res;
		boost::algorithm::split(res, command, boost::is_any_of("->"));

		int x = stoi(res.at(0));
		int y = stoi(res.at(2));

		dg.add_va(x, y);
	}

	cout << "1-1 " << dg.V.size() << endl;
	cout << "1-2 " << dg.out_max.second << " " << dg.out_max.first << endl;
	cout << "1-2 " << dg.in_max.second << " " << dg.in_max.first << endl;
	cout << "1-3 " << "tv:" << dg.tv << " tr:" << dg.tr << endl;
	cout << "1-4 " << dg.t_cycle << endl;
}
