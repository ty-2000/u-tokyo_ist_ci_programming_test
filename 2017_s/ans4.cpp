#include<bits/stdc++.h>
using namespace std;

int readPicFile(vector<string>& text);

bool isAllBlank(vector<string::iterator>& itrs);

void moveAhead(vector<string::iterator>& itrs);

void makeEmpty(vector<string>& text);

void makeDic(map<vector<string>, int>& dic);

int main() {

	string filename = "out3.txt";

	ifstream ifs{ filename };

	vector<string> text;
	string line;
	while (getline(ifs, line)) {

		text.push_back(line);
	}

	int ans = readPicFile(text);

	cout << ans << endl;
}

int readPicFile(vector<string>& text) {

	// add blank to the last of texts
	for (auto& line : text)	line += " ";

	map<vector<string>, int> dic;	// dictionary
	makeDic(dic);

	string num_str = "";	// number 

	vector<string::iterator> iterators(text.size());	// iterators for search
	
	// set iterators
	for (int i = 0; i < (int)text.size(); i++)	iterators.at(i) = text.at(i).begin();

	// buffer to hold one pic
	vector<string> buf(text.size());

	while (iterators.at(0) != text.at(0).end())
	{
		if (isAllBlank(iterators)) {

			// for each 5 cols, search wether it match to dic
			for (int i = 0; i <= (int)text.size() - 5; i++) {

				vector<string> pic_box(buf.begin() + i, buf.begin() + i + 5);

				if (dic.find(pic_box) != dic.end()) {

					int digit = dic.at(pic_box);

					num_str += to_string(digit);

					break;
				}
			}

			makeEmpty(buf);
		}
		else {

			for (int i = 0; i < (int)buf.size(); i++) {

				buf.at(i) = buf.at(i) + *iterators.at(i);
			}
		}

		moveAhead(iterators);
	}

	return stoi(num_str);
}

bool isAllBlank(vector<string::iterator>& itrs) {

	for (auto& itr : itrs) {

		if (*itr != ' ')	return false;
	}

	return true;
}

void moveAhead(vector<string::iterator>& itrs) {

	for (auto& itr : itrs)	itr++;

	return;
}

void makeEmpty(vector<string>& text) {

	for (auto& line : text) {

		line = "";
	}

	return;
}

void makeDic(map<vector<string>, int>& dic) {

	dic = {
		{{
			"****",
			"|  |",
			"*  *",
			"|  |",
			"****"},
			0},
		{{
			"*",
			"|",
			"*",
			"|",
			"*"
		},	1},
		{{
			"****",
			"   |",
			"****",
			"|   ",
			"****"
		},	2},
		{{
			"****",
			"   |",
			"****",
			"   |",
			"****"
		},	3},
		{{
			"*  *",
			"|  |",
			"****",
			"   |",
			"   *"
		},	4},
		{{
			"****",
			"|   ",
			"****",
			"   |",
			"****"
		},	5 },
		{{
			"*   ",
			"|   ",
			"****",
			"|  |",
			"****"
		},	6},
		{{
			"****",
			"   |",
			"   *",
			"   |",
			"   *"
		},	7},
		{{
			"****",
			"|  |",
			"****",
			"|  |",
			"****"
		},	8},
		{{
			"****",
			"|  |",
			"****",
			"   |",
			"   *"
		},	9}
	};
}