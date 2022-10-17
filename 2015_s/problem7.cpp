#include<bits/stdc++.h>
using namespace std;

vector<vector<string> > getSameBlock(vector<string>& data);

vector<string> subtractBlock(int first, int size, vector<string> &data);

vector<string> readFile(string fileName);

int main() {

	auto data = readFile("program.txt");

	auto ans = getSameBlock(data);

	for (auto& block : ans) {

		for (int i = 0; i < (int)block.size(); i++) {

			cout << block.at(i) << "\n";
		}
		cout << endl;
	}
}

vector<vector<string> > getSameBlock(vector<string>& data) {

	// ブロックの始めのインデックスとブロックサイズ
	map<int, int> dict;

	const int min_block_size = 4;

	for (int size = min_block_size; size < (int)data.size() - 1; size++) {

		for (int i = 0; i < (int)data.size() - size; i++) {

			for (int j = i + 1; j < (int)data.size() - size; j++) {

				if (subtractBlock(i, size, data) == subtractBlock(j, size, data)) {

					dict[i] = size;
					for (int first = i + 1; first < i + size; first++) {

						if (dict.find(first) != dict.end() && first + dict[first] <= i + size) {

							dict.erase(first);
						}
					}
				}
			}
		}
	}

	vector<vector<string> > ret;
	for (auto& e : dict) {

		ret.push_back(subtractBlock(e.first, e.second, data));
	}

	return ret;
}

vector<string> subtractBlock(int first, int size, vector<string>& data) {

	vector<string> ret(data.begin() + first, data.begin() + first + size);

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
