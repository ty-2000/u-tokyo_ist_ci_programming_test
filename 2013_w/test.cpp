#include<bits/stdc++.h>

using namespace std;

int main() {

	set<vector<int> > s;

	vector<int> a = { 0, 0, 0 };
	vector<int> b = { 0, 0, 1 };
	vector<int> c = { 0, 1, 0 };

	s.insert(a);
	s.insert(b);
	s.insert(c);
	s.insert(a);


	for (auto& e : s) {

		for (int i = 0; i < 3; i++) {

			cout << e.at(i);
		}

		cout << endl;
	}
}