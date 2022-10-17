#include<bits/stdc++.h>
using namespace std;

vector<long long> generateRondom(int n);

int main() {

	int n = 99;

	vector<long long> f = generateRondom(n);

	int cnt_even = 0;
	for (int i = 0; i <= n; i += 2) {

		if (f.at(i) & 1) cnt_even++;
	}

	cout << cnt_even << endl;
}

vector<long long> generateRondom(int n) {

	vector<long long> f(n + 1, 1LL);

	int p = 1 << 24;

	for (int i = 1; i <= n; i++) {

		f.at(i) = (161 * f.at(i - 1) + 2457) % p;
	}

	return f;
}
