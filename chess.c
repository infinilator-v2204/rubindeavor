#include "generic.h"
#include "chess.h"
#include "sprites.h"
#include "audio.h"
#include "overworld.h"
#include "event.h"

ChessSystem chessSystem;

const ChessState puzzleChessState = {
	{
		 0, 0, 0, 0, 0, 0, 0, 0,
		14, 0, 0, 0, 0, 0, 0,14,
		 0, 0, 0, 0, 0, 0, 0,14,
		14, 0, 0, 0, 0, 0, 0,14,
		13, 0, 0, 2, 0, 0, 0,14,
		 1, 0, 0, 0, 0, 0, 0,14,
		14, 0,11, 0, 0, 0, 0, 0,
		11, 9, 0, 0, 0,12, 0,12,
	},
	CHESS_PIECE_WHITE, {}, 0, false, false, {0, 0}, false
};
const char puzzleMoves[][2] = {
	{35,59}, {50,58},
	{59,43}, {58,50},
	{43,61}, {50,58},
	{61,43}, {58,50},
	{43,59}, {50,58},
	{59,51}, {58,50},
	{51,60}, {50,58},
	{60,36}, {58,50},
	{36,63}, {50,58},
	{63,36}, {58,50},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {8,16},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {47,55},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {39,47},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {31,39},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {23,31},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {55,63},//promotion
	{36,63}, {50,58},
	{63,36}, {58,50},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {47,55},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {39,47},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {15,23},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {55,63},//promotion
	{36,63}, {50,58},
	{63,36}, {58,50},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {31,39},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {47,55},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {23,31},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {39,47},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {55,63},//promotion
	{36,63}, {50,58},
	{63,36}, {58,50},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {31,39},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {47,55},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {39,47},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {55,63},//promotion
	{36,63}, {50,58},
	{63,36}, {58,50},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {47,55},
	{36,60}, {50,58},
	{60,51}, {58,50},
	{51,59}, {50,58},
	{59,43}, {58,50},
	{43,36}, {55,63},//promotion
	{36,63}, {50,58},
	//finale
	{63,15}, {58,50},
	{15,36}, {32,41},
	{36,60}, {50,58},
	{60,51}, {41,50},
	{51,42}, {24,32},
	{42,49},
};
const int puzzleMoveCount = 259;



void Chess_Init() {
	Audio_StopMusic();
	/*for (int i = 0; i < 64; i++) chessSystem.state.board[i] = 0;
	for (int i = 0; i < 2; i++) {
		char color = i == 0 ? CHESS_PIECE_BLACK : CHESS_PIECE_WHITE;
		chessSystem.state.board[i * 56 + 0] = CHESS_PIECE_ROOK | color;
		chessSystem.state.board[i * 56 + 1] = CHESS_PIECE_KNIGHT | color;
		chessSystem.state.board[i * 56 + 2] = CHESS_PIECE_BISHOP | color;
		chessSystem.state.board[i * 56 + 3] = CHESS_PIECE_QUEEN | color;
		chessSystem.state.board[i * 56 + 4] = CHESS_PIECE_KING | color;
		chessSystem.state.board[i * 56 + 5] = CHESS_PIECE_BISHOP | color;
		chessSystem.state.board[i * 56 + 6] = CHESS_PIECE_KNIGHT | color;
		chessSystem.state.board[i * 56 + 7] = CHESS_PIECE_ROOK | color;
		for (int j = 8 + i * 40; j < 16 + i * 40; j++) {
			chessSystem.state.board[j] = CHESS_PIECE_PAWN | color;
		}
	}
	chessSystem.state.turn = CHESS_PIECE_WHITE;*/
	chessSystem.boardX = 32;
	chessSystem.boardY = 32;
	
	chessSystem.state = puzzleChessState;
	Chess_FindLegalMoves(&chessSystem.state);
	chessSystem.puzzleState = 0;
	chessSystem.puzzleProgress = 0;
	chessSystem.puzzleCooldown = 0;
	chessSystem.xDrag = -1;
	chessSystem.pieceAnimationTimer = -1;
	
	CreatePopup("You have been locked out from playing\nthe game due to being stupid. If you\nwant to resume control of the game, you\nneed to solve this chess puzzle.");
	Audio_PlaySound(SND_no);
}

