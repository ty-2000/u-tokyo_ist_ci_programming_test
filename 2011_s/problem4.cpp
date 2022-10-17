#include<bits/stdc++.h>
using namespace std;

// zip
string zip(string& text);

// to make 3 digit String from int
string to_3digitstr(int num);

// make dictionary
void makeDictionary(unordered_map<string, int>& dict, string& text);

int main() {

	// file name
	string fileName = "s1.txt";
	ifstream ifs{ fileName };

	// text in the file
	string str;
	getline(ifs, str);

	string text_zipped = zip(str);

	//cout << text_zipped << endl;	// ˆ³kƒf[ƒ^o—Í

	cout << "ˆ³k•¶Žš—ñ‚Ì’·‚³ : " << text_zipped.size() << "\n";

	cout << "––”ö10•¶Žš : " << text_zipped.substr(text_zipped.size() - 10, 10);
}

// zip
string zip(string& text) {

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
