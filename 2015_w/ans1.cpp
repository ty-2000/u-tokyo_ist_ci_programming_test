#include<bits/stdc++.h>
using namespace std;

vector<long long> generateRondom(int n);

int main() {

	int n;
	cin >> n;

	vector<long long> f = generateRondom(n);

	auto ans = f.at(n);

	cout << ans << endl;
}

vector<long long> generateRondom(int n) {

	vector<long long> f(n + 1, 1LL);

	int p = 1 << 24;

	for (int i = 1; i <= n; i++) {

		f.at(i) = (161 * f.at(i - 1) + 2457) % p;
	}

	return f;
}
