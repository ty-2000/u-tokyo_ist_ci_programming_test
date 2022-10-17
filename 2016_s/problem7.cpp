#include<bits/stdc++.h>

using namespace std;

int enToInteger(string &en);

int main() {

	string en;

	getline(cin, en);

	int ans = enToInteger(en);

	cout << ans << endl;
}


int enToInteger(string& en) {

	unordered_map<string, int> dict = {

		{"one", 1},
		{ "two", 2 },
		{ "three", 3 },
		{ "four", 4 },
		{ "five", 5 },
		{ "six", 6 },
		{ "seven", 7 },
		{ "eight", 8 },
		{ "nine", 9 },
		{ "ten", 10 },
		{ "eleven", 11 },
		{ "twelve", 12 },
		{ "thirteen", 13 },
		{ "fourteen", 14 },
		{ "fifteen", 15 },
		{ "sixteen", 16 },
		{ "seventeen", 17 },
		{ "eighteen", 18 },
		{ "nineteen", 19 },
		{ "twenty", 20 },
		{ "thirty", 30 },
		{ "forty", 40 },
		{ "fifty", 50 },
		{ "sixty", 60 },
		{ "seventy", 70 },
		{ "eighty", 80 },
		{ "ninety", 90 },
		{ "hundred", 100 },
		{ "thousand", 1000 },
	};

	en = en + " one";

	stringstream ss{ en };

	int ans = 0;
	int buf = 0;

	while (!ss.eof()) {

		string str;

		ss >> str;

		int currentNum = dict.at(str);
		if (currentNum == 1 || currentNum == 10 || currentNum == 100 || currentNum == 1000) {

			ans += buf * currentNum;
			buf = 0;
		}
		else {

			buf += currentNum;
		}
	}

	return ans;
}