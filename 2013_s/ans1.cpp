#include<bits/stdc++.h>
using namespace std;

vector<tuple<string, string, string> > readFileAsProgram(string filename);

int main() {

	auto commands = readFileAsProgram("prog1.txt");

	for (auto& command : commands) {

		cout << get<1>(command) << endl;
	}

	return 0;
}

vector<tuple<string, string, string> > readFileAsProgram(string filename) {

	vector<tuple<string, string, string> > commands;

	ifstream ifs{ filename };

	string line;
	while (getline(ifs, line)) {

		string opr;
		string a;
		string b;

		stringstream ss;
		ss << line;

		ss >> opr >> a >> b;

		commands.push_back(make_tuple(opr, a, b));
	}

	return commands;
}
