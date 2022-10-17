#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
using namespace std;

int V_MAX = 10001;

class DynamicGraph {

public:

	vector<vector<int> > graph;
	vector<vector<int> > graph_rev;

	vector<vector<int> > Rgraph_rev;

	set<int> V;
	set<pair<int, int> > A;
	set<int> R;

	int time = 0;

	// for prob2
	vector<int> trVec;
	int size_prevR = 1;

	DynamicGraph() {

		graph.resize(V_MAX);
		graph_rev.resize(V_MAX);

		Rgraph_rev.resize(V_MAX);

		V.insert(0);
		R.insert(0);
	}

	void add_va(int x, int y) {

		++time;

		if (V.find(x) == V.end())	return;

		// グラフに挿入
		V.insert(x);
		V.insert(y);
		A.insert({ x, y });

		graph.at(x).push_back(y);
		graph_rev.at(y).push_back(x);

		// xがルート集合の要素なら、yとyの後続をルート集合に追加

	}

	void del_a(int x, int y) {

		++time;

		A.erase({ x, y });

		graph.at(x).erase(find(graph.at(x).begin(), graph.at(x).end(), y));
		graph_rev.at(y).erase(find(graph_rev.at(y).begin(), graph_rev.at(y).end(), x));

		if (graph_rev.at(y).size() == 0) {
			
			dfs_delVertex(y);
		}
	}

	void dfs_delVertex(int u) {

		map<int, bool> visited;

		stack<int> st;
		st.push(u);

		while (!st.empty()) {

			int v = st.top(); st.pop();

			visited[v] = true;

			for (auto& e : graph.at(v)) {

				if (1 < graph_rev.at(e).size()) {

					continue;
				}
				else if (visited[e] == false) {

					st.push(e);
					A.erase({ v, e });
				}
			}

			V.erase(v);

			graph.at(v).clear();
			graph_rev.at(v).clear();
		}

		return;
	}

	void dfs_delR(int u) {

		map<int, bool> visited;

		stack<int> st;
		st.push(u);

		while (!st.empty()) {

			int v = st.top(); st.pop();

			visited[v] = true;

			for (auto& e : graph.at(v)) {

				if (1 < Rgraph_rev.at(e).size()) {

					continue;
				}
				else if (visited[e] == false) {

					st.push(e);
				}
			}

			Rgraph_rev.at(v).clear();
			R.erase(v);
		}

		return;
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
				}
			}
		}

		return;
	}
};

int main() {

	DynamicGraph dg = DynamicGraph();

	string fileName = "b.txt";
	ifstream ifs{ fileName };

	string command;
	std::smatch m;
	while (getline(ifs, command)) {

		regex_match(command, m, regex(R"((!*)(\d+)->(\d+))"));
		int x = stoi(m[2].str());
		int y = stoi(m[3].str());

		if (m[1].str() == "!") {

			dg.del_a(x, y);
		}
		else {

			dg.add_va(x, y);
		}
	}

	cout << "3-2 " << dg.V.size() << endl;
}
