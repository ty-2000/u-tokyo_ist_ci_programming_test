
#include<bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace chrono;


vector<string> graphic;

const int RIGHT = 0;
const int LEFT = 1;

struct Target
{
	int pos_i;
	int pos_j;

	int j_extended;

	Target() {}
	Target(int i, int j) {

		this->pos_i = i;
		this->pos_j = j;

		this->j_extended = j;
	}

	void move() {

		this->pos_i++;

		j_extended++;
		if (j_extended < 9)	pos_j = j_extended;
		else if (j_extended < 16)	pos_j = 15 - j_extended;
		else    pos_j = j_extended - 15;
	}

	void set(int i, int j) {
		pos_i = i;
		pos_j = j;
		j_extended = j;
	}
};

struct Bullet {

	int pos_i;
	int pos_j;

	Bullet() {}
	Bullet(int i, int j) : pos_i{ i }, pos_j{ j } {}

	void move() {

		pos_i--;
	}

	void set(int i, int j) {
		pos_i = i;
		pos_j = j;
	}
};

class Game {

public:

	int score = 0;

	vector<string> state;

	Target target;

	Bullet bullet;

	int V = 4;
	int A = 4;

	Game() {

		this->state = {
			"|-------|",
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
			"|.......|",
		};

		this->target = Target(0, V);

		this->bullet = Bullet(16, A);

		this->state.at(target.pos_i).at(target.pos_j) = 'o';

		show();
	}

	void command_i() {

		this->bullet.set(14, A);
	}
	void command_j() {

		if (A > 0)	A--;
	}
	void command_l() {

		if (A < 14)	A++;
	}


	void update() {

		// update target position
		this->target.move();

		// update bullet position
		if (bullet.pos_i < 16)	this->bullet.move();


		if (collision()) {

			this->score++;
			target.set(-1, V - 1);
			bullet.set(16, A);
		}

		if (target.pos_i == 15) {

			target.set(-1, V - 1);
		}
		if (bullet.pos_i == -1) {

			bullet.set(16, A);
		}

		show();
	}

	bool collision() {

		return (bullet.pos_i == target.pos_i && bullet.pos_j == target.pos_j);
	}

	void show() {

		vector<string> graphic = state;

		if (target.pos_i > -1)	graphic.at(target.pos_i).at(target.pos_j) = 'o';

		if (bullet.pos_i < 15) graphic.at(bullet.pos_i).at(bullet.pos_j) = 'e';

		graphic.at(0).at(V) = 'V';

		graphic.at(14).at(A) = 'A';

		for (auto& e : graphic) {

			cout << e << "\n";
		}
	}
};



int main() {

	system_clock::time_point p;
	Game game = Game();

	while (true)
	{
		char command = 'x';

		 p = system_clock::now() + milliseconds{ 500 };

		while (p > system_clock::now()) {

			cin >> command;
		}

		if ('i' <= command && command <= 'l') {

			if (command == 'i')	game.command_i();

			if (command == 'j')	game.command_j();

			if (command == 'l')	game.command_l();

			game.update();
		}
	}
}