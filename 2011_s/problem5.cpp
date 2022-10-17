#include<bits/stdc++.h>
using namespace std;

string unzip(string& zipped_text);

int main() {

	// file name
	string fileName_1 = "c1.txt";
	string fileName_2 = "c2.txt";

	// get text from textfile
	ifstream ifs_1{ fileName_1 };
	ifstream ifs_2{ fileName_2 };

	string text1, text2;

	getline(ifs_1, text1);
	getline(ifs_2, text2);
	
	// unzip text
	string ans_1 = unzip(text1);
	string ans_2 = unzip(text2);

	//cout << ans_1 << endl;
	//cout << ans_2 << endl;

	cout << "c1.txt の展開結果 : \n";
	cout << " 長さ : " << ans_1.size() << "\n";
	cout << " 末尾10文字 : " << ans_1.substr(ans_1.size() - 10, 10) << "\n";
	
	cout << "c2.txt の展開結果 : \n";
	cout << " 長さ : " << ans_2.size() << "\n";
	cout << " 末尾10文字 : " << ans_2.substr(ans_2.size() - 10, 10) << endl;
}

string unzip(string& zipped_text) {

	string original_text = "";

	for (int i = 0; i < zipped_text.size(); i++) {

		if ('0' <= zipped_text.at(i) && zipped_text.at(i) <= '9') { // num

			int idx = stoi(zipped_text.substr(i, 3));

			if ((i - idx) > 5) {	// 重なっていない

				original_text = original_text + original_text.substr(idx, 6);
			}
			else {	// 重なっている

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
