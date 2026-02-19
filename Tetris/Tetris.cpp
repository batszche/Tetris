#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include "Tetris.h"
using namespace std;

Tetris::Tetris() {
	system("cls");
	while (true) {
		cout << "보드의 가로 크기를 입력하세요. (12~30)";
		cin >> boardWidth;
		if (cin.fail() || boardWidth < 12 || boardWidth > 30) {
			cout << "12에서 30 사이의 숫자를 입력해 주세요." << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else break;
	}
	while (true) {
		cout << "보드의 세로 크기를 입력하세요. (15~45)";
		cin >> boardHeight;

		if (cin.fail() || boardHeight < 15 || boardHeight > 45) {
			cout << "15에서 30 사이의 숫자를 입력해 주세요." << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else break;
	}
	BOARD = new int* [boardHeight];
	for (int i = 0; i < boardHeight; i++) {
		BOARD[i] = new int[boardWidth];
	}
	resetGame();
}


void Tetris::setColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
void Tetris::setCursor(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hConsole, pos);
}
void Tetris::draw() {
	setCursor(0, 0);
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			bool isDrawn = false;
			if (y >= curPos.y && y <= curPos.y + 3 && x >= curPos.x && x <= curPos.x + 3) {
				if (nowBlock[y - curPos.y][x - curPos.x] == 1) {
					setColor(14);
					cout << "■";
					isDrawn = true;
				}
			}
			if (!isDrawn) {
				if (BOARD[y][x] == WALL) {
					setColor(4);
					cout << "◆";
				}
				else if (BOARD[y][x] == FIXEDBLOCK) {
					setColor(2);
					cout << "▼";
				}
				else {
					setColor(7);
					cout << "□";
				}
			}
		}
		cout << "                                    " << endl ;
	}
	setColor(7);
	cout << endl << "현재 점수 : " << score;
	cout << endl << "다음 블록 " << endl;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blockShapes[nextBlockType][y][x] == 1) {
				setColor(14);
				cout << "■";
			}
			else {
				setColor(7);
				cout << "□";
			}
		}		
		cout << endl;
	}
}

void Tetris::blockMove(int dx, int dy) {
	if (!checkCollision(curPos.x + dx, curPos.y + dy)) {
		curPos.x += dx;
		curPos.y += dy;
	}
}
		


bool Tetris::checkCollision(int nextX, int nextY) {
	for (int blockY = 0; blockY < 4; blockY++) {
		for (int blockX = 0; blockX < 4; blockX++) {
			if (nowBlock[blockY][blockX] == 1) {
				if (BOARD[nextY + blockY][nextX + blockX] == WALL || BOARD[nextY + blockY][nextX + blockX] == FIXEDBLOCK)
					return true;
			}
		}
	}
	return false;
}

bool Tetris::touchBottom() {
	for (int blockY = 0; blockY < 4; blockY++) {
		for (int blockX = 0; blockX < 4; blockX++) {
			if (nowBlock[blockY][blockX] == 1) {
				if (BOARD[curPos.y + blockY + 1][curPos.x + blockX] == WALL || BOARD[curPos.y + blockY + 1][curPos.x + blockX] == FIXEDBLOCK)	return true;
			}
		}
	}
	return false;
}

void Tetris::blockFix() {
	for (int blockY = 0; blockY < 4; blockY++) {
		for (int blockX = 0; blockX < 4; blockX++) {
			if (nowBlock[blockY][blockX] == 1)
				BOARD[curPos.y + blockY][curPos.x + blockX] = FIXEDBLOCK;
		}
	}
	curPos.x = boardWidth /2 -2;
	curPos.y = 0;
	curBlockType = nextBlockType;
	nextBlockType = rand() % MINO_MAX;
	for (int blockY = 0; blockY < 4; blockY++) {
		for (int blockX = 0; blockX < 4; blockX++) {
			nowBlock[blockY][blockX] = blockShapes[curBlockType][blockY][blockX];
		}
	}
	if (checkCollision(curPos.x, curPos.y) == true) {
		ifGameOver = true;
		gameOver();
	}
}


void Tetris::lineClear(int lineY) {
	for (int y = lineY; y > 1; y--) {
		for (int x = 1; x < boardWidth; x++) {
			BOARD[y][x] = BOARD[y - 1][x];
		}
	}
	for (int x = 1; x < boardWidth; x++) {
		BOARD[0][x] = EMPTY;
	}
	score++;
}

bool Tetris::ifLineFull(int lineY) {
	for (int x = 1; x < boardWidth; x++) {
		if (BOARD[lineY][x] == EMPTY) return false;
	}
	return true;
}

void Tetris::checkLineFull() {
	for (int y = 0; y < boardHeight-1; y++) {
		if (ifLineFull(y) == true) {
			lineClear(y);
			y--;
		}
	}
}