void Chess_Update() {
	if (chessSystem.puzzleState == 2) {
		chessSystem.puzzleCooldown--;
		if (chessSystem.puzzleCooldown == 1) {
			CreatePopup("Congratulations! Now you can continue\nplaying the game.");
		}
		else if (chessSystem.puzzleCooldown <= 0) {
			ChangeScene(SCENE_OVERWORLD);
			Audio_PlayMusic(overworld.lastMusicId);
			eventSystem.paused = false;
		}
	}
	else if (chessSystem.puzzleState == 0) {
		if (chessSystem.puzzleCooldown > 0) {
			chessSystem.puzzleCooldown--;
			if (chessSystem.puzzleCooldown == 0) {
				Chess_TryMovePiece(&chessSystem.state, puzzleMoves[chessSystem.puzzleProgress][0], puzzleMoves[chessSystem.puzzleProgress][1]);
				Audio_PlaySound(SND_chess_move);
				chessSystem.pieceAnimationX1 = puzzleMoves[chessSystem.puzzleProgress][0];
				chessSystem.pieceAnimationX2 = puzzleMoves[chessSystem.puzzleProgress][1];
				chessSystem.pieceAnimationTimer = 0;
				chessSystem.puzzleProgress++;
			}
		}
		else {
			if (MousePressed(MOUSE_LEFT)) {
				if (game.mouseX >= chessSystem.boardX && game.mouseX < chessSystem.boardX + 256 && game.mouseY >= chessSystem.boardY && game.mouseY < chessSystem.boardY + 256) {
					int file = (game.mouseX - chessSystem.boardX) / 32;
					int rank = (game.mouseY - chessSystem.boardY) / 32;
					if (chessSystem.state.board[file + rank * 8] > 0) {
						chessSystem.xDrag = file + rank * 8;
					}
				}
			}
			else if (MouseReleased(MOUSE_LEFT) && chessSystem.xDrag >= 0) {
				if (game.mouseX >= chessSystem.boardX && game.mouseX < chessSystem.boardX + 256 && game.mouseY >= chessSystem.boardY && game.mouseY < chessSystem.boardY + 256) {
					int file = (game.mouseX - chessSystem.boardX) / 32;
					int rank = (game.mouseY - chessSystem.boardY) / 32;
					int x1 = chessSystem.xDrag;
					int x2 = file + rank * 8;
					Chess_TryMovePiece(&chessSystem.state, x1, x2);
					if (chessSystem.state.turn == CHESS_PIECE_BLACK) {
						if (chessSystem.state.pieceCaptured)
							Audio_PlaySound(SND_chess_check);
						else
							Audio_PlaySound(SND_chess_move);
						
						if (x1 != puzzleMoves[chessSystem.puzzleProgress][0] || x2 != puzzleMoves[chessSystem.puzzleProgress][1]) {
							chessSystem.puzzleState = 1;
							Audio_PlaySound(SND_chess_wrong);
						}
						else {
							chessSystem.puzzleCooldown = 15 + 15 * (chessSystem.puzzleProgress == 0);
							chessSystem.puzzleProgress++;
							if (chessSystem.puzzleProgress >= puzzleMoveCount) {
								chessSystem.puzzleState = 2;
								Audio_PlaySound(SND_chess_mate);
								chessSystem.puzzleCooldown = 120;
							}
						}
					}
				}
				chessSystem.xDrag = -1;
			}
		}
	}
	
	if (chessSystem.pieceAnimationTimer >= 0) {
		chessSystem.pieceAnimationTimer++;
		if (chessSystem.pieceAnimationTimer >= 10) {
			chessSystem.pieceAnimationTimer = -1;
		}
	}
	
	if (PlayerButtonPressed(PLAYER_BUTTON_X)) {
		chessSystem.state = puzzleChessState;
		Chess_FindLegalMoves(&chessSystem.state);
		chessSystem.puzzleState = 0;
		chessSystem.puzzleProgress = 0;
		chessSystem.puzzleCooldown = 0;
		chessSystem.xDrag = -1;
		chessSystem.pieceAnimationTimer = -1;
	}
}

