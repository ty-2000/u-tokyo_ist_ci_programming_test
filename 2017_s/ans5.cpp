#include<bits/stdc++.h>
using namespace std;

int readPicFile(vector<string>& text);

int getSimilerNumber(vector<string>& pics, vector<string> &dic);

bool isAllBlank(vector<string::iterator>& itrs);
void moveAhead(vector<string::iterator>& itrs);

bool isAllBlank(vector<string>& text);
void makeEmpty(vector<string>& text);

int getEditDistance(string a, string b);

void makeDic(vector<string> & dic);

int main() {

	string filename = "out5.txt";

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

	vector<string> dic;	// dictionary
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

			if (!isAllBlank(buf)) {

				int d = getSimilerNumber(buf, dic);

				num_str += to_string(d);
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


int getSimilerNumber(vector<string>& pics, vector<string>& dic) {

	vector<int> edit_dists(10, 1 << 25);

	for (int i = 0; i <= (int)pics.size() - 5; ++i) {

		string pic_line = "";
		for (int j = i; j < i + 5; ++j) {

			pic_line += pics.at(j);
		}

		for (int num = 0; num <= 9; ++num) {

			int d = getEditDistance(pic_line, dic.at(num));

			if (edit_dists.at(num) > d)	edit_dists.at(num) = d;
		}
	}

	return min_element(edit_dists.begin(), edit_dists.end()) - edit_dists.begin();
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

bool isAllBlank(vector<string>& text) {

	for (auto& line : text) {

		for (auto& e : line) {

			if (e != ' ')	return false;
		}
	}

	return true;
}

void makeEmpty(vector<string>& text) {

	for (auto& line : text) {

		line = "";
	}

	return;
}

int getEditDistance(string a, string b) {

	a = " " + a;
	b = " " + b;

	vector<vector<int> > dp(a.size(), vector<int>(b.size()));

	for (int i = 0; i < a.size(); ++i) {

		dp.at(i).at(0) = i;
	}

	for (int j = 0; j < b.size(); ++j) {

		dp.at(0).at(j) = j;
	}

	for (int i = 1; i < (int)a.size(); ++i) {

		for (int j = 1; j < (int)b.size(); ++j) {

			if (a.at(i) == b.at(j)) {

				dp.at(i).at(j) = min({
					dp.at(i - 1).at(j -1),
					dp.at(i).at(j - 1) + 1,
					dp.at(i - 1).at(j) + 1 });
			}
			else {

				dp.at(i).at(j) = min({
					dp.at(i - 1).at(j - 1) + 1,
					dp.at(i).at(j - 1) + 1,
					dp.at(i - 1).at(j) + 1
					});
			}
		}
	}

	return dp.at(a.size() - 1).at(b.size() - 1);
}

void makeDic(vector<string>& dic) {

	dic.clear();

	vector<vector<string> > dic_num_to_pic = {
		{
			"****",
			"|  |",
			"*  *",
			"|  |",
			"****"
		},
		{
			"*",
			"|",
			"*",
			"|",
			"*"
		},
		{
			"****",
			"   |",
			"****",
			"|   ",
			"****"
		},
		{
			"****",
			"   |",
			"****",
			"   |",
			"****"
		},
		{
			"*  *",
			"|  |",
			"****",
			"   |",
			"   *"
		},
		{
			"****",
			"|   ",
			"****",
			"   |",
			"****"
		},
		{
			"*   ",
			"|   ",
			"****",
			"|  |",
			"****"
		},
		{
			"****",
			"   |",
			"   *",
			"   |",
			"   *"
		},
		{
			"****",
			"|  |",
			"****",
			"|  |",
			"****"
		},
		{
			"****",
			"|  |",
			"****",
			"   |",
			"   *"
		},
	};

	for (auto& pic : dic_num_to_pic) {

		string str = "";

		for (auto& s : pic) {

			str += s;
		}

		dic.push_back(str);
	}

	return;
}
