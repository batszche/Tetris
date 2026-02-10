#pragma once

class Tetris {
private:
	// 총 점수
	int score;
	// 보드의 크기
	int BOARD[22][12];
	// 현재 블록의 좌표
	struct position { int x, y; };
	position curPos;
public:
	// 생성자
	Tetris();
	// 소멸자
	~Tetris();
	// 테트리스 보드 그리기
	void draw();
	// 열 지우기
	void lineClear();
	// 블록 이동
	void blockMove(int dx, int dy);
	// 블록 고정
	void blockFix();
	// 외부에서 점수 값을 수정
	void setScore(int score);
	// 외부에서 점수 값에 접근
	int getScore();
};