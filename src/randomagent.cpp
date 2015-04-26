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

		void playerMove(Action& a, Reversi& currentGame);
	private:
		static bool seeded;
		bool thePlayer;
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
void RandomAgent<Reversi>::playerMove(Action& a, Reversi& currentGame) {
	vector<typename Reversi::Action> actions(currentGame.actionBegin(), currentGame.actionEnd());
	a = actions[rand()%actions.size()];
}
