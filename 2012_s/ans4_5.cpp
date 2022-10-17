#include<bits/stdc++.h>
using namespace std;

class Game {

public:

    struct Bullet
    {
        int i;
        int j;

        Bullet() {}

        Bullet(int launch_position) {

            i = 14;
            j = launch_position;
        }

        void move() {
            --i;
        }
    };

    struct Target
    {

    public:
        int launch_pos;

        int i;
        int j;

        int direction;  // 1:right, -1:left

        Target() {

            launch_pos = 4;
            init();
        }



        void init() {

            launch_pos = rand() % 9;

            i = 0;
            j = launch_pos;
            direction = 1;
        }

        void move(Game& game) {

            if (j == 8)  direction = -1;
            else if (j == 0) direction = 1;

            ++i;
            j += direction;

            if (i == 15) {
                init();
                game.gun.reset();
                return;
            }
        }
    };

    struct Gun {

        int launch_pos;

        int remain;

        Gun() {
            launch_pos = 4;
            remain = 2;
        }

        void shoot(Game& game) {

            if (!remain) return;

            game.bullets.bullet_list.push_back(Bullet(launch_pos));

            --remain;
        }

        void reset() {
            remain = 2;
        }

        void move_right() {

            if (launch_pos < 9)  ++launch_pos;

            return;
        }
        void move_left() {

            if (launch_pos > 0)  --launch_pos;

            return;
        }
    };

    struct Bullets {

        list<Bullet> bullet_list;

        Bullets() {}

        void move() {

            for (auto& e : bullet_list) {

                e.move();
            }

            for (auto itr = bullet_list.begin(); itr != bullet_list.end(); itr++) {

                if (itr->i < 0) {

                    bullet_list.erase(itr);

                    return;
                }
            }
            return;
        }
    };

    vector<vector<char> > board;

    Target target;

    Gun gun;

    Bullets bullets;

    int score = 0;
    int life = 5;

    Game() {

        board = {
            {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
            {'|', '.', '.', '.', '.', '.', '.', '.', '|'},
        };

        target = Target();

        gun = Gun();

        bullets = Bullets();
    }

    list<Bullet>::iterator findHitBullet() {

        auto itr = bullets.bullet_list.begin();
        while (itr != bullets.bullet_list.end()) {

            if (itr->i == target.i && itr->j == target.j)    break;

            itr++;
        }

        return itr;
    }


    void show() {

        vector<vector<char> > state = board;

        state.at(target.i).at(target.j) = 'O';

        state.at(0).at(target.launch_pos) = 'V';

        state.at(14).at(gun.launch_pos) = 'A';

        for (auto& bullet : bullets.bullet_list) {

            state.at(bullet.i).at(bullet.j) = 'e';
        }

        for (auto& line : state) {

            for (auto& e : line) {

                cout << e << ' ';
            }
            cout << endl;
        }
    }
};

int main()
{
    Game game = Game();
    game.show();

    char command;

    while (cin >> command) {

        if (command < 'i' || 'l' < command)  continue;

        else if (command == 'i') {

            game.gun.shoot(game);
        }
        else if (command == 'j') {

            game.gun.move_left();
        }
        else if (command == 'l') {

            game.gun.move_right();
        }

        game.bullets.move();

        game.target.move(game);
        if (game.target.i == 0) {   // target arrive edge C

            --game.life;
            game.gun.reset();
        }

        if (game.life <= 0)  break;

        auto itr = game.findHitBullet();
        if (itr != game.bullets.bullet_list.end()) {    // hit

            game.target.init();
            game.gun.reset();

            game.bullets.bullet_list.erase(itr);

            game.score += 1;
        }

        game.show();

    }

    cout << game.score << endl;
}