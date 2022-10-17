#include<bits/stdc++.h>
using namespace std;
using namespace chrono;

class Game {

private:
    vector<vector<int> > state; // 3x3ƒ}ƒX

    int turn = 0;   // Žè”Ô, 0 or 1
    vector<char> pieces;    // ‹î

public:
    Game() {

        state.assign(3, vector<int>(3, 2));
        pieces.resize(3);
        pieces = { 'O', 'X', '-' };
    }

    void run() {

        print();

        while (true)
        {

            string place;
            place = select_rondomPlace();

            setPiece(place);

            print();

            int judge_res = judge();

            if (judge_res == 0) {

                cout << "First player wins" << endl;
                break;
            }
            else if (judge_res == 1) {

                cout << "Secont player wins" << endl;
                break;
            }
            else if (judge_res == 2) {

                cout << "Draw" << endl;
                break;
            }
            else {
                continue;
            }
        }
    }

    // 0:player0 wins.  1:player1 wins  2:draw  3: not yet
    int judge();

    string select_rondomPlace();

    void setPiece(string place);

    void print();
};

int main() {

    Game game = Game();
    game.run();
}

// 0:player0 wins.  1:player1 wins  2:draw  3: not yet
int Game::judge() {

    // whether one player wins or not
    for (int i = 0; i < 3; i++) {

        if (state.at(i).at(0) != 2 && state.at(i).at(0) == state.at(i).at(1) && state.at(i).at(1) == state.at(i).at(2)) {
            return state.at(i).at(0);
        }
        if (state.at(0).at(i) != 2 && state.at(0).at(i) == state.at(1).at(i) && state.at(1).at(i) == state.at(2).at(i)) {
            return state.at(0).at(i);
        }
    }

    if (state.at(0).at(0) != 2 && state.at(0).at(0) == state.at(1).at(1) && state.at(1).at(1) == state.at(2).at(2))    return state.at(0).at(0);
    if (state.at(0).at(2) != 2 && state.at(0).at(2) == state.at(1).at(1) && state.at(1).at(1) == state.at(2).at(0))    return state.at(0).at(2);

    for (int i = 0; i < 9; i++) {

        // There is space to set piece
        if (state.at(i / 3).at(i % 3) == 2)  return 3;
    }

    // no space to set piece
    return 2;
}

string Game::select_rondomPlace() {

    // wait for 1 second;
    system_clock::time_point tp = system_clock::now() + seconds(1);
    while (tp > system_clock::now()) {}

    vector<int> candidate;

    for (int i = 0; i < 9; i++) {

        if (state.at(i / 3).at(i % 3) == 2)  candidate.push_back(i);
    }

    random_device seed_gen;
    mt19937 engine{ seed_gen() };
    uniform_int_distribution<> dist{ 0, (int)candidate.size() - 1 };

    int res = candidate.at(dist(engine));

    char i = res / 3;
    char j = res % 3;

    i += '1';
    j += 'A';

    string ret = "";
    ret += i;
    ret += j;

    return ret;
}


void Game::setPiece(string place) {

    int i = place.at(0) - '1';
    int j = place.at(1) - 'A';

    if (state.at(i).at(j) != 2) {

        cout << "this space is filled" << endl;
        return;
    }

    state.at(i).at(j) = turn;

    turn = (turn + 1) % 2;
}

void Game::print() {

    for (auto& line : state) {
        for (auto& e : line) {

            cout << pieces.at(e) << " ";
        }
        cout << "\n";
    }
    cout << endl;
}