#include<iostream>
#include <cstdlib>
#include <ctime>
#include <vector>	
#include <algorithm>
#include <string>


bool gamestate = 1;
int n_mines = 10;
int n_flagged = 0;
int n_opened = 0;

template<typename T>

void PrintGrid(T arr[10][10])
{
	std::cout << "   ";
	for (int i = 0; i < 10; i++)
	{
		std::cout << char(97 + i) << " ";
	}

	std::cout << std::endl;
	std::cout << "  ";

	for (int i = 0; i < 10; i++)
	{
		std::cout << "--";
	}

	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
	{

		std::cout << i << "|" << " ";

		for (int j = 0; j < 10; j++)
		{
			std::cout << arr[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void setMines(int(&mines)[10][10]) {
	// Seed the random number generator
	srand(time(nullptr));

	std::vector<int> numbers;

	// Generate 10 different random numbers between 0 and 99
	for (int i = 0; i < 10; ++i) {
		int randomNumber;
		do {
			randomNumber = rand() % 100; // Generate a random number between 0 and 99
		} while (std::find(numbers.begin(), numbers.end(), randomNumber) != numbers.end());
		numbers.push_back(randomNumber);
	}

	for (int num : numbers)
	{
		int row = num / 10;
		int col = num % 10;

		mines[row][col] = 1;
	}

}

void clearConsole() {
	#ifdef _WIN32
	std::system("cls"); // For Windows
	#else
	// Assume Unix-based system
	std::system("clear"); // For Linux/Unix/macOS
	#endif
}

bool isValidCoordinate(int& i, int& j)
{
	if (i < 0 || i > 9 || j < 0 || j > 9)
	{
		return false;
	}
	return true;
}

bool isMine(int(&mines)[10][10], int& i, int& j)
{
	return mines[i][j];
}

int findNumberOfMines(int(&mines)[10][10], int& row, int& col)
{

	int number_of_mines = 0;

	int start_i = row - 1;
	int start_j = col - 1;

	for (int i = start_i; i < start_i + 3; i++)
	{
		for (int j = start_j; j < start_j + 3; j++)
		{
			if (!isValidCoordinate(i, j) || (i == row && j == col)) continue;
			if (isMine(mines, i, j)) number_of_mines++;
		}
	}

	return number_of_mines;
}

void OpenTile(char(&board)[10][10], int(&mines)[10][10], int row, int col)
{
	int number_of_mines = findNumberOfMines(mines, row, col);
	char char_number_of_mines = char(int('0') + number_of_mines);
}

void Expand(char(&board)[10][10], int(&mines)[10][10], int row, int col)
{
	if (board[row][col] != '+') return;
	if (isMine(mines, row, col) || !isValidCoordinate(row, col)) return;
	char char_number_of_mines = char(int('0') + findNumberOfMines(mines, row, col));
	board[row][col] = char_number_of_mines;
	n_opened++;
	if (board[row][col] == '0')
	{
		
		Expand(board, mines, row - 1, col - 1);
		Expand(board, mines, row - 1, col);
		Expand(board, mines, row - 1, col + 1);
		Expand(board, mines, row, col - 1);
		Expand(board, mines, row, col + 1);
		Expand(board, mines, row + 1, col-1);
		Expand(board, mines, row + 1, col);
		Expand(board, mines, row + 1, col+1);

	}
}

bool getAndProcessInput(char(&board)[10][10], int(&mines)[10][10]) {
	std::string line;
	std::cout << "Enter your input: ";
	std::getline(std::cin, line);

	if (line.size() < 3)
	{
		std::cout << "Invalid Input. Please Retry..." << std::endl;
		return 0;
	}

	char what = line[0];
	char row = line[1];
	char col = line[2];


	if (!(what == 'o' || what == 'f')) {
		std::cout << "Invalid Input. Please Retry..." << std::endl;
		return 0;
	}

	if (!(row >= '0' && row <= '9')) {
		std::cout << "Invalid Input. Please Retry..." << std::endl;
		return 0;
	}

	if (!(col >= 'a' && col <= 'j')) {
		std::cout << "Invalid Input. Please Retry..." << std::endl;
		return 0;
	}

	int int_row = int(row - '0');
	int int_col = int(col - 'a');

	if (what == 'o')
	{
		if (board[int_row][int_col] != '+')
		{
			std::cout << "Invalid Input. Point already opened. Please Retry..." << std::endl;
			return 0;
		}

		char number_of_mines = char(int('0') + findNumberOfMines(mines, int_row, int_col));

		Expand(board, mines, int_row, int_col);
		if (isMine(mines, int_row, int_col))
		{
			gamestate = 0;
			return 1;
		}

	}

	if (what == 'f')
	{
		if (board[int_row][int_col] == 'f')
		{
			board[int_row][int_col] = '+';
			n_mines++;
			n_flagged--;
		}
		else if (board[int_row][int_col] == '+')
		{
			board[int_row][int_col] = 'f';
			n_mines--;
			n_flagged++;
		}
		else
		{
			std::cout << "Invalid Input. Point already opened. Please Retry..." << std::endl;
			return 0;
		}
	}

	return 1;

}

int main()
{
	int mines[10][10];
	char gameBoard[10][10];


	memset(mines, 0, sizeof(mines));
	setMines(mines);
	memset(gameBoard, '+', sizeof(gameBoard));


	// Welcome Screen and Rules

	const char* menuScreen = R"(
Welcome to MINESWEEPER by cos1point57.
There's a 10x10 board with 10 mines hidden.
How to play? 
1) To open a cell input 'o<row><col>'. Example input -> o2a
2) To flag a cell as a potential bomb input 'f<row><col>'. Example input -> f4b
	)";


	// Gameloop
	while (gamestate)
	{
		std::cout << menuScreen << std::endl << std::endl;
		std::cout << "Opened: " << n_opened << "   Flagged: " << n_flagged << "   Mines Left: " << n_mines << "\n\n";

		PrintGrid(gameBoard);
		while (!getAndProcessInput(gameBoard, mines))
		{
		}

		if (!gamestate) {
			std::cout << "Popped a mine. Game Over :(" << std::endl;
			PrintGrid(mines);
			break;
		}

		if (n_opened == 90)
		{
			std::cout << "Congratulations! You are world MineSweeper Champion :)" << std::endl;
			break;
		}

		clearConsole();
	}

	return 0;
}