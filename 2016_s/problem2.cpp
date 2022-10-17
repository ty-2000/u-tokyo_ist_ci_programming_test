#include<bits/stdc++.h>

using namespace std;

int hexToDecimal(string hexNum);

int main() {

	string str;
	cin >> str;

	int ans = hexToDecimal(str);

	cout << ans << endl;
}

int hexToDecimal(string hexNum) {

	auto ritr = hexNum.rbegin();

	int ans = 0;

	int i = 1;
	while (ritr != hexNum.rend()) {

		ans += i * (*ritr - 'a');

		i *= 8;
		ritr++;
	}

	return ans;
}
