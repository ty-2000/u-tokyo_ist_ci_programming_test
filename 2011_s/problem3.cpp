#include<bits/stdc++.h>
using namespace std;

// make dictionary
void makeDictionary(unordered_map<string, int>& dict, string &text);

int main(){

	// file name
	string fileName = "s1.txt";
	ifstream ifs{ fileName };

	// text in the file
	string str;
	getline(ifs, str);

	unordered_map<string, int> dict;

	makeDictionary(dict, str);

	cout << "Ž«‘‚ÌƒTƒCƒY : " << dict.size() << endl;
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
