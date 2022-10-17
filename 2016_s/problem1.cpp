#include<bits/stdc++.h>

using namespace std;

int quadrantToDecimal(string quadrantNum);

int main() {

	string quadrantNum;
	cin >> quadrantNum;

	int ans = quadrantToDecimal(quadrantNum);

	cout << ans << endl;
}

int quadrantToDecimal(string quadrantNum) {

	auto ritr = quadrantNum.rbegin();

	int ans = 0;

	int i = 1;
	while (ritr != quadrantNum.rend()) {

		ans += i * (*ritr - '0');

		i *= 4;
		ritr++;
	}

	return ans;
}