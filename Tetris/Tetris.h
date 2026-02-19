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
	
	int score;
	int** BOARD;
	int boardWidth;
    int boardHeight;
	struct position { int x, y; };
	position curPos;
	bool checkCollision(int nextX, int nextY);
	int curBlockType;
	int nextBlockType;
    int curRotation = 0;
    int nowBlock[4][4];
    int tempBlock[4][4];
public:
    Tetris();
    ~Tetris();
    void setColor(int color);
    bool ifGameOver;
	int timer = 0;
	int lockTimer = 0;
	void draw();
	bool ifLineFull(int lineY);
	void lineClear(int lineY); 
	void checkLineFull();
	void blockMove(int dx, int dy);
	void blockFix();
	bool touchBottom();
	void rotateBlock(bool isClockwise);
	bool checkRotationCollision(int nextX, int nextY, bool isClockwise);
    void gameOver();
    void resetGame();
    void setCursor(int x, int y);

};