#include<bits/stdc++.h>
using namespace std;

vector<string> decodeCaesar(vector<string> text, int key);

vector<string> readFileAsText(string file_name);

void showText(vector<string>& text);

int main() {

	vector<string> text = readFileAsText("q1.txt");
	

	int key = 0;

	while ((cin >> key)) {

		auto res = decodeCaesar(text, key);

		showText(res);
	}

	cout << key << endl;
}

vector<string> decodeCaesar(vector<string> text, int key) {

	vector<string> originalText;

	for (auto& line : text) {

		for (auto itr = line.begin(); itr != line.end(); itr++) {

			if ('A' <= *itr && *itr <= 'Z') {

				*itr = (*itr - key - 'A' + 26) % 26 + 'A';
			}
			else if ('a' <= *itr && *itr <= 'z') {

				*itr = (*itr - key - 'a' + 26) % 26 + 'a';
			}
		}
	}

	return text;
}

vector<string> readFileAsText(string file_name) {

	ifstream ifs{ file_name };

	string line;
	vector<string> ret;

	while (getline(ifs, line)) {

		ret.push_back(line);
	}

	return ret;
}

void showText(vector<string>& text) {

	for (auto& line : text) {

		cout << line << "\n";
	}
}