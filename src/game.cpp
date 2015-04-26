#include <iostream>

#include "reversi.h"
#include "agent.cpp"
#include "randomagent.cpp"

using namespace std;

int main(int argc, char** argv) {
	int games=100;
	int sum=0;
	int wins=0, losses=0, ties=0;

	Reversi game = Reversi();

	for(int i=0; i<games; i++) {
		game = Reversi();
		Agent<Reversi> agent0(Reversi::black, 5);
		RandomAgent<Reversi> agent1(Reversi::white);

		//game.printBoard();
		while(game.actionBegin() != game.actionEnd()) {
			if(game.player == Reversi::black) {
				Reversi::Action act;
				//cout << "Black: "<< endl;
				agent0.playerMove(act, game);
				game.play(act);
			} else {
				Reversi::Action act;
				//cout << "White: " << endl;
				agent1.playerMove(act, game);
				game.play(act);
			}
			//game.printBoard();
		}
		game.printBoard();
		cout << "Black - White: " << game.score() << endl;
		if(game.score()>0) {
			wins++;
		} else if(game.score()<0) {
			losses++;
		} else {
			ties++;
		}
		sum+=game.score();

		if(games-1==i) {
			cout << "games played: " << games << endl;
			cout << "between " << agent0.name << " and " << agent1.name << endl;
			cout << "wins: " << wins << endl;
			cout << "losses: " << losses << endl;
			cout << "ties: " << ties << endl;
			cout << "average score (black-white): " << (double)sum/(double)games << endl;
		}
	}
}
