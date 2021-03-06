#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace sf;

#define LENGTH 3
#define PLAYER 1
#define COMPUTER 0

#define DRAW -1
#define LOSE 0
#define WIN 1

void showPanel(char a[LENGTH][LENGTH]) {
	system("cls");
	printf(" _ _ _\n");
	for (int i = 0; i < LENGTH; ++i) {
		printf("|");
		for (int j = 0; j < LENGTH; ++j) {
			printf("%c|", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void welcome(char sym[2], bool turn) {
	system("cls");
	printf("Welcome to the ultimate tic-tac-toe game!!!\n");
	printf("Your symbol is '%c'.\n", sym[PLAYER]);
	printf("You go %s\n\n", turn ? "first :)" : "second :|");
	system("pause");
}

void initArray(char a[LENGTH][LENGTH]) {
	for (int i = 0; i < LENGTH; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			a[i][j] = '_';
		}
	}
}

void flush() {
	while ((getchar()) != '\n');
}

bool whoPlaysFirst() {
	srand(time(0));
	return rand() % 2;
}

bool isLegalMove(char a[LENGTH][LENGTH], int pos) {
	if (pos < 0 || pos > 9) {
		flush();
		return false;
	}
	return a[pos/LENGTH][pos%LENGTH] == '_';
}

int checkTicTacToe(char a[LENGTH][LENGTH], char sym[2], int player) {
	int count = 0;

	//rows
	for (int i = 0; i < LENGTH; ++i) {
		for (int j = 0; j < LENGTH; ++j)
			if (a[i][j] == sym[player])
				count++;
		if(count == LENGTH)
			return player;
		count = 0;
	}

	//columns
	for (int j = 0; j < LENGTH; ++j) {
		for (int i = 0; i < LENGTH; ++i)
			if (a[i][j] == sym[player])
				count++;
		if(count == LENGTH)
			return player;
		count = 0;
	}

	//main diagonal
	for (int i = 0; i < LENGTH; ++i)
		if (a[i][i] == sym[player])
			count++;
	if(count == LENGTH)
		return player;
	count = 0;

	//second diagonal
	for (int i = 0; i < LENGTH; ++i)
		if (a[i][LENGTH-1-i] == sym[player])
			count++;
	if(count == LENGTH)
		return player;
	count = 0;

	return -1;
}

int main() {
	char moves[LENGTH][LENGTH];
	char symbols[2] = {'X', 'O'};
	char symbol;

	bool myTurn;
	bool gameIsOn = true;
	
	int doWin = -1;
	int position;
	int row;
	int col;
	int countMoves = 0;

	initArray(moves);
	myTurn = whoPlaysFirst();

	{
		int width = 512;
		int height = 512;

		Texture t1,t2, t3;
		if (!t1.loadFromFile("images/x-medium.png"))
			return 1;
	    Sprite sprite1;
	    sprite1.setTexture(t1);

		RenderWindow window(VideoMode(width, height), "tic-tac-toe");
		window.setFramerateLimit(60);

		while (window.isOpen()) {
			Event e;
	    	while (window.pollEvent(e)) {
	    		if (e.type == Event::Closed)
	    			window.close();
	    	}

	    	window.clear(Color::White);

	    	//sprite1.setPosition(5, 5);
            window.draw(sprite1);

			window.display();
		}
	}


    ////Here start the game////
    welcome(symbols, myTurn);
	showPanel(moves);

	while (gameIsOn) {
		if (myTurn) {
			do {
				showPanel(moves);
				scanf("%d", &position);
				position--;
			} while (!isLegalMove(moves, position));
			flush();
			symbol = symbols[PLAYER];
			myTurn = false;
		} else {
			do {
				position = rand() % (LENGTH*LENGTH);
			} while (!isLegalMove(moves, position));
			symbol = symbols[COMPUTER];
			myTurn = true;
		}

		row = position / LENGTH;
		col = position % LENGTH;
		moves[row][col] = symbol;
		doWin = checkTicTacToe(moves, symbols, myTurn ? COMPUTER : PLAYER);
		countMoves++;

		if(doWin != -1 | (countMoves == LENGTH*LENGTH))
			gameIsOn = false;

		showPanel(moves);
	}

	switch (doWin) {
		case DRAW:
			printf("DRAW\n");
			break;

		case LOSE:
			printf("LOSE\n");
			break;

		case WIN:
			printf("WIN\n");	
	}
	system("pause");

	return 0;
}