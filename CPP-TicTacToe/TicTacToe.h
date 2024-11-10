#include <iostream>
#include "Game.h"

#pragma once
using namespace std;

class TicTacToe : public Game
{

private: 

	char m_board[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	//starts as player 2 because we switch it before the first turn
	int m_turn = 1;
	int turnsTaken = 0;

public:
	// does cpp have derived properties or is this what you would have to do instead
	bool IsGameOver() const { return (IsWin() || IsTie()); }
	bool IsTie() const 
	{ 
		if (turnsTaken == 9)
		{
			cout << "\nTie Game!\n\n";
			return true;
		}
		return false;
	
	}
	bool IsWin() const
	{
		//looks gross but I feel like it's the most concise way to do it if you're just gonna check each scenario
		if (
			CheckSpaces(0, 1, 2) ||
			CheckSpaces(3, 4, 5) ||
			CheckSpaces(6, 7, 8) ||
			CheckSpaces(0, 3, 6) ||
			CheckSpaces(1, 4, 7) ||
			CheckSpaces(2, 5, 8) ||
			CheckSpaces(0, 4, 8) ||
			CheckSpaces(6, 4, 2))
		{
			cout << "Player " << m_turn + 1 << " Wins!\n\n";
			return true;
		}
		return false;
	}

	void TakeTurn()
	{
		//flipping the turn before it's taken just so that we don't have switch it when somebody wins
		//not sure if we've used ternary operators in this class yet
		m_turn = m_turn == 0 ? 1 : 0;
		PlaceCharacter();
		turnsTaken++;
	}

	void Display() const
	{
		//clears the screen
		system("cls");
		//shows the board
		cout << "\n" <<
			m_board[0] << "|" << m_board[1] << "|" << m_board[2] << "\n"
			<< "------\n" <<
			m_board[3] << "|" << m_board[4] << "|" << m_board[5] << "\n"
			<< "------\n" <<
			m_board[6] << "|" << m_board[7] << "|" << m_board[8] << "\n\n";
	}

	//places a character on the board
	void PlaceCharacter()
	{
		//stuff that's based on who's turn it is
		cout << "Player " << m_turn + 1 << "'s turn!\n\n";
		char playerChar = m_turn == 0 ? 'X' : 'O';
		//repeats until the chosen space is valid
		int spaceToPlace = 0;
		while (true)
		{
			cout << "Pick a Space to Place an " << playerChar << ": ";
			cin >> spaceToPlace;
			if (spaceToPlace < 1 || spaceToPlace > 9) cout << "Out of Bounds!\n";
			else if (m_board[spaceToPlace - 1] != ToChar(spaceToPlace)) cout << "Space Taken!\n";
			else break;	
		}
		m_board[spaceToPlace - 1] = playerChar;
		
	}

	// had to look this up
	// really wanted to just store the ints as chars in the char array and be able to compare them to input ints
	char ToChar(int i) const
	{
		return (char)('0' + i);
	}

	//checks if all given spaces are equal
	bool CheckSpaces(int x, int y, int z) const
	{
		return m_board[x] == m_board[y] && m_board[y] == m_board[z];
	}

	
};

