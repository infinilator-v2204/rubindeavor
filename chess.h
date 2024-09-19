#pragma once

typedef struct {
	char board[64];
	char turn;
	char legalMoves[128][2];
	int legalMoveCount;
	bool kingCheck;
	bool pieceCaptured;
	char lastMove[2];
	bool enableKingCaptures;
} ChessState;

typedef struct {
	ChessState state;
	int boardX;
	int boardY;
	char xDrag;
	int puzzleState;
	int puzzleProgress;
	int puzzleCooldown;
	char pieceAnimationX1;
	char pieceAnimationX2;
	int pieceAnimationTimer;
} ChessSystem;

enum {
	CHESS_PIECE_KING = 1,
	CHESS_PIECE_QUEEN = 2,
	CHESS_PIECE_ROOK = 3,
	CHESS_PIECE_KNIGHT = 4,
	CHESS_PIECE_BISHOP = 5,
	CHESS_PIECE_PAWN = 6,
	
	CHESS_PIECE_WHITE = 0,
	CHESS_PIECE_BLACK = 8,
};

enum {
	CHESS_UPLEFT	= -9,
	CHESS_UP		= -8,
	CHESS_UPRIGHT	= -7,
	CHESS_LEFT		= -1,
	CHESS_RIGHT		= 1,
	CHESS_DOWNLEFT	= 7,
	CHESS_DOWN		= 8,
	CHESS_DOWNRIGHT	= 9,
};

extern ChessSystem chessSystem;



void Chess_Init();
void Chess_Update();
void Chess_Draw();

char Chess_GetFile(char x);
char Chess_GetRank(char x);
char Chess_GetPieceType(ChessState* state, char x);
char Chess_GetPieceColor(ChessState* state, char x);
void Chess_MovePiece(ChessState* state, char x1, char x2);
bool Chess_MoveIsLegal(ChessState* state, char x1, char x2);
void Chess_TryMovePiece(ChessState* state, char x1, char x2);
void Chess_AddLegalMove(ChessState* state, char x1, char x2);
char Chess_CheckLegalMove(ChessState* state, char x1, char x2);
void Chess_FindLegalMoves(ChessState* state);
