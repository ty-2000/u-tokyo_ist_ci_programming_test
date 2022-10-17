
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
        direction = Right;
    }
};

struct Bullet {

    int i;
    int j;

    bool isAlive = false;

    Bullet() {}
    Bullet(int i, int j):    i { i }, j{ j } {}

    void move() {
        if (isAlive) {

            i--;
            if (i < 0)  isAlive = false;
        }
    }

    void set(int i, int j) {

        this->i = i;
        this->j = j;
        this->isAlive = true;
    }
};

class Game {

public:

    int score = 0;
    int life = 5;

    vector<string> stage;

    int posV = 4;
    int posA = 4;

    shared_ptr<Target> target;

    int remain = 2;
    vector<Bullet> bullets;
    int idNextbullet = 0;

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

        bullets.assign(4, Bullet(14, posA));

        show();
    }

    void command_i() {

        if (!remain) return;

        bullets.at(idNextbullet).set(14, posA);

        idNextbullet = (idNextbullet + 1) % 4;
        remain--;
    }

    void update() {

        if (target->i == 14) {
            life--;
            target.reset(new Target(0, posV));
            remain = 2;
        }
        else    target->move();

        for (int i = 0; i < 4; i++) bullets.at(i).move();

        for (int i = 0; i < 4; i++) {

            if (is_collision(i)) {

                bullets.at(i).isAlive = false;
                target->set(0, posV);
                score++;
                remain = 2;
            }
        }
    }

    bool is_collision(int id) {

        return (bullets.at(id).isAlive) && bullets.at(id).i == target->i && bullets.at(id).j == target->j;
    }

    void show() {

        vector<string> graphic = stage;

        graphic.at(target->i).at(target->j) = 'o';

        for (int id = 0; id < 4; id++) {
            if (bullets.at(id).isAlive)   graphic.at(bullets.at(id).i).at(bullets.at(id).j) = 'e';
        }

        graphic.at(0).at(posV) = 'V';
        graphic.at(14).at(posA) = 'A';

        for (auto& e : graphic) {

            cout << e << "\n";
        }

    }
};



int main() {

    Game game = Game();

    while (game.life > 0) {

        char command;
        cin >> command;

        if ('i' <= command && command <= 'l') {

            if (command == 'i')  game.command_i();

            game.update();
        }

        game.show();
    }

    cout << game.score << endl;
}