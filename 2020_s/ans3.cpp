#include<bits/stdc++.h>
using namespace std;

int encode(string input_filename, string output_filename);

pair<int, int> getLongestSamePart(vector<char>& dic, vector<char> &key);

void readFileAsBinary(vector<char>& data, string filename);

int main() {

	int ans = encode("data3a.txt", "data3a.bin");

	cout << ans << endl;
}

int encode(string input_filename, string output_filename) {

	vector<char> original_data;
	readFileAsBinary(original_data, input_filename);

	vector<char> output_data;

	while(!original_data.empty()){

		pair<int, int> p = getLongestSamePart(output_data, original_data);

		int len = p.first;
		int rev = p.second;

		if (len < 4) {

			output_data.push_back(original_data.at(0));

			original_data.erase(original_data.begin());
		}
		else {

			output_data.push_back(0);
			output_data.push_back((char)rev);
			output_data.push_back((char)len);

			original_data.erase(original_data.begin(), original_data.begin() + len);

		}
	}

	ofstream ofs{ output_filename, ios_base::binary };

	for (auto& e : output_data) {

		ofs << e;
	}

	return (int)output_data.size();
}

pair<int, int> getLongestSamePart(vector<char>& dic, vector<char> &key) {

	int length_max = 0;
	int rev_size = 0;

	auto itr_first = find(dic.begin(), dic.end(), key.at(0));

	while (itr_first != dic.end()) {

		int length = 0;

		for (int i = 0; i < min(256, (int)key.size()); i++) {

			if (key.at(i) != *(itr_first + i))	break;

			++length;
		}

		if (length_max < length) {

			length_max = length;

			rev_size = (dic.end() - itr_first);
		}

		itr_first = find(itr_first + 1, dic.end(), key.at(0));
	}

	return make_pair(length_max, rev_size);
}

void readFileAsBinary(vector<char>& data, string filename) {

	ifstream ifs{ filename , ios_base::binary };

	typedef istreambuf_iterator<char> iter_type;

	data.assign(iter_type{ ifs }, iter_type{});

	return;
}