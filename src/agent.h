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

		Agent(bool p, const int& maxd) : thePlayer(p),maxDepth(maxd) {
			name="my agent at depth " + itos(maxDepth);
		}

		void playerMove(Action& a, Reversi& currentGame);
		int minMaxAlphaBeta(Reversi& currentGame, unsigned int level, int alpha, int beta);
		int getBestMove(Reversi& currentGame, int level);
		int heuristic(Reversi& currentGame);
	private:
		bool thePlayer;
		unsigned int maxDepth;
};

#endif // AGENT_H
