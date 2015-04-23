#include <algorithm>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

template<typename Reversi>
class RandomAgent {
	public:
		typedef typename Reversi::Action Action;

		string name;

		RandomAgent(bool p);
		RandomAgent(bool p, const Reversi& game);

		void otherMove(const Action& a);
		void playerMove(Action& a);
	private:
		static bool seeded;
		bool thePlayer;
		Reversi theGame;
};

template<typename Reversi>
bool RandomAgent<Reversi>::seeded = false;

template<typename Reversi>
RandomAgent<Reversi>::RandomAgent(bool p) : thePlayer(p) {
	name="random agent";
	if(!seeded) {
		srand(time(NULL));
		seeded = true;
	}
}

template<typename Reversi>
RandomAgent<Reversi>::RandomAgent(bool p, const Reversi& game) : thePlayer(p), theGame(game) {
	name="random agent";
	if(!seeded) {
		srand(time(NULL));
		seeded = true;
	}
}

template<typename Reversi>
void RandomAgent<Reversi>::otherMove(const Action& a) {
	theGame.play(a);
}

template<typename Reversi>
void RandomAgent<Reversi>::playerMove(Action& a) {
	vector<typename Reversi::Action> actions(theGame.actionBegin(), theGame.actionEnd());
	a = actions[rand()%actions.size()];
	theGame.play(a);
}
