/*
 * Author: Jeffrey A. Robinson
 * 
 * Game of Nim.  Allows either 1 or 2 players.  Single player game goes against AI.
 * 
 */
 
#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>

// Holds the best moves at this state
class State {

	private:
		std::default_random_engine gen;
		size_t *moves,count,numMoves;
		size_t move;
		
	public:
		State(int k) {
			moves = new size_t[k];
			for(int i = 0; i < k;++i) moves[i] = 1;
			numMoves = k;
			count = k;
		}
		
		~State() {
			delete[] moves;
		}
		
		size_t randomMove() {
			// Generate a number between 1 and count (inclusive)
			std::uniform_int_distribution<size_t> dist(1,count);
			size_t ball = dist(gen);
		
			// Find where that ball is
			move = 0;
			int sum = moves[move];
			while(sum < ball) sum += moves[++move];
			return move + 1;
		}
		
		void won() {
			++moves[move];
			++count;
		}
		
		void lost() {
			if(moves[move] > 1) {
				--moves[move];
				--count;
			}
		}
};

// Train to hold best move to make at each state
bool train(State** state, int n) {
	if(n == 1) return true;
	if(n == 0) return false;
	
	State *s = state[n-1];
	
	int move = s->randomMove();
	bool won = train(state,n - move);
	
	if(won) s->won();
	else s->lost();
	
	return !won;
}

// Convert size_t to string, template would have been better
std::string toString(size_t value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

// Prompt and read in an option, keep reading unless valid.  Only works for ranges
size_t readOption(std::string msg,size_t lower, size_t upper) {
	size_t result = upper;
	do {
		if(result != upper) std::cout << "Please enter a number between " << lower << " and " << upper << std::endl;
		std::cout << msg;
		std::cin >> result;
	} while(result < lower || result > upper );
	return result;
}

// Asks for players move, if the move picks up last stick return true, false otherwise
size_t playerMove(size_t player,size_t& remaining, size_t minMove) {
	std::cout << "\nThere are " << remaining << " sticks on the board." << std::endl;
	remaining -= readOption("Player " + toString(player) + ": How many sticks do you take (1-" + toString(minMove) + ")? ",1,minMove);
	if(remaining == 0) std::cout << "Player " + toString(player) + ", you lose" << std::endl;
	return remaining == 0;
}

// Play the game of nim
void play(size_t sticks, size_t k, bool useAi,State** states) {
	while(true) {
		size_t remaining = sticks;
		while(true) {
			if(playerMove(1,remaining,std::min(k,remaining))) break;
			
			if(useAi) {
				std::cout << "\nThere are " << remaining << " sticks on the board." << std::endl;
				size_t move = states[remaining-1]->randomMove();
				std::cout << "AI selects " << move << std::endl;
				remaining -= move;
				if(remaining == 0) {
					std::cout << "AI loses." << std::endl;
					break;
				}
			}else if(playerMove(2,remaining,std::min(k,remaining))) break;
			
		}
		if(readOption("Play again (1 = yes, 0 = no)? ",0,1) == 0) break;
	}
}

// prompt and read game options
void readOptions(size_t& sticks, size_t& k, bool& useAi) {
	const std::string StickOptionMsg = "How many sticks are there on the table initially (10-100)? ";
	const size_t SticksLower = 10, SticksUpper = 100;
	
	const std::string MoveOptionMsg = "How many sticks can be picked up per round (2-20)? ";
	const size_t MovesLower = 2, MovesUpper = 20;
	
	const std::string PlayerOptionMsg = "\n\nOptions:\n  Play against a friend (1)\n  Play against a computer (2)\nWhich option do you take (1-2)? ";
	const size_t PlayersLower = 1, PlayersUpper = 2;

	sticks = readOption(StickOptionMsg,SticksLower,SticksUpper);
	k = readOption(MoveOptionMsg,MovesLower,MovesUpper);
	useAi = readOption(PlayerOptionMsg,PlayersLower,PlayersUpper) == 2;
}

// Create and initialize AI, train.
void setupAi(State*** states,size_t sticks,size_t k) {
	State** result = new State*[sticks];
	for(size_t i = 0;i < sticks;++i) result[i] = new State(std::min(i+1,k));
	
	std::cout << "Training AI, please wait..." << std::endl;
	for(int j = 2; j <= sticks;++j) {
		for(size_t i = 0 ; i < j*sticks;++i) {
			train(result,j);
		}
	}
	*states = result;
}

// Clean up resources allocated for AI
void cleanupAi(State*** states,size_t sticks) {
	for(int i = 0;i < sticks;++i) delete (*states)[i];
	delete[] *states;
}

int main(void) {
	std::cout << "Welcome to the game of sticks!" << std::endl;
	size_t sticks,k;
	bool useAi;
	
	readOptions(sticks,k,useAi);
	
	State** states = NULL;
	if(useAi) setupAi(&states,sticks,k);
	
	play(sticks,k,useAi,states);
	
	if(useAi) cleanupAi(&states,sticks);
	
	return 0;
}