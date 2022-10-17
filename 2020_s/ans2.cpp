#include<bits/stdc++.h>
using namespace std;

// return size of unzipped data 
int unZip(string input_filename, string output_filename);

void readFileAsBinary(vector<char>& data, string filename);

int main() {

	int ans_2a = unZip("data2a.bin", "data2a.txt");

	cout << ans_2a << endl;
}

int unZip(string input_filename, string output_filename) {

	// read binary file
	vector<char> input_data;
	readFileAsBinary(input_data, input_filename);

	vector<char> output_data;

	for (int i = 0; i < (int)input_data.size(); ++i) {

		char c = input_data.at(i);

		if (c)	output_data.push_back(c);	// non zero
		else {		// zero
				
			char p = input_data.at(i + 1);
			char d = input_data.at(i + 2);

			for (int j = i - p; j < i - p + d; ++j) {

				output_data.push_back(input_data.at(j));
			}

			i += 2;
		}
	}

	ofstream ofs{ output_filename, ios_base::binary };

	for (auto& e : output_data) {

		ofs << e;
	}

	return output_data.size();
}


void readFileAsBinary(vector<char>& data, string filename) {

	ifstream ifs{ filename , ios_base::binary};

	typedef istreambuf_iterator<char> iter_type;

	data.assign(iter_type{ ifs }, iter_type{});

	return;
}
