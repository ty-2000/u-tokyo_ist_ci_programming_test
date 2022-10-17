#include<bits/stdc++.h>
using namespace std;

int solve();

int solve_clever();

vector<long long> generateRondom(int n);

int main() {

	auto ans = solve();

	auto ans_sub = solve_clever();

	cout << ans << endl;
	cout << ans_sub << endl;
}

int solve_clever() {

	int p = 1 << 10;

	int h_prev = 1;
	int h = h_prev;

	long long a_l = 1103515245 % p;
	int a = a_l & 0xffffffff;

	int b_l = 12345 % p;
	int b = b_l & 0xffffffff;

	int k = 0;
	while (true)
	{
		++k;

		h = (a * h_prev + b) % p;
		h_prev = h;

		if (h == 1)	break;
	}

	return k;
}

int solve() {

	int p = 1 << 26;

	int ph = 1 << 10;

	long long g_prev = 1;
	long long g = g_prev;

	int k = 0;
	while (true)
	{
		++k;

		g = (1103515245 * g_prev + 12345) % p;

		g_prev = g;

		int h = g % ph;

		if (h == 1)	break;
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
