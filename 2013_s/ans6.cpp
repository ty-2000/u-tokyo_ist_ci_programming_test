#include<bits/stdc++.h>
using namespace std;

using command = tuple<string, string, string>;

void runProgram(vector<command>& commands);

int callFunction(vector<command>& commands, int pc, int in);

int valueof(string value_name, map<string, int>& valuables) {

	if ('a' <= value_name.at(0) && value_name.at(0) <= 'z') {

		return valuables[value_name];
	}

	return stoi(value_name);
}

vector<command> readFileAsProgram(string filename);

int main() {

	vector<command> commands = readFileAsProgram("prog5.txt");

	runProgram(commands);

	return 0;
}

void runProgram(vector<command>& commands) {

	// stroage of valuables
	map<string, int> valuables;

	// program counter
	int pc = 0;

	// stack for subroutine
	stack<int> st_returning_point;


	while (pc < (int)commands.size()) {

		string operation = get<0>(commands.at(pc));
		string val1_str = get<1>(commands.at(pc));
		string val2_str = get<2>(commands.at(pc));

		if (operation == "SET") {

			valuables[val1_str] = valueof(val2_str, valuables);
		}
		else if (operation == "ADD") {

			valuables[val2_str] += valueof(val1_str, valuables);
		}
		else if (operation == "CMP") {

			if (valueof(val1_str, valuables) == valueof(val2_str, valuables)) {

				pc += 2;
				continue;
			}
		}
		else if (operation == "JMP") {

			pc += valueof(val1_str, valuables);

			continue;
		}
		else if (operation == "SUB") {

			st_returning_point.push(pc);

			pc += valueof(val1_str, valuables);

			continue;
		}
		else if (operation == "BAK") {

			pc = st_returning_point.top();

			st_returning_point.pop();
		}
		else if (operation == "CAL") {

			int out = callFunction(commands, pc + valueof(val1_str, valuables), valueof(val2_str, valuables));

			valuables.insert({ "out", out });
		}
		else if (operation == "PRN") {

			cout << valueof(val1_str, valuables) << " " << valueof(val2_str, valuables) << endl;

			return;
		}

		++pc;
	}

	return;
}

int callFunction(vector<command>& commands, int pc, int in) {

	// stroage of valuables
	map<string, int> valuables;

	valuables.insert({ "in", in });

	// program counter
	int pc = 0;

	// stack for subroutine
	stack<int> st_returning_point;


	while (pc < (int)commands.size()) {

		string operation = get<0>(commands.at(pc));
		string val1_str = get<1>(commands.at(pc));
		string val2_str = get<2>(commands.at(pc));

		if (operation == "SET") {

			valuables[val1_str] = valueof(val2_str, valuables);
		}
		else if (operation == "ADD") {

			valuables[val2_str] += valueof(val1_str, valuables);
		}
		else if (operation == "CMP") {

			if (valueof(val1_str, valuables) == valueof(val2_str, valuables)) {

				pc += 2;
				continue;
			}
		}
		else if (operation == "JMP") {

			pc += valueof(val1_str, valuables);

			continue;
		}
		else if (operation == "SUB") {

			st_returning_point.push(pc);

			pc += valueof(val1_str, valuables);

			continue;
		}
		else if (operation == "BAK") {

			pc = st_returning_point.top();

			st_returning_point.pop();
		}
		else if (operation == "CAL") {

			int out = callFunction(commands, pc + valueof(val1_str, valuables), valueof(val2_str, valuables));

			valuables.insert({ "out", out });
		}
		else if (operation == "RET") {

			return valueof(val2_str, valuables);
		}
		else if (operation == "PRN") {

			cout << valueof(val1_str, valuables) << " " << valueof(val2_str, valuables) << endl;

			return -1;
		}

		++pc;
	}

	return -1;
}

vector<command > readFileAsProgram(string filename) {

	vector<command > commands;

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
