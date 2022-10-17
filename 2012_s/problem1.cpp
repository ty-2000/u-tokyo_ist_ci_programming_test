
#include<bits/stdc++.h>
using namespace std;

class Game {

public:

	vector<string> stage;

	int posV = 4;
	int posA = 4;

	Game() {

		this->stage = {
			"|---V---|",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|       |",
			"|...A...|",
		};

		show();
	}

	void show() {

		vector<string> graphic = stage;

		graphic.at(0).at(posV) = 'V';
		graphic.at(14).at(posA) = 'A';

		for (auto& e : graphic) {

			cout << e << "\n";
		}
	}
};



int main() {

	Game game = Game();
}