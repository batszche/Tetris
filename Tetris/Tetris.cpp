#include <iostream>
#include "Tetris.h"
using namespace std;

Tetris::Tetris() {
	// 벽 배열 초기화// position curPos = { 0, 0 }; // 주의: 여기서 새로 선언하면 멤버 변수가 아니라 '지역 변수'가 됩니다.
    // curPos = { 5, 0 }; // 헤더에 선언된 멤버 변수를 그대로 쓰세요.
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 22; j++) {
			if (i == 0 || i == 11 || j == 21)
			{
				BOARD[i][j] = 1;
			}
			else BOARD[i][j] = 0;
		}
	}

	// 변수 세팅: 점수 및 블록 위치

	curPos = { 0, 0 };
	score = 0;
}

void Tetris::draw() {
	system("cls");

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 22; j++) {
			if (i == 0 || i == 11 || j == 21)
			{
				BOARD[i][j] = 1;
			}
			else BOARD[i][j] = 0;
		}
	}
}