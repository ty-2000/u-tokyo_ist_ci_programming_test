#include<bits/stdc++.h>
using namespace std;

vector<string> readFile(string fileName);

int main() {

	auto data = readFile("program.txt");

	int cnt = 1;
	for (auto& line : data) {

		cout << format("{:<3}", cnt) << flush;
		cout << line << endl;

		cnt++;
	}
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
