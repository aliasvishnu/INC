#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdlib.h>

using namespace std;

// O for computer
// X for player

struct threeInt{
	int first;
	int second;
	int third;
};

struct twoInt{
	int first;
	int second;
};

class board{
private:
	char brd[3][3];
	char turn[10];
	int depth;
	int mainBoard;
	struct twoInt choice;
public:
	char getValue(int locX, int locY){
		return brd[locX][locY];
	}
	void setValue(char sym, int locX, int locY){
		brd[locX][locY] = sym;
	}
	void putValue(int locX, int locY){
		cout << " " << brd[locX][locY] << " ";
	}
	char* getTurn(){
		return turn;
	}
	void togglePlayer(){
		if(!strcmp(getTurn(), "player")) strcpy(turn, "computer");
		else strcpy(turn, "player");
	}
	board(){
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; ++j){
				setValue('-', i, j);
			}
		}
		choice.first = 1; choice.second = 1;
		strcpy(turn, "computer");
		depth = 0;
		mainBoard = 1;
	}
	board(board parent, int locX, int locY){
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; ++j){
				setValue(parent.getValue(i, j), i, j);
			}
		}	
		depth = parent.depth + 1;		
		strcpy(turn, parent.getTurn());
		togglePlayer();
		mainBoard = 0;

		if(!strcmp(turn, "player")){
			setValue('O', locX, locY);
		}else{
			setValue('X', locX, locY);
		}
	}
	void displayBoard(){
		cout << "\n";
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; ++j){
				putValue(i, j);
			}
			cout << "\n";
		}
	}
	void computerMove(){
		minimax();
	    setValue('O', choice.first, choice.second);
		
	    depth += 1;		
		displayBoard();
		if(winner() == 1){
			cout << "You lost!" << "\n";
			exit(0);
		}
		if(over()){
			cout << "Draw!\n";
			exit(0);
		}
		playerMove();
	}

	void playerMove(){
		int a;
		cout << "\nWhere would you like to place?";
		cin >> a;

		int locX, locY;
		switch(a){
			case 1 : locX = 0; locY = 0; break;
			case 2 : locX = 0; locY = 1; break;
			case 3 : locX = 0; locY = 2; break;
			case 4 : locX = 1; locY = 0; break;
			case 5 : locX = 1; locY = 1; break;
			case 6 : locX = 1; locY = 2; break;
			case 7 : locX = 2; locY = 0; break;
			case 8 : locX = 2; locY = 1; break;
			case 9 : locX = 2; locY = 2; break;
		}

		if(getValue(locX, locY) == '-'){
			setValue('X', locX, locY);
			depth += 1;
			displayBoard();
			if(winner() == 1){
				cout << "You have won\n";
				exit(0);
			}
			if(over()){
				cout << "Draw!\n";
				exit(0);
			}
			computerMove();
		}else {
			cout << "\nThat's taken dear!";
			playerMove();
		}
	}
	int score(){
		if(strcmp(turn, "player") && winner()){ //Meaning computer won
			return (10 - depth);
		}	
		else if(strcmp(turn, "computer") && winner()) {
			return (depth - 10) ;
		}
		else{ 
			return 0;
		}
	}
	// Says if the game got over - Take care when to call
	int winner(){
		int game = 0;		// Nobody has won yet

		if(brd[0][0] == brd [1][1] && brd [1][1] == brd[2][2] && brd[2][2] != '-') game = 1;
		if(brd[0][0] == brd [0][1] && brd [0][1] == brd[0][2] && brd[0][2] != '-') game = 1;
		if(brd[1][0] == brd [1][1] && brd [1][1] == brd[1][2] && brd[1][2] != '-') game = 1;
		if(brd[2][0] == brd [2][1] && brd [2][1] == brd[2][2] && brd[2][2] != '-') game = 1;
		if(brd[0][0] == brd [1][0] && brd [1][0] == brd[2][0] && brd[2][0] != '-') game = 1;
		if(brd[0][1] == brd [1][1] && brd [1][1] == brd[2][1] && brd[2][1] != '-') game = 1;
		if(brd[0][2] == brd [1][2] && brd [1][2] == brd[2][2] && brd[2][2] != '-') game = 1;
		if(brd[2][0] == brd [1][1] && brd [1][1] == brd[0][2] && brd[0][2] != '-') game = 1;

		return game;
	}
	bool over(){
		int flag = 1;
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; ++j){
				if(getValue(i, j) == '-') flag = 0;
			}
		}

		int ifWin = winner();
		// Condition says if someone won or if the game is draw
		if(ifWin || (!ifWin && flag)) return 1;
		else return 0;
	}

	int minimax(){
		if(over()){
			return score();
		}

		struct twoInt moves[10], temp;
		int scores[10], count = 0;

		// Collect all legal moves into the moves array
		for(int i = 0; i < 3; i++){
			for (int j = 0; j < 3; ++j){
				if(getValue(i, j) == '-'){
					temp.first = i; temp.second = j;
					moves[count++] = temp;
				}
			}
		}
		
		if(!strcmp(turn, "player")){
			int bestValue = -32000;
			for(int i = 0; i < count; i++){
				board newGamePath(*this, moves[i].first, moves[i].second);
				int val = newGamePath.minimax();
				if(bestValue < val){
					choice.first = moves[i].first;
					choice.second = moves[i].second;
					bestValue = val;
				}
			}
			return bestValue;
		}else{
			int bestValue = 32000;
			for(int i = 0; i < count; i++){
				board newGamePath(*this, moves[i].first, moves[i].second);
				int val = newGamePath.minimax();
				if(bestValue > val){
					choice.first = moves[i].first;
					choice.second = moves[i].second;
					bestValue = val;
				}
			}
			return bestValue;
		}
	}
};

int main(){
	cout << "Welcome to my TIC TAC TOE\n";
	int start = 0;
	cout << "Do you wanna start?";
	cin >> start;

	board nemesis;
	if(start == 1){
			nemesis.playerMove();
	}else{
		nemesis.computerMove();
	}
return 0;
}
