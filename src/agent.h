#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <sstream>

using namespace std;

inline string itos(int i) {
	string s;
	stringstream out;
	out << i;
	s = out.str();
	return s;
}

template<typename Reversi>
class Agent {
	public:
		typedef typename Reversi::Action Action;

		string name;

		Agent(bool p) : thePlayer(p) {
			name="my agent at depth " + itos(maxDepth);
		}

		Agent(bool p, const Reversi& game) : thePlayer(p),theGame(game) {
			name="my agent at depth " + itos(maxDepth);
		}

		Agent(bool p, const Reversi& game, const int& maxd) : thePlayer(p),theGame(game),maxDepth(maxd) {
			name="my agent at depth " + itos(maxDepth);
		}

		void otherMove(const Action& a);
		void playerMove(Action& a);
		int minMaxAlphaBeta(Reversi& currentGame, unsigned int level, int alpha, int beta);
		int getBestMove(Reversi& currentGame, int level);
		int heuristic(Reversi& currentGame);
	private:
		bool thePlayer;
		Reversi theGame;
		unsigned int maxDepth;
};

#endif // AGENT_H