bool Tetris::checkRotationCollision(int nextX, int nextY, bool isClockwise) {
	int temp[4][4];
	if (isClockwise == true) {
		for (int blockY = 0; blockY < 4; blockY++) {
			for (int blockX = 0; blockX < 4; blockX++) {
				temp[blockY][blockX] = nowBlock[3 - blockX][blockY];
			}
		}
	}
	else {
		for (int blockY = 0; blockY < 4; blockY++) {
			for (int blockX = 0; blockX < 4; blockX++) {
				temp[blockY][blockX] = nowBlock[blockX][3 - blockY];
			}
		}

	}
	for (int blockY = 0; blockY < 4; blockY++) {
		for (int blockX = 0; blockX < 4; blockX++) {
			if (temp[blockY][blockX] == 1) {
				if (BOARD[nextY + blockY][nextX + blockX] == WALL || BOARD[nextY + blockY][nextX + blockX] == FIXEDBLOCK)
					return true;
			}
		}
	}
	return false;
}

void Tetris::rotateBlock(bool isClockwise) {
	if (!checkRotationCollision(curPos.x, curPos.y, isClockwise)) {
		int temp[4][4];
		for (int blockY = 0; blockY < 4; blockY++) {
			for (int blockX = 0; blockX < 4; blockX++) {
				temp[blockY][blockX] = nowBlock[blockY][blockX];
			}
		}
		if (isClockwise == false) {
			for (int blockY = 0; blockY < 4; blockY++) {
				for (int blockX = 0; blockX < 4; blockX++) {
					nowBlock[blockX][3 - blockY] = temp[blockY][blockX];
				}
			}
		}
		else {
			for (int blockY = 0; blockY < 4; blockY++) {
				for (int blockX = 0; blockX < 4; blockX++) {
					nowBlock[blockY][blockX] = temp[blockX][3 - blockY];
				}
			}
		}
		curRotation++;
		if (curRotation == 4) curRotation = 0;
	}
}
void Tetris::gameOver() {
	system("cls");
	int centerX = (boardWidth / 2); 
	int centerY = (boardHeight / 2);
	for (int y = 0; y < boardHeight; y++) {
		setColor(4);
		cout << "◆";
		if (y == centerY - 3 || y == centerY + 4) {
			for (int i = 0; i < (boardWidth - 5) / 2; i++) {
				setColor(7);
				cout << "□";
			}
			for (int i = 0; i < 4; i++) {
				setColor(14);
				cout << "=";
			}
			if (boardWidth %2 == 1){
				for (int i = 0; i < (boardWidth - 5) / 2-1; i++) {
					setColor(7);
					cout << "□";
				}
			}
			else {
				for (int i = 0; i < (boardWidth - 5) / 2 ; i++) {
					setColor(7);
					cout << "□";
				}
			}
		}
		else if (y == centerY - 1) {
			for (int i = 0; i < (boardWidth - 9) / 2; i++) {
				setColor(7);
				cout << "□";
			}
			setColor(14);
			cout << "GAME OVER";
			if (boardWidth % 2 == 1) {
				for (int i = 0; i < (boardWidth - 9) / 2; i++) {
					setColor(7);
					cout << "□";
				}
			}
			else {
				for (int i = 0; i < (boardWidth - 9) / 2 - 1; i++) {
					setColor(7);
					cout << "□";
				}
			}
		}
		else if (y == centerY + 1) {
			setColor(2);
			for (int i = 0; i < (boardWidth - 7) / 2; i++) {
				setColor(7);
				cout << "□";
			}
			setColor(14);
			cout << "REPLAY?";
			if (boardWidth % 2 == 1) {
				for (int i = 0; i < (boardWidth - 7) / 2; i++) {
					setColor(7);
					cout << "□";
				}
			}
			else {
				for (int i = 0; i < (boardWidth - 7) / 2 - 1; i++) {
					setColor(7);
					cout << "□";
				}
			}
		}
		else if (y == centerY + 2) {
			setColor(2);
			for (int i = 0; i < (boardWidth - 7) / 2; i++) {
				setColor(7);
				cout << "□";
			}
			setColor(14);
			cout << "(Y / N)";

			if (boardWidth % 2 == 1) {
				for (int i = 0; i < (boardWidth - 7) / 2; i++) {
					setColor(7);
					cout << "□";
				}
			}
			else {
				for (int i = 0; i < (boardWidth - 7) / 2 - 1; i++) {
					setColor(7);
					cout << "□";
				}
			}
		}
		else if (y == boardHeight-1) {
			for (int i = 0; i < boardWidth-2; i++) {
				cout << "◆";
			}
		}
		else {
			for (int i = 0; i < boardWidth - 2; i++) {
				setColor(7);
				cout << "□";
			}
		}
		setColor(4);
		cout << "◆";
		cout << "                           " << endl;
	}
}

void Tetris::resetGame() {
	ifGameOver = false;
	for (int y = 0; y < boardHeight; y++) {
		for (int x = 0; x < boardWidth; x++) {
			if (x == 0 || x == boardWidth-1 || y == boardHeight-1)
			{
				BOARD[y][x] = 1;
			}
			else BOARD[y][x] = 0;
		}
	}

	curPos = { boardWidth /2 -2, 0 };
	score = 0;
	curBlockType = rand() % MINO_MAX;
	nextBlockType = rand() % MINO_MAX;
	for (int blockY = 0; blockY < 4; blockY++) {
		for (int blockX = 0; blockX < 4; blockX++) {
			nowBlock[blockY][blockX] = blockShapes[curBlockType][blockY][blockX];
		}
	}
}
Tetris::~Tetris() {
	for (int i = 0; i <boardHeight;i++){
		delete[] BOARD[i];
	}

	delete[] BOARD;

	BOARD = nullptr;
} 