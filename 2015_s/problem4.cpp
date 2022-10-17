#include<bits/stdc++.h>
using namespace std;

set<pair<int, string> > getSameline(vector<string>& data);

vector<string> readFile(string fileName);

int main() {

	auto data = readFile("program.txt");

	auto ans = getSameline(data);

	for (auto& line : ans) {

		cout << line.first << " " << line.second << endl;
	}
}

set<pair<int, string> > getSameline(vector<string>& data) {

	set<pair<int, string> >ret;

	unordered_map<string, int> dict;

	int cnt_line = 1;
	for (auto& line : data) {

		if (dict.find(line) == dict.end()) {

			dict.insert({ line, cnt_line });
		}
		else {

			int num_line = dict.at(line);

			ret.insert({ num_line, line });
		}

		cnt_line++;
	}

	return ret;
}

vector<string> readFile(string fileName) {

	vector<string> data;

	ifstream ifs{ fileName };

	string line;
	while (getline(ifs, line)) {

		data.push_back(line);
	}

	return data;
}
