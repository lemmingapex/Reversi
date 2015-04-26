#ifndef REVERSI_H
#define REVERSI_H

#include <bitset>
#include <iterator>

using namespace std;

class Reversi {
	public:
		class Action;

		unsigned int boardSize;

		enum square {
			black=0,
			white=1,
			none=2
		};

		//square* pieces;

		bitset<64> blackPieces;
		bitset<64> whitePieces;


		// white(0) or black(1)
		bool player;

		// ctor
		Reversi() {
			boardSize = 8;
			player = black;
			//pieces = new square[boardSize*boardSize];
			//fill_n(pieces, boardSize*boardSize, none);

			setSquare(boardSize/2-1, boardSize/2-1, white);
			setSquare(boardSize/2, boardSize/2, white);
			setSquare(boardSize/2, boardSize/2-1, black);
			setSquare(boardSize/2-1, boardSize/2, black);
		}

		int score() const {
			int score = blackPieces.count() - whitePieces.count();
			return score;
		}

		void printBoard();

		void play(const Action& a);

		Action actionBegin() const;
		Action actionEnd() const;

		square getSquare(unsigned int r, unsigned int c) const;
		void setSquare(unsigned int r, unsigned int c, square s);

		void flipSquares(const Action& a, unsigned int r, unsigned int c);
};

class Reversi::Action : public iterator<input_iterator_tag, Reversi::Action> {
	public:
		unsigned int row;
		unsigned int col;
		const Reversi* game;

		// ctors
		Action() {
			game=NULL;
			row=0;
			col=0;
		}

		Action(unsigned int Row, unsigned int Col) {
			game=NULL;
			row=Row;
			col=Col;
		}

		// Iterator constructor
		explicit Action(const Reversi* _game);

		bool operator == (const Action& R) const {
			return row == R.row && col == R.col;
		}

		bool operator != (const Action& R) const {
			return row != R.row || col != R.col;
		}

		// Functions needed for this to class to be a model of Input Iterator
		const Action& operator++();
		Action operator++(int);
		const Action& operator*() const;

		// The following functions are not needed by Action
		unsigned int getRow() const {
			return row;
		}

		unsigned int getCol() const {
			return col;
		}

		bool isPass() const {
			return row == 255 && col == 255;
		}

		void setRow(unsigned int Row) {
			row = Row;
		}

		void setCol(unsigned int Col) {
			col = Col;
		}

		void setPass() {
			row = col = 255;
		}

		bool isLegal() const;
		bool checkSquares(unsigned int rIncr, unsigned int cIncr) const;
};


#endif // REVERSI_H
