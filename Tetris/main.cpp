#include "Tetris.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int main() {
	srand((unsigned int)time(NULL));
	Tetris game;
	while (true) {
		if (game.ifGameOver == true) {
			system("cls");
			game.setCursor(0, 10);
			cout << "====================" << endl;
			cout << "      GAME OVER     " << endl;
			cout << "    REPLAY? (Y/N)   " << endl;
			cout << "====================" << endl;
			int key = _getch();
			if (key == 'y') game.resetGame();
			if (key == 'n')	exit(0);
			continue;
		}
		if (game.timer == 50) {
			game.blockMove(0, 1);
			game.timer = 0;
		}
		if (game.lockTimer == 50) {
			game.blockFix();
			game.lockTimer = 0;
		}
		if (_kbhit()) {
			int key = _getch();

			if (key == 'a') game.blockMove(-1, 0);
			if (key == 'd') game.blockMove(1, 0);
			if (key == 's') {
				if (game.touchBottom() == true)	game.blockFix();
				else {
					game.blockMove(0, 1);
				}
			}
			if (key == 'f') game.rotateBlock(false);
			if (key == 'r') game.rotateBlock(true);
		}
		game.checkLineFull();
		game.timer++;
		if (game.touchBottom() == true) game.lockTimer++;
		game.draw();
		Sleep(10);
	}
	return 0;
}
