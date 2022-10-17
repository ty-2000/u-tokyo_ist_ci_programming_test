#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
using namespace std;

int V_MAX = 10001;

class DynamicGraph {

public:

	vector<vector<int> > graph;

	vector<vector<int> > Rgraph_rev;

	set<int> V;
	set<pair<int, int> > A;
	set<int> R;

	int time = 0;


	DynamicGraph() {

		graph.resize(V_MAX);

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

		// xがルート集合の要素なら、xの後続をルート集合に追加
		if (R.find(x) != R.end() && Rgraph_rev.at(y).size() <= 1) {

			dfs_makeR(x);
		}
	}

	void del_a(int x, int y) {

		++time;

		A.erase({ x, y });

		graph.at(x).erase(find(graph.at(x).begin(), graph.at(x).end(), y));

		if (R.find(y) != R.end()) {

			dfs_delR(y);
		}
	}

	void s1() {


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
					A.erase({ v, e });
				}
			}

			Rgraph_rev.at(v).clear();
			graph.at(v).clear();

			V.erase(v);
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

	cout << "3-1 " << dg.A.size() <<" " << dg.V.size() << endl;
}
