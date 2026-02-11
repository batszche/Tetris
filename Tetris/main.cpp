#include "Tetris.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main() {
	Tetris game;
	while (true) {
		game.draw();

		if (_kbhit()) {
			int key = _getch();

			if (key == 'a') game.blockMove(-1,0);
			if (key == 'd') game.blockMove(1, 0);
			if (key == 's') game.blockMove(0, 1);
		}
	}
	return 0;
}

