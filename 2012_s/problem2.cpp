
#include<bits/stdc++.h>
using namespace std;

struct Target {

    enum Direction { Left = -1, Right = 1 };

    int i = 0;
    int j = 4;

    Direction direction = Right;

    Target() {}
    Target(int i, int j) : i{ i }, j{ j } {}

    void move() {

        if (j == 0 || j == 8) {

            direction = (direction == Left) ? Right : Left;
        }

        i += 1;
        j += direction;
    }

    void set(int i, int j) {
        this->i = i;    this->j = j;
    }
};

class Game {

public:

    vector<string> stage;

    int posV = 4;
    int posA = 4;

    shared_ptr<Target> target;

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

        target.reset(new Target(0, posV));

        show();
    }

    void update() {

        if (target->i == 14) target.reset(new Target(0, posV));
        else    target->move();
    }

    void show() {

        vector<string> graphic = stage;

        graphic.at(target->i).at(target->j) = 'o';

        graphic.at(0).at(posV) = 'V';
        graphic.at(14).at(posA) = 'A';

        for (auto& e : graphic) {

            cout << e << "\n";
        }
    }
};



int main() {

    Game game = Game();

    while (true) {

        char command;
        cin >> command;

        if ('i' <= command && command <= 'l') {

            game.update();
        }

        game.show();
    }
}