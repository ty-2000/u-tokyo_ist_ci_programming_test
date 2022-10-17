#include<bits/stdc++.h>

using namespace std;

int romanToDecimal(string romanNum);

int main() {

	string str;
	cin >> str;

	int ans = romanToDecimal(str);

	cout << ans << endl;
}


int romanToDecimal(string romanNum) {

	unordered_map<char, int> romanMap = {
		{'I', 1},
		{'V', 5},
		{'X', 10},
		{'L', 50},
		{'C', 100},
		{'D', 500},
		{'M', 1000},
	};

	int ans = 0;

	for (auto itr = romanNum.begin(); itr != romanNum.end(); itr++) {

		// reverse
		if (itr+1 != romanNum.end() && romanMap[*itr] < romanMap[*(itr + 1)]) {

			ans -= romanMap[*itr];
		}
		else {

			ans += romanMap[*itr];
		}
	}

	return ans;
}
