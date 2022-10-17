#include<bits/stdc++.h>
using namespace std;

vector<string> getSubsequenceSameline(vector<string>& program);

vector<string> readFile(string fileName);

int main() {

	auto data = readFile("program.txt");

	auto ans = getSubsequenceSameline(data);

	for (auto& line : ans) {

		cout << line << endl;
	}
}

vector<string> getSubsequenceSameline(vector<string>& program) {

	vector<string> ret;

	bool block = false;
	string tmp = "";
	for (auto& line : program) {

		if (tmp == line) {

			if (!block) {

				ret.push_back(line);
				block = true;
			}
		}
		else {

			block = false;
			tmp = line;
		}
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
