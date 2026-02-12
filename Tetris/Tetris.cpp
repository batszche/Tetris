#include <iostream>
#include "Tetris.h"
#include <windows.h>
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

	// 변수 세팅: 점수 및 블록 위치, 블록 종류
	// curBlockType = MINO_J;
	// 현재 블록 상태 변수curBlockType을 랜덤으로 뽑기/blockfix 이후 랜덤으로 새로 뽑기 / 미리 뽑기
	curPos = { 4, 0 };
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
			else if (BOARD[y][x] == WALL) {
				cout << "◆";
			}
			else if (BOARD[y][x] == EMPTY) {
				cout << "□";
			}
			else if (BOARD[y][x] == FIXEDBLOCK) {
				cout << "▼";
			}
		}
		cout << endl;
	}
	cout << endl << "플레이 시간 : " << timer;
	cout << endl << "현재 점수 : " << score;
	cout << endl << "다음 블록 : " << score;
}

void Tetris::blockMove(int dx, int dy) {
	if (checkCollision(curPos.x + dx, curPos.y + dy) == true)	return;
		else {
			curPos.x += dx;
			curPos.y += dy;
		}
	}


bool Tetris::checkCollision(int nextX, int nextY) {
	if (BOARD[nextY][nextX] == WALL || BOARD[nextY][nextX] == FIXEDBLOCK)
		return true;
	else return false;
}

bool Tetris::touchBottom() {
	if (BOARD[curPos.y+1][curPos.x] == WALL || BOARD[curPos.y + 1][curPos.x] == FIXEDBLOCK)	return true;
	else return false;
}

void Tetris::blockFix() {
		BOARD[curPos.y][curPos.x] = 2;
		curPos.x = 5;
		curPos.y = 0;
}



// 한 줄 지우기 함수
// 1. 모두 FIXEDBLOCK으로 채워진 y번째 행을 y-1번째행의 배열로 바꾼다.
// 2. y번째 행에서 2번째 행까지 윗줄로 진행하며 위 작업을 반복한다.
// 3. 1번째 행은 EMPTY로 채운다.
// 4. 점수를 추가한다.
void Tetris::lineClear(int lineY) {
	for (int y = lineY; y > 1; y--) {
		for (int x = 1; x < 11; x++) {
			BOARD[y][x] = BOARD[y - 1][x];
		}
	}
	for (int x = 1; x < 11; x++) {
		BOARD[0][x] = 0;
	}
	score++;
}

// 한 줄의 모든 요소가 FIXEDBLOCK으로 구성되어 있는가?
bool Tetris::ifLineFull(int lineY) {
	for (int x = 1; x < 11; x++) {
		if (BOARD[lineY][x] == 0) return false;
	}
	return true;
}

// 가득 찬 줄 검사
// 1. 모든 y열에 대해, y열의 모든 x번째 요소에 대해 검사 (이중 for문)
// 2. 한 줄이 모두 FIXEDBLOCK인지 검사하기
// 3. 줄 안에 빈 칸이 있으면 false, 모두 FIXEDBLOCK이면 true
// 모든 줄에 대해 실시간 검사- 한 프레임마다 한 번씩
void Tetris::checkLineFull() {
	for (int y = 0; y < 21; y++) {
		if (ifLineFull(y) == true) lineClear(y);
	}
}


Tetris::~Tetris() {

} 