var toggle = 1;
// 0 if computer move
// 1 if human move

function twoInt(type){
	this.first = 0;
	this.second = 0;
}

function threeInt(type){
	this.first = 0;
	this.second = 0;
	this.third = 0;
}

function board(type){
	// this.brd = [[],[],[]];
	this.brd = [['-','-','-'],['-','-','-'],['-','-','-']];
	this.turn;
	this.depth;
	this.choice = new twoInt();

	this.getValue = function(locX, locY){
		return this.brd[locX][locY];
	}
	this.setValue = function(sym, locX, locY){
		this.brd[locX][locY] = sym;
	}
	this.putValue = function(locX, locY){
		var index = '';
		index = (locX) * 3 + (locY + 1);
		if(this.brd[locX][locY] == 'X'){
			document.getElementById("box" + index).style.backgroundPosition = "-400px 0px";			
		}else{
			document.getElementById("box" + index).style.backgroundPosition = "0px 0px";
		}
	}
	this.getTurn = function(){
		return this.turn;
	}
	this.togglePlayer = function(){
		if(this.getTurn() == "player") this.turn = "computer";
		else this.turn = "player";
	}
	this.boardConstructor = function(parent, locX, locY){
		if(parent == undefined){
			for(var i = 0; i < 3; i++){
				for(var j = 0; j < 3; j++){
					this.setValue('-', i, j);
				}
			}
			this.choice.first = 0; this.choice.second = 0;
			this.turn = "computer";
			this.depth = 0;
		}else{
			for(var i = 0; i < 3; i++){
				for(var j = 0; j < 3; j++){
					this.setValue(parent.getValue(i, j), i, j);
				}
			}
			this.depth = parent.depth + 1;
			this.turn = parent.getTurn();
			this.togglePlayer();

			if(this.turn == "player") this.setValue('O', locX, locY);
			else this.setValue('X', locX, locY);
		}
	}
	this.computerMove = function(){
		if(toggle == 0){
			console.log("Computer about to play");
			this.minimax();
			console.log("Minimax complete");
			console.log("Position " + this.choice.first + "  " + this.choice.second);
			this.setValue('O', this.choice.first, this.choice.second);
			this.putValue(this.choice.first, this.choice.second);
			
			this.depth += 1;
			if(this.winner() == 1){
				alert("You lost :(");
			}
			if(this.over()){
				alert("Draw!");
			}
			toggle = 1;
		}
	}

	this.playerMove = function(id){
		if(toggle == 1){
			var locX, locY;
			switch(id){
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
			if(this.getValue(locX, locY) == '-'){
				this.setValue('X', locX, locY);
				//this.putValue(locX, locY);
				console.log("Player 1 complete. Computer will play now!");
				alert("Player 1 complete. Computer will play now!");
				this.depth += 1;
				if(this.winner() == 1){
					alert("You have won\n");
				}
				if(this.over()){
					alert("Draw!\n");
				}
				toggle = 0;
				this.computerMove();
			}else {
				alert("\nThat's taken dear!");
				this.playerMove(id);
			}
		}
	}

	this.score = function(){
			if(this.turn == "computer" && this.winner()) return (10 - this.depth);
			else if(this.turn == "player" && this.winner)  return (this.depth - 10);
			else return 0;
	}
	this.winner = function(){
		var game = 0;

		if(this.brd[0][0] == this.brd [1][1] && this.brd [1][1] == this.brd[2][2] && this.brd[2][2] != '-') game = 1;
		if(this.brd[0][0] == this.brd [0][1] && this.brd [0][1] == this.brd[0][2] && this.brd[0][2] != '-') game = 1;
		if(this.brd[1][0] == this.brd [1][1] && this.brd [1][1] == this.brd[1][2] && this.brd[1][2] != '-') game = 1;
		if(this.brd[2][0] == this.brd [2][1] && this.brd [2][1] == this.brd[2][2] && this.brd[2][2] != '-') game = 1;
		if(this.brd[0][0] == this.brd [1][0] && this.brd [1][0] == this.brd[2][0] && this.brd[2][0] != '-') game = 1;
		if(this.brd[0][1] == this.brd [1][1] && this.brd [1][1] == this.brd[2][1] && this.brd[2][1] != '-') game = 1;
		if(this.brd[0][2] == this.brd [1][2] && this.brd [1][2] == this.brd[2][2] && this.brd[2][2] != '-') game = 1;
		if(this.brd[2][0] == this.brd [1][1] && this.brd [1][1] == this.brd[0][2] && this.brd[0][2] != '-') game = 1;

		return game;
	}
	this.over = function(){
		var flag = 1;
		for(var i = 0; i < 3; i++){
			for(var j = 0; j < 3; j++){
				if(this.getValue(i, j) == '-') flag = 0;
			}
		}

		var ifWin = this.winner();
		if(ifWin || (!ifWin && flag)) return 1;
		else return 0;
	}
	this.minimax = function(){
		if(this.over()){
			return this.score();
		}

		var moves = new Array;
		for(i = 0; i < 10; i++) moves[i] = new twoInt;
		var temp = new twoInt;

		var scores = new Array;
		var number = 0;

		for(var i = 0; i < 3; i++){
			for(var j = 0; j < 3; j++){
				if(this.getValue(i, j) == '-') {
					temp.first = i; temp.second = j;
					moves[number++] = temp;
				}
			}
		}

		if(this.turn == "player"){
			var bestValue = -32000;
			for(var i = 0; i < number ; i++){
				newGamePath = new board();
				newGamePath.boardConstructor(this, moves[i].first, moves[i].second);
				var val = newGamePath.minimax();
				if(bestValue < val){
					this.choice.first = moves[i].first;
					this.choice.second = moves[i].second;
					bestValue = val;
				}
			}
			return bestValue;
		}else{
			var bestValue = 32000;
			for(var i = 0; i < number; i++){
				newGamePath = new board(this, moves[i].first, moves[i].second);
				var val = newGamePath.minimax();
				if(bestValue > val){
					this.choice.first = moves[i].first;
					this.choice.second = moves[i].second;
					bestValue = val;
				}
			}
			return bestValue;
		}
	}	
}
var ttt = new board();
ttt.boardConstructor();

