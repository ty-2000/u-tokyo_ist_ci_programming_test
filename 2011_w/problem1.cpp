#include<bits/stdc++.h>
using namespace std;

class Game {

private:
    vector<vector<int> > state; // 3x3マス

    int turn = 0;   // 手番, 0 or 1
    vector<char> pieces;    // 駒

    int cnt_setPiece = 0;

public:
    Game() {

        state.assign(3, vector<int>(3, 2));
        pieces.resize(3);
        pieces = { 'O', 'X', '-' };
    }
    ~Game() {

        cout << "終了しました。" << endl;
    }

    void run() {

        setPiece("1A");
        setPiece("1B");
        setPiece("2A");
        setPiece("2B");
        setPiece("3A");
        setPiece("2C");
        setPiece("3B");

        print();
    }

    void setPiece(string place) {

        int i = place.at(0) - '1';
        int j = place.at(1) - 'A';

        if (state.at(i).at(j) != 2) {

            cout << "マスは埋まっています" << endl;
            return;
        }

        state.at(i).at(j) = turn;

        turn = (turn + 1) % 2;
        cnt_setPiece++;
    }

    void print() {

        for (auto& line : state) {
            for (auto& e : line) {

                cout << pieces.at(e) << " ";
            }
            cout << "\n";
        }
        cout << endl;
    }
};

int main() {

    Game game = Game();
    game.run();
}