void Chess_Draw() {
	for (int i = 0; i < 64; i++) {
		if (((i + (i >> 3)) & 1) == 0)
			Drawer_SetDrawColor(240, 224, 186);
		else
			Drawer_SetDrawColor(186, 136, 96);
		Drawer_FillRect(chessSystem.boardX + (i & 7) * 32, chessSystem.boardY + (i >> 3) * 32, 32, 32);
	}
	if (chessSystem.xDrag >= 0) {
		Drawer_SetDrawColor(0, 0, 0);
		for (int i = 0; i < chessSystem.state.legalMoveCount; i++) {
			if (chessSystem.state.legalMoves[i][0] == chessSystem.xDrag) {
				int x2 = chessSystem.state.legalMoves[i][1];
				Drawer_SetDrawAlpha(127);
				if (Chess_GetPieceType(&chessSystem.state, x2) > 0) {
					Drawer_FillRect(chessSystem.boardX + (x2 & 7) * 32, chessSystem.boardY + (x2 >> 3) * 32, 8, 8);
					Drawer_FillRect(chessSystem.boardX + (x2 & 7) * 32 + 24, chessSystem.boardY + (x2 >> 3) * 32, 8, 8);
					Drawer_FillRect(chessSystem.boardX + (x2 & 7) * 32, chessSystem.boardY + (x2 >> 3) * 32 + 24, 8, 8);
					Drawer_FillRect(chessSystem.boardX + (x2 & 7) * 32 + 24, chessSystem.boardY + (x2 >> 3) * 32 + 24, 8, 8);
				}
				else
					Drawer_FillRect(chessSystem.boardX + (x2 & 7) * 32 + 12, chessSystem.boardY + (x2 >> 3) * 32 + 12, 8, 8);
				Drawer_SetDrawAlpha(255);
			}
		}
	}
	
	Drawer_SetDrawColor(255, 255, 255);
	for (int i = 0; i < 64; i++) {
		int x = chessSystem.boardX + (i & 7) * 32;
		int y = chessSystem.boardY + (i >> 3) * 32;
		if (chessSystem.state.board[i] > 0 && i != chessSystem.xDrag) {
			int subImage = Chess_GetPieceType(&chessSystem.state, i) - 1;
			if ((chessSystem.state.board[i] & CHESS_PIECE_BLACK) == 0)
				subImage += 6;
			
			if (chessSystem.pieceAnimationTimer >= 0 && chessSystem.pieceAnimationX2 == i) {
				int xPrev = chessSystem.boardX + (chessSystem.pieceAnimationX1 & 7) * 32;
				int yPrev = chessSystem.boardY + (chessSystem.pieceAnimationX1 >> 3) * 32;
				Drawer_DrawSprite(SPR_misc_chess_pieces, xPrev + (x - xPrev) * chessSystem.pieceAnimationTimer / 10, yPrev + (y - yPrev) * chessSystem.pieceAnimationTimer / 10, subImage, 2, 2);
			}
			else {
				Drawer_DrawSprite(SPR_misc_chess_pieces, x, y, subImage, 2, 2);
			}
		}
	}
	if ((chessSystem.puzzleProgress & 1) == 1) {
		int x = chessSystem.boardX + (chessSystem.state.lastMove[1] & 7) * 32;
		int y = chessSystem.boardY + (chessSystem.state.lastMove[1] >> 3) * 32;
		Drawer_SetDrawColor(0, 255, 0);
		Drawer_DrawText("V", 1, x + 20, y - 12, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	if (chessSystem.xDrag >= 0) {
		int subImage = Chess_GetPieceType(&chessSystem.state, chessSystem.xDrag) - 1;
		if ((chessSystem.state.board[chessSystem.xDrag] & CHESS_PIECE_BLACK) == 0)
			subImage += 6;
		Drawer_DrawSprite(SPR_misc_chess_pieces, game.mouseX - 16, game.mouseY - 16, subImage, 2, 2);
	}
	if (chessSystem.puzzleState == 1) {
		Drawer_DrawText("WROOONG!!!", 256, 0, 0, 2, 2);
		int x = chessSystem.boardX + (chessSystem.state.lastMove[1] & 7) * 32;
		int y = chessSystem.boardY + (chessSystem.state.lastMove[1] >> 3) * 32;
		Drawer_SetDrawColor(255, 0, 0);
		Drawer_DrawText("X", 1, x + 20, y - 12, 2, 2);
		Drawer_SetDrawColor(255, 255, 255);
	}
	if (chessSystem.puzzleState == 2) {
		Drawer_DrawText("Puzzle completed!", 256, 0, 0, 2, 2);
	}
	Drawer_DrawText("Mate in 130\n\n"
	"Can you find a\n"
	"checkmate for white\n"
	"within 130 moves?\n\n"
	"White to play and\n"
	"win.", 256, 304, 0, 2, 2);
	
	Drawer_DrawText("Drag the pieces by holding down left\nmouse button. Legal moves will be\nhighlighted for you.\n\nPress X to reset the puzzle.", 256, 0, 296, 2, 2);
}



char Chess_GetFile(char x) {
	return x & 7;
}

char Chess_GetRank(char x) {
	return x >> 3;
}

char Chess_GetPieceType(ChessState* state, char x) {
	return state->board[x] & 7;
}

char Chess_GetPieceColor(ChessState* state, char x) {
	return state->board[x] & CHESS_PIECE_BLACK;
}

void Chess_MovePiece(ChessState* state, char x1, char x2) {
	state->board[x2] = state->board[x1];
	state->board[x1] = 0;
	if (state->board[x2] == 6 && Chess_GetRank(x2) == 0) {
		state->board[x2] = 2;
	}
	else if (state->board[x2] == 14 && Chess_GetRank(x2) == 7) {
		state->board[x2] = 10;
	}
}

bool Chess_MoveIsLegal(ChessState* state, char x1, char x2) {
	for (int i = 0; i < state->legalMoveCount; i++) {
		if (state->legalMoves[i][0] == x1 && state->legalMoves[i][1] == x2) {
			return true;
		}
	}
	return false;
}

void Chess_TryMovePiece(ChessState* state, char x1, char x2) {
	if (!Chess_MoveIsLegal(&chessSystem.state, x1, x2)) return;
	state->pieceCaptured = state->board[x2] > 0;
	Chess_MovePiece(state, x1, x2);
	state->kingCheck = false;
	if (state == &chessSystem.state) {
		Chess_FindLegalMoves(state);
		for (int i = 0; i < state->legalMoveCount; i++) {
			if (Chess_GetPieceType(state, state->legalMoves[i][1]) == CHESS_PIECE_KING) {
				state->kingCheck = true;
				break;
			}
		}
	}
	state->turn = state->turn == CHESS_PIECE_WHITE ? CHESS_PIECE_BLACK : CHESS_PIECE_WHITE;
	Chess_FindLegalMoves(state);
	state->lastMove[0] = x1;
	state->lastMove[1] = x2;
}

void Chess_AddLegalMove(ChessState* state, char x1, char x2) {
	state->legalMoves[state->legalMoveCount][0] = x1;
	state->legalMoves[state->legalMoveCount][1] = x2;
	state->legalMoveCount++;
}

char Chess_CheckLegalMove(ChessState* state, char x1, char x2) {
	if (x2 < 0 || x2 >= 64) return 0;
	if (state->board[x2] == 0 || Chess_GetPieceColor(state, x1) != Chess_GetPieceColor(state, x2)) {
		if (!state->enableKingCaptures) {
			ChessState newState = *state;
			newState.enableKingCaptures = true;
			Chess_MovePiece(&newState, x1, x2);
			newState.turn = newState.turn == CHESS_PIECE_WHITE ? CHESS_PIECE_BLACK : CHESS_PIECE_WHITE;
			Chess_FindLegalMoves(&newState);
			for (int i = 0; i < newState.legalMoveCount; i++) {
				if (Chess_GetPieceType(&newState, newState.legalMoves[i][1]) == CHESS_PIECE_KING) {
					return 1;
				}
			}
		}
		
		Chess_AddLegalMove(state, x1, x2);
		return 1;
	}
	return 0;
}

void Chess_FindLegalMoves(ChessState* state) {
	state->legalMoveCount = 0;
	int x = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < 64; i++) {
		if (state->board[i] == 0 || Chess_GetPieceColor(state, i) != state->turn) continue;
		switch (Chess_GetPieceType(state, i)) {
			case CHESS_PIECE_KING:
				x = i + CHESS_UPLEFT;
				if (Chess_GetFile(i) > 0) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_UP;
				Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_UPRIGHT;
				if (Chess_GetFile(i) < 7) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_LEFT;
				if (Chess_GetFile(i) > 0) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_RIGHT;
				if (Chess_GetFile(i) < 7) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_DOWNLEFT;
				if (Chess_GetFile(i) > 0) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_DOWN;
				Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_DOWNRIGHT;
				if (Chess_GetFile(i) < 7) Chess_CheckLegalMove(state, i, x);
				break;
			case CHESS_PIECE_QUEEN:
				x = i + CHESS_UP;
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					x += CHESS_UP;
				}
				
				x = i + CHESS_DOWN;
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					x += CHESS_DOWN;
				}
				
				x = i + CHESS_LEFT;
				if (Chess_GetRank(i) == Chess_GetRank(x))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					x += CHESS_LEFT;
					if (Chess_GetRank(i) != Chess_GetRank(x)) break;
				}
				
				x = i + CHESS_RIGHT;
				if (Chess_GetRank(i) == Chess_GetRank(x))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					x += CHESS_RIGHT;
					if (Chess_GetRank(i) != Chess_GetRank(x)) break;
				}
				
				x = i + CHESS_UPLEFT;
				if (!(Chess_GetFile(x) == 7))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					if (Chess_GetFile(x) == 0 || Chess_GetFile(x) == 7) break;
					x += CHESS_UPLEFT;
				}
				
				x = i + CHESS_UPRIGHT;
				if (!(Chess_GetFile(x) == 0))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					if (Chess_GetFile(x) == 0 || Chess_GetFile(x) == 7) break;
					x += CHESS_UPRIGHT;
				}
				
				x = i + CHESS_DOWNLEFT;
				if (!(Chess_GetFile(x) == 7))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					if (Chess_GetFile(x) == 0 || Chess_GetFile(x) == 7) break;
					x += CHESS_DOWNLEFT;
				}
				
				x = i + CHESS_DOWNRIGHT;
				if (!(Chess_GetFile(x) == 0))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					if (Chess_GetFile(x) == 0 || Chess_GetFile(x) == 7) break;
					x += CHESS_DOWNRIGHT;
				}
				break;
			case CHESS_PIECE_ROOK:
				x = i + CHESS_UP;
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					x += CHESS_UP;
				}
				
				x = i + CHESS_DOWN;
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					x += CHESS_DOWN;
				}
				
				x = i + CHESS_LEFT;
				if (Chess_GetRank(i) == Chess_GetRank(x))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					x += CHESS_LEFT;
					if (Chess_GetRank(i) != Chess_GetRank(x)) break;
				}
				
				x = i + CHESS_RIGHT;
				if (Chess_GetRank(i) == Chess_GetRank(x))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					x += CHESS_RIGHT;
					if (Chess_GetRank(i) != Chess_GetRank(x)) break;
				}
				break;
			case CHESS_PIECE_KNIGHT:
				x = i + CHESS_UPLEFT + CHESS_UP;
				if (Chess_GetFile(i) > 0) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_UPLEFT + CHESS_LEFT;
				if (Chess_GetFile(i) > 1) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_UPRIGHT + CHESS_UP;
				if (Chess_GetFile(i) < 7) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_UPRIGHT + CHESS_RIGHT;
				if (Chess_GetFile(i) < 6) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_DOWNLEFT + CHESS_DOWN;
				if (Chess_GetFile(i) > 0) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_DOWNLEFT + CHESS_LEFT;
				if (Chess_GetFile(i) > 1) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_DOWNRIGHT + CHESS_DOWN;
				if (Chess_GetFile(i) < 7) Chess_CheckLegalMove(state, i, x);
				
				x = i + CHESS_DOWNRIGHT + CHESS_RIGHT;
				if (Chess_GetFile(i) < 6) Chess_CheckLegalMove(state, i, x);
				break;
			case CHESS_PIECE_BISHOP:
				x = i + CHESS_UPLEFT;
				if (!(Chess_GetFile(x) == 7))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					if (Chess_GetFile(x) == 0 || Chess_GetFile(x) == 7) break;
					x += CHESS_UPLEFT;
				}
				
				x = i + CHESS_UPRIGHT;
				if (!(Chess_GetFile(x) == 0))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					if (Chess_GetFile(x) == 0 || Chess_GetFile(x) == 7) break;
					x += CHESS_UPRIGHT;
				}
				
				x = i + CHESS_DOWNLEFT;
				if (!(Chess_GetFile(x) == 7))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					if (Chess_GetFile(x) == 0 || Chess_GetFile(x) == 7) break;
					x += CHESS_DOWNLEFT;
				}
				
				x = i + CHESS_DOWNRIGHT;
				if (!(Chess_GetFile(x) == 0))
				while (Chess_CheckLegalMove(state, i, x)) {
					if (state->board[x] > 0) break;
					if (Chess_GetFile(x) == 0 || Chess_GetFile(x) == 7) break;
					x += CHESS_DOWNRIGHT;
				}
				break;
			case CHESS_PIECE_PAWN:
				x = i + CHESS_UP + CHESS_DOWN*2*(Chess_GetPieceColor(state, i) == CHESS_PIECE_BLACK);
				
				if (Chess_GetPieceType(state, x) == 0)
					if (Chess_CheckLegalMove(state, i, x) && Chess_GetRank(i) == 6 - (Chess_GetPieceColor(state, i) == CHESS_PIECE_BLACK)*5 && Chess_GetPieceType(state, x + CHESS_UP + CHESS_DOWN*2*(Chess_GetPieceColor(state, i))) == 0)
						Chess_CheckLegalMove(state, i, x + CHESS_UP + CHESS_DOWN*2*(Chess_GetPieceColor(state, i) == CHESS_PIECE_BLACK));
				
				if (Chess_GetPieceType(state, x + CHESS_LEFT) > 0 && Chess_GetFile(x) > 0)
					Chess_CheckLegalMove(state, i, x + CHESS_LEFT);
				if (Chess_GetPieceType(state, x + CHESS_RIGHT) > 0 && Chess_GetFile(x) < 7)
					Chess_CheckLegalMove(state, i, x + CHESS_RIGHT);
				
				break;
		}
	}
}
