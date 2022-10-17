#include<bits/stdc++.h>
using namespace std;

void makefile_edge_text() {

	vector<string> data(4950);

	ofstream ofs{ "edge.txt" };

	int idx = 0;

	for (int i = 1; i <= 100; i++) {

		for (int j = i + 1; j <= 100; j++) {

			string str = to_string(i) + " ";
			str += to_string(j);

			data.at(idx++) = str;
		}
	}

	shuffle(data.begin(), data.end(), mt19937{});

	for (auto& e : data) {

		ofs << e << "\n";
	}
	ofs << flush;
}

int main() {

	makefile_edge_text();
}