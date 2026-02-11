#include <iostream>
#include "Tetris.h"
using namespace std;

Tetris::Tetris() {
	// 벽 배열 초기화// position curPos = { 0, 0 }; // 주의: 여기서 새로 선언하면 멤버 변수가 아니라 '지역 변수'가 됩니다.
    // curPos = { 5, 0 }; // 헤더에 선언된 멤버 변수를 그대로 쓰세요.
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			if (x == 0 || x == 11 || y == 21)
			{
				BOARD[y][x] = 1;
			}
			else BOARD[y][x] = 0;
		}
	}

	// 변수 세팅: 점수 및 블록 위치

	curPos = { 5, 0 };
	score = 0;
}


// 초기화
void Tetris::draw() {
	system("cls");
	for (int y = 0; y < 22; y++) {
		for (int x = 0; x < 12; x++) {
			if (x == curPos.x && y == curPos.y) {
				cout << "■";
			}
			else if (BOARD[y][x] == 1) {
				cout << "◆";
			}
			else if (BOARD[y][x] == 0) {
				cout << "□";
			}
		}
		cout << endl;
	}
}

void Tetris::blockMove(int dx, int dy) {
	curPos.x += dx;
	curPos.y += dy;
}

bool Tetris::checkCollision(int nextX, int nextY) {
	if (nextX == 1 || nextY == 1)
		return false;
	else true;
}

Tetris::~Tetris() {

}