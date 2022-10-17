#include<bits/stdc++.h>

using namespace std;

vector<string> split(string text, char splitter);

int main() {

	string str;
	getline(cin, str);

	auto ans = split(str, '+');

	for (auto& e : ans) {

		cout << e << endl;
	}

	return 0;
}

vector<string> split(string text, char splitter) {

	text = text + splitter;

	vector<string> ret;
	string buf = "";

	for (auto itr = text.begin(); itr != text.end(); itr++) {

		if (*itr == splitter) {

			if (buf.size() > 0) {

				ret.push_back(buf);

				buf.clear();
			}
			else {

				continue;
			}
		}
		else {

			buf = buf + *itr;
		}
	}

	return ret;
}
