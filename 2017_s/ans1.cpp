#include<bits/stdc++.h>
using namespace std;

void makePicFile(int num, string filename);

void pushBlank(int space_size, vector<string>& data);

void makeSet(vector<vector<string> > &dic_num_to_pic);

int main() {

	int num;
	cin >> num;

	makePicFile(num, "out1.txt");
}

void makePicFile(int num, string filename) {

	vector<vector<string> > dic;
	makeSet(dic);

	vector<string> output_data(5);

	string num_str = to_string(num);

	for (auto itr = num_str.begin(); itr != num_str.end(); itr++) {

		int digit = *itr - '0';

		if (itr != num_str.begin())	pushBlank(2, output_data);

		vector<string> pic = dic.at(digit);

		for (int i = 0; i < output_data.size(); i++) {

			output_data.at(i) += pic.at(i);
		}
	}

	ofstream ofs{ filename };

	for (auto& line : output_data) {

		ofs << line << endl;
	}

	return;
}

void pushBlank(int space_size, vector<string>& data) {

	string blank = "";
	for (int i = 0; i < space_size; i++)	blank += " ";

	for (int i = 0; i < data.size(); i++) {

		data.at(i) += blank;
	}

	return;
}

void makeSet(vector<vector<string> >& dic_num_to_pic) {

	dic_num_to_pic = {
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

	return;
}

