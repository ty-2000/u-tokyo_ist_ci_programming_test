#include<bits/stdc++.h>
using namespace std;

int countSemicolon(string str);

vector<string> readFile(string fileName);

int main() {

	auto data = readFile("program.txt");

	int cnt = 0;
	for (auto& line : data) {

		cnt += countSemicolon(line);
	}

	cout << cnt << endl;
}

int countSemicolon(string str) {

	int cnt = 0;
	for (auto itr = str.begin(); itr != str.end(); itr++) {

		if (*itr == ';')	cnt++;
	}

	return cnt;
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
