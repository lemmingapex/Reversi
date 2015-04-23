#include <algorithm>
#include <string>
#include <vector>

#include "agent.h"

using namespace std;

template<typename Reversi>
void Agent<Reversi>::otherMove(const Action& a) {
	theGame.play(a);
}

template<typename Reversi>
void Agent<Reversi>::playerMove(Action& a) {
	vector<typename Reversi::Action> actions(theGame.actionBegin(), theGame.actionEnd());
	a = actions[minMaxAlphaBeta(theGame,0,-999999,999999)];
	theGame.play(a);
}

template<typename Reversi>
int Agent<Reversi>::minMaxAlphaBeta(Reversi& currentGame, unsigned int depth, int alpha, int beta) {
	if(depth >= maxDepth || currentGame.actionBegin() == currentGame.actionEnd()) {
		return heuristic(currentGame);
	}

	Reversi tempGame;
	int score, actionCounter = 0, bestAction = 0;

	if(depth%2 == 0) {
		for(Action iter = currentGame.actionBegin(); iter != currentGame.actionEnd(); iter++) {
			tempGame = currentGame;
			tempGame.play(iter);
			score = minMaxAlphaBeta(tempGame,depth+1,alpha,beta);
			if(score > alpha) {
				bestAction = actionCounter;
				alpha = score;
			}
			if(alpha>=beta) {
				bestAction = actionCounter;
				return alpha;
			}
			actionCounter++;
		}
		if(depth == 0) {
			return bestAction;
		}
		else {
			return alpha;
		}
	}
	else {
		for(Action iter = currentGame.actionBegin(); iter != currentGame.actionEnd(); iter++) {
			tempGame = currentGame;
			tempGame.play(iter);
			score = minMaxAlphaBeta(tempGame,depth+1,alpha,beta);
			if(score < beta) {
				bestAction = actionCounter;
				beta = score;
			}
			if(alpha>=beta) {
				bestAction = actionCounter;
				return beta;
			}
			actionCounter++;
		}
		if(depth == 0) {
			return bestAction;
		}
		else {
			return beta;
		}
	}
}

template<typename Reversi>
int Agent<Reversi>::heuristic(Reversi& currentGame) {
	int score = 0;

	// corners
	for(unsigned int i=0; i < currentGame.boardSize; i+=currentGame.boardSize-1) {
		for(unsigned int j=0; j < currentGame.boardSize; j+=currentGame.boardSize-1) {
			if(currentGame.getSquare(i, j) == thePlayer) {
				score += 5;
			} else if(currentGame.getSquare(i, j) != 2) {
				score -= 5;
			}
		}
	}

	// edges
	for(unsigned int i=0; i < currentGame.boardSize; i++) {
		if(currentGame.getSquare(i,0) == thePlayer)
			score++;
		if(currentGame.getSquare(i,currentGame.boardSize-1) == thePlayer)
			score++;
		if(currentGame.getSquare(0,i) == thePlayer)
			score++;
		if(currentGame.getSquare(currentGame.boardSize-1,i) == thePlayer)
			score++;
	}

	// near corners
	if(currentGame.getSquare(0,1) == thePlayer && currentGame.getSquare(0,0) == 2)
		score -= 5;
	if(currentGame.getSquare(1,1) == thePlayer && currentGame.getSquare(0,0) == 2)
		score -= 5;
	if(currentGame.getSquare(1,0) == thePlayer && currentGame.getSquare(0,0) == 2)
		score -= 5;

	if(currentGame.getSquare(0,currentGame.boardSize-2) == thePlayer && currentGame.getSquare(0,currentGame.boardSize-1) == 2)
		score -= 5;
	if(currentGame.getSquare(1,currentGame.boardSize-2) == thePlayer && currentGame.getSquare(0,currentGame.boardSize-1) == 2)
		score -= 5;
	if(currentGame.getSquare(1,currentGame.boardSize-1) == thePlayer && currentGame.getSquare(0,currentGame.boardSize-1) == 2)
		score -= 5;

	if(currentGame.getSquare(currentGame.boardSize-2,0) == thePlayer && currentGame.getSquare(currentGame.boardSize-1,0) == 2)
		score -= 5;
	if(currentGame.getSquare(currentGame.boardSize-2,1) == thePlayer && currentGame.getSquare(currentGame.boardSize-1,0) == 2)
		score -= 5;
	if(currentGame.getSquare(currentGame.boardSize-1,currentGame.boardSize-1) == thePlayer && currentGame.getSquare(currentGame.boardSize-1,0) == 2)
		score -= 5;

	if(currentGame.getSquare(currentGame.boardSize-2,currentGame.boardSize-2) == thePlayer && currentGame.getSquare(currentGame.boardSize-1,currentGame.boardSize-1) == 2)
		score -= 5;
	if(currentGame.getSquare(currentGame.boardSize-2,currentGame.boardSize-1) == thePlayer && currentGame.getSquare(currentGame.boardSize-1,currentGame.boardSize-1) == 2)
		score -= 5;
	if(currentGame.getSquare(currentGame.boardSize-1,currentGame.boardSize-2) == thePlayer && currentGame.getSquare(currentGame.boardSize-1,currentGame.boardSize-1) == 2)
		score -= 5;

	if(thePlayer)
		return -1.0*currentGame.score() + score;
	else
		return currentGame.score() + score;
}
