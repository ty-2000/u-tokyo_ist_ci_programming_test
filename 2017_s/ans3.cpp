#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

void makePicFile(int num, vector<int> top_space, vector<int> inter_space, string filename);

void pushBlank(int space_size, vector<string>& data);

string space(int space_size);

void makeSet(vector<vector<string> >& dic_num_to_pic);

int main() {

	string input_text;
	cin >> input_text;

	std::vector<string> result;
	boost::algorithm::split(result, input_text, boost::is_any_of(","));

	int num = 0;
	vector<int> top_spaces;
	vector<int> inter_spaces;

	num = stoi(result.at(0));

	for (int i = 1; i < result.size(); ++i) {

		if (i & 1) {

			top_spaces.push_back(stoi(result.at(i)));
		}
		else {

			inter_spaces.push_back(stoi(result.at(i)));
		}
	}

	makePicFile(num, top_spaces, inter_spaces, "out3.txt");
}

void makePicFile(int num, vector<int> top_space, vector<int> inter_space, string filename){

	// make dictionary
	vector<vector<string> > dic;
	makeSet(dic);

	// add sentinel
	inter_space.push_back(0);

	// height
	int num_line = (*max_element(top_space.begin(), top_space.end()) + 5);

	vector<string> output_data(num_line);

	string num_str = to_string(num);


	for (int i_char = 0; i_char < (int)num_str.size(); i_char++) {

		int digit = num_str.at(i_char) - '0';	// num

		vector<string> pic = dic.at(digit);		// pic

		int width = pic.at(0).size();			// width of pic

		string blank = space(width);

		// put pic to text with top space
		for (int i = 0; i < (int)output_data.size(); ++i) {

			if (i < top_space.at(i_char)) {		// top

				output_data.at(i) += blank;
			}
			else if (i < top_space.at(i_char) + 5) {	// middle

				output_data.at(i) += pic.at(i - top_space.at(i_char));
			}
			else {	// buttom

				output_data.at(i) += blank;
			}
		}
		pushBlank(inter_space.at(i_char), output_data);

	}

	ofstream ofs{ filename };

	for (auto& line : output_data) {

		ofs << line << endl;
	}

	return;
}

string space(int space_size) {

	string ret = "";
	for (int i = 0; i < space_size; ++i) {

		ret += " ";
	}

	return ret;
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

