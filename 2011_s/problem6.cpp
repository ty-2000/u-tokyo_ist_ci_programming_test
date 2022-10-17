#include<bits/stdc++.h>
using namespace std;

// unzip main
string unzip(string& zipped_text);
// unzip_sub
string unzip_sub(string& zipped_text);


// zip main
string zip(string& text);

// zip_sub
string zip_sub(string& text);

// to make 3 digit String from int
string to_3digitstr(int num);

// make dictionary
void makeDictionary(unordered_map<string, int>& dict, string& text);

int main() {

	string fileName = "s3.txt";

	ifstream ifs{ fileName };

	string text;
	getline(ifs, text);

	string zipped_text = zip(text);

	cout << zipped_text << endl;

	string original_text = unzip(zipped_text);

	cout << original_text << endl;
}

string unzip(string& zipped_text) {

	string original_text = "";

	int i = 0;
	while (i < zipped_text.size())
	{
		string blockstr = zipped_text.substr(i, min(1000, (int)zipped_text.size() - i));

		original_text = original_text + unzip_sub(blockstr);

		i += 1000;
	}

	return original_text;
}

string unzip_sub(string& zipped_text) {

	string original_text = "";

	for (int i = 0; i < zipped_text.size(); i++) {

		if ('0' <= zipped_text.at(i) && zipped_text.at(i) <= '9') { // num

			int idx = stoi(zipped_text.substr(i, 3));

			if ((i - idx) > 5) {	// èdÇ»Ç¡ÇƒÇ¢Ç»Ç¢

				original_text = original_text + original_text.substr(idx, 6);
			}
			else {	// èdÇ»Ç¡ÇƒÇ¢ÇÈ

				for (int j = 0; j < 6; j++) {

					original_text = original_text + original_text.at(idx + j);
				}
			}

			i += 2;
		}
		else {	// character

			original_text = original_text + zipped_text.at(i);
		}
	}

	return original_text;
}

string zip(string& text) {

	string zipped_text = "";

	int i = 0;
	while (i < text.size())
	{
		string blockstr = text.substr(i, min(1000, (int)text.size() - i));

		zipped_text = zipped_text + zip_sub(blockstr);

		i += 1000;
	}

	return zipped_text;

}

// zip_sub
string zip_sub(string& text) {

	text = text + "&&&&&";

	unordered_map<string, int> dict;

	makeDictionary(dict, text);

	string text_zipped = "";

	for (int i = 0; i < text.size() - 5; i++) {

		string partialText = text.substr(i, 6);

		if (dict.at(partialText) == i) {

			text_zipped = text_zipped + text.at(i);
		}
		else {

			text_zipped = text_zipped + to_3digitstr(dict.at(partialText));

			i += 5;
		}
	}

	return text_zipped;
}

string to_3digitstr(int num) {

	string ret = "";

	if (num < 10) {

		ret = "00" + to_string(num);
	}
	else if (num < 100) {

		ret = "0" + to_string(num);
	}
	else {
		ret = to_string(num);
	}

	return ret;
}

void makeDictionary(unordered_map<string, int>& dict, string& text) {

	auto itr = text.begin();

	while (itr != text.end() - 5)
	{
		string partialText(itr, itr + 6);

		if (dict.find(partialText) == dict.end()) {	// if not extist

			// insert to dictionary
			dict.insert({ partialText, (itr - text.begin()) });
		}
		itr++;
	}

	return;
}
