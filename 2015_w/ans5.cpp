#include<bits/stdc++.h>
using namespace std;

vector<long long> generateRondom(int n);

int main() {

	int n = 3;

	vector<long long> g = generateRondom(n);

	cout << g.at(2) << endl;
	cout << g.at(3) << endl;
}

vector<long long> generateRondom(int n) {

	vector<long long> g(n + 1, 1LL);

	int p = 1 << 26;

	for (int i = 1; i <= n; i++) {

		g.at(i) = (1103515245 * g.at(i - 1) + 12345) % p;
	}

	return g;
}
