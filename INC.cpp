#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class board{
private:
	char brd[3][3];
	int score;
	char turn[10];
	int depth;
	vector<pair<int, int> > availableMoves;
	vector<pair<int, int> > availableScores;
public:
	board(char player[]){
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; ++j){
				this.setValue(' - ', i, j);
			}
		}
		strcpy(this.turn, "player");
		depth = 0;
	}

	board(board parent, int locX, int locY){
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; ++j){
				this.setValue(parent.getValue(i, j), i, j);
			}
		}	
		this.depth += 1;
		this.togglePlayer();
		if(strcmp == "player"){
			this.brd[locX][locY] = 'x';
		}else{
			this.brd[locX][locY] = '0';
		}
	}
	
	void setValue(char sym, int locX, int locY){
		this.brd[locX][locY] = sym;
	}

	void putValue(int locX, int locY){
		cout << " " << this.brd[locX][locY] << " ";
	}

	void togglePlayer(char turnParent[]){
		if(!strcmp(turnParent, "computer")) strcpy(this.turn, "player");
		if(!strcmp(turnParent, "player")) strcpy(this.turn, "computer");
	}

	void displayBoard(){
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; ++j){
				this.putValue(' - ', i, j);
			}
		}
	}

	char getValue(int locX, int locY){
		return this.brd[locX][locY];
	}

	int winner(){
		if(brd[0][0] == brd [1][1] && brd [1][1] == brd[2][2]) return 1;
		if(brd[0][0] == brd [0][1] && brd [0][1] == brd[0][2]) return 1;
		if(brd[1][0] == brd [1][1] && brd [1][1] == brd[1][2]) return 1;
		if(brd[2][0] == brd [2][1] && brd [2][1] == brd[2][2]) return 1;
		if(brd[0][0] == brd [1][0] && brd [1][0] == brd[2][0]) return 1;
		if(brd[0][1] == brd [1][1] && brd [1][1] == brd[2][1]) return 1;
		if(brd[0][2] == brd [1][2] && brd [1][2] == brd[2][2]) return 1;
		if(brd[2][0] == brd [1][1] && brd [1][1] == brd[0][2]) return 1;
		return 0;
	}

	void calculateAvailableMoves(){
		for(int i = 0; i < 3 ; i++){
			for(int j = 0; j < 3 ; j++){
				if(this.getValue(i, j) == '-') this.availableMoves.push_back(pair<int, int>(i, j));
			}
		}
	}

	int score(){
		if(strcmp(this.turn, "player"))	return 10 - depth;
		else return depth;
	}

	int minimax(this){
		// Check if the game is over or not
		if(this.winner()) return this.score();

		// Calculate all possible moves in the board
		calculateAvailableMoves(); 

		// For each move, find out the score
		for (vector<pair<int, int> >::iterator i = this.availableMoves.begin(); i != this.availableMoves.end(); ++i){
			board newGamePath = new board(this, (*i)->first, (*i)->second);
			this.availableScores.push_back(newGamePath.minimax());
		}

		if(strcmp(this.turn, "player") == ){
			// Meaning next move belongs to computer	
		} 

	}



	~board();
	
};

int main(){
	
}