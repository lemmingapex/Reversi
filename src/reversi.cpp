#include <cassert>
#include <iostream>

#include "reversi.h"

void Reversi::play(const Action& a) {
	// Pass?
	if ( a.isPass() ) {
		player = !player;
		return;
	}

	flipSquares(a, 1, 1);
	flipSquares(a, 0, 1);
	flipSquares(a,-1, 1);
	flipSquares(a,-1, 0);
	flipSquares(a,-1,-1);
	flipSquares(a, 0,-1);
	flipSquares(a, 1,-1);
	flipSquares(a, 1, 0);

	setSquare(a.getRow(),a.getCol(),(square)player);

	player = !player;
}

Reversi::Action Reversi::actionBegin() const {
	// Return the iterator
	return Action(this);
}

Reversi::Action Reversi::actionEnd() const {
	return Action(boardSize,0);
}

void Reversi::printBoard() {
	cout << endl;
	for(unsigned int r = 0; r < boardSize; r++ ) {
		for(unsigned int c = 0; c < boardSize; c++ ) {
			switch (getSquare(r,c)) {
				case Reversi::black:
					cout << "X";
					break;
				case Reversi::white:
					cout << "O";
					break;
				default:
					cout << ".";
			}
			cout << " ";
		}
		cout << endl;
	}
}

void Reversi::flipSquares(const Action& a, unsigned int rIncr, unsigned int cIncr) {
	square thePlayer((square)player);
	square otherPlayer((square)!player);
	const unsigned int origRow = a.getRow();
	const unsigned int origCol = a.getCol();
	unsigned int row = origRow + rIncr;
	unsigned int col = origCol + cIncr;

	while(row < boardSize && col < boardSize) {
		square theSquare = getSquare(row, col);
		if(theSquare == otherPlayer) {
			row += rIncr;
			col += cIncr;
			continue;
		}
		if ( theSquare == thePlayer ) {
			row -= rIncr;
			col -= cIncr;
			while ( row != origRow || col != origCol ) {
				setSquare(row,col,thePlayer);
				row -= rIncr;
				col -= cIncr;
			}
			break;
		}
		// Empty square
		break;
	}
}

Reversi::square Reversi::getSquare(unsigned int r, unsigned int c) const {
	assert(r < boardSize);
	assert(c < boardSize);
	if(blackPieces[r*boardSize + c]) {
		return black;
	}
	if(whitePieces[r*boardSize + c]) {
		return white;
	}
	return none;
}

void Reversi::setSquare(unsigned int r, unsigned int c, square s) {
	assert(r < boardSize);
	assert(c < boardSize);
	if ( s == black ) {
		blackPieces[r*boardSize + c] = true;
		whitePieces[r*boardSize + c] = false;
	}
	else if ( s == white ) {
		blackPieces[r*boardSize + c] = false;
		whitePieces[r*boardSize + c] = true;
	}
	else {
		blackPieces[r*boardSize + c] = false;
		whitePieces[r*boardSize + c] = false;
	}
}

Reversi::Action::Action(const Reversi* _game) :	game(_game), row(0), col(0) {
	if(!isLegal()) {
		operator++();
	}

	// Action is a pass, or the game is over?
	if ( *this == _game->actionEnd() ) {
		Reversi newGame(*_game);
		newGame.player = !newGame.player;
		setRow(0);
		setCol(0);
		game = &newGame;
		if ( !isLegal() ) {
			operator++();
		}

		// Game over?
		if ( *this == _game->actionEnd() ) {
			setCol(0);
			setRow(game->boardSize);
		}

		// Pass?
		else {
			setPass();
		}
		game = _game;
	}
}

const Reversi::Action& Reversi::Action::operator++() {
	if ( isPass() ) {
		setCol(0);
		setRow(game->boardSize);
		return *this;
	}

	do {
		setCol(getCol()+1);
		if ( getCol() >= game->boardSize ) {
			setCol(0);
			setRow(getRow()+1);
		}
	}
	while (getRow() < game->boardSize && !isLegal());
	return *this;
}

Reversi::Action Reversi::Action::operator++(int) {
	Action temp(*this);
	++(*this);
	return temp;
}

const Reversi::Action& Reversi::Action::operator*() const {
	return *this;
}

bool Reversi::Action::isLegal() const {
	return game->getSquare(row,col) == none &&
		(checkSquares( 1, 1) ||
		checkSquares( 0, 1) ||
		checkSquares(-1, 1) ||
		checkSquares(-1, 0) ||
		checkSquares(-1,-1) ||
		checkSquares( 0,-1) ||
		checkSquares( 1,-1) ||
		checkSquares( 1, 0));
}

bool Reversi::Action::checkSquares(unsigned int rIncr, unsigned int cIncr) const {
	square thePlayer((square)game->player);
	square otherPlayer((square)!game->player);

	// neighbor postion
	unsigned int row = getRow() + rIncr;
	unsigned int col = getCol() + cIncr;

	if( row >= boardSize || col >= boardSize ) {
		return false;
	}

	// If the immediate neighbor is the same?
	if( game->getSquare(row,col) == thePlayer) {
		return false;
	}

	while(row < boardSize && col < boardSize) {
		square theSquare = game->getSquare(row,col);
		if(theSquare == otherPlayer) {
			row += rIncr;
			col += cIncr;
			continue;
		}
		if(theSquare == thePlayer) {
			return true;
		}

		// Blank square
		return false;
	}

	// Off bounds
	return false;
}
