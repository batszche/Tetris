#pragma once

enum blockState {
	EMPTY = 0,
	WALL = 1,
	FIXEDBLOCK = 2,
	HEART = 3
}; 

enum TetrominoType {
	MINO_I = 0,
	MINO_O,
	MINO_T,
	MINO_S,
	MINO_Z,
	MINO_J,
	MINO_L,
	MINO_MAX
};

enum curRotation {
    ROT_0 = 0,
    ROT_90,
    ROT_180,
    ROT_270
};
class Tetris {
private:
	const int blockShapes[MINO_MAX][4][4] = {
        {
            // MINO_I
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            // MINO_O
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            // MINO_T
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            // MINO_S
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            // MINO_Z
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            // MINO_J
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            // MINO_L
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }
    };
	
	// 총 점수
	int score;
	// 보드의 크기
	int BOARD[22][12];
	// 현재 블록의 좌표
	struct position { int x, y; };
	position curPos;
	// 충돌 감지
	bool checkCollision(int nextX, int nextY);
	int curBlockType;
	int nextBlockType;
    int curRotation = 0;
    int nowBlock[4][4];
    int tempBlock[4][4];
public:
	int timer = 0;
	int lockTimer = 0;
	// 생성자
	Tetris();
	// 소멸자
	~Tetris();
	// 테트리스 보드 그리기
	void draw();
	bool ifLineFull(int lineY);
	// 열 지우기
	void lineClear(int lineY); 
	void checkLineFull();
	// 블록 이동
	void blockMove(int dx, int dy);
	// 블록 고정
	void blockFix();
	// 외부에서 점수 값을 수정
	bool touchBottom();
	void rotateBlock();
	bool checkCollisionAfterRotate();
    void gameOver();
};