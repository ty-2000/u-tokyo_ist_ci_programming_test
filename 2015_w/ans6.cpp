#include<bits/stdc++.h>
using namespace std;

int solve();

vector<long long> generateRondom(int n);

int main() {

	auto ans = solve();

	cout << ans << endl;
}

int solve() {

	int p = 1 << 26;

	long long g_prev = 1;
	long long g = g_prev;

	int k = 0;
	while (true)
	{
		++k;

		g = (1103515245 * g_prev + 12345) % p;

		g_prev = g;

		if (g == 1)	break;
	}

	return k;
}

vector<long long> generateRondom(int n) {

	vector<long long> g(n + 1, 1LL);

	int p = 1 << 26;

	for (int i = 1; i <= n; i++) {

		g.at(i) = (1103515245 * g.at(i - 1) + 12345) % p;
	}

	return g;
}
