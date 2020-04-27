#include <iostream>

using namespace std;

const char human = 'X';
const char ai = 'O';

enum Player { HUMAN, AI };

struct Move {
	int x;
	int y;
};

class Game {
	char board[3][3];

public:
	Game();
	void printBoard();
	bool gameO();
	bool checkWin(Player player);
	void play();
	void getHumanMove();
	int score();
	Move minimax(char AIboard[3][3]);
	int minSearch(char AIboard[3][3]);
	int MaxS(char AIboard[3][3]);
	};