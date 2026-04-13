#include <iostream>
#include <cstdlib>

using namespace std;

// structures and enums;
enum enGameChoice  {Stock=1 , Paper=2, Scisser=3 };
enum enWinner{ Player=1 , Computer =2 , Draw=3};
struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName="";
};
struct stGameResults
{
	short GameRound = 0;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName="";
};

//Player
short RoundNumber() {
	short Num = 0;
	do
	{
		cout << "Please Enter Number Rounds: ";
		cin >> Num;
	} while (Num<1 || Num>10);
	return Num;
}
enGameChoice ReadPlayChoice() {
	short Number;
	do
	{
		cout << "Please Choice Want to Play Stock(1) Paper(2) Scisser(3): ";
		cin >> Number;
	} while (Number <1 || Number> 3);
	return (enGameChoice)Number;
}

//Computer
int RandomNumber(int From , int To) {
	return rand() % (To - From + 1) + From;
}
enGameChoice GetComputerChoice() {
	return (enGameChoice)RandomNumber(1,3);
}

//Who Win 
enWinner WhoWinnerTheRound(stRoundInfo RoundInfo) {

	if (RoundInfo.ComputerChoice == RoundInfo.PlayerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice) {
	case enGameChoice::Stock:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scisser)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scisser :
		if (RoundInfo.ComputerChoice == enGameChoice::Stock)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player;
}
enWinner WhoWinnerTheGame(short PlayWinnerTimes, short ComputerWinnerTimes) {
	if (PlayWinnerTimes > ComputerWinnerTimes)
		return enWinner::Player;
	else if (ComputerWinnerTimes > PlayWinnerTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

//Winner Name 
string WinnerName(enWinner Winner) {
	string arrWinnerName[3] = { "Player" , "Computer" , "Draw" };
	return arrWinnerName[Winner - 1];
}
string choiceName(enGameChoice Choice) {
	string arrChoiceName[3] = {"Stock" , "Paper" , "Scisser"};
	return arrChoiceName[Choice - 1];
}

//Other Tools
string Tabs(short NumberTabs) {
	string t = "";
	for (short i = 1; i < NumberTabs; i++)
	{
		t = t + "\t";
	
	}
	return t;
}
void SetWinnerScreenColor(enWinner Winner) {
	switch (Winner) {
	case enWinner::Player:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default :
		system("color 6F");
		break;
	}
}
void ReSetColorScreen() {
	system("cls");
	system("color 0F");
}
 
//The Pints
void PrintRoundInfo(stRoundInfo RoundInfo) {
	cout << "\n____________________Round[" << RoundInfo.RoundNumber<< "]____________________\n";
	cout << "Player Choice: " << choiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << choiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Winner: " << RoundInfo.WinnerName << endl;
	cout << "___________________________________________\n";
}
void ShowGameOverScreen() {
	cout << endl<< Tabs(2) << "________________________________________________________________________\n";
	cout << Tabs(2) << "                       + + + G a m e  O v e r + + +                     \n";
	cout << Tabs(2) << "_________________________________________________________________________\n";
}
void ShowFinalResults(stGameResults GameResults) {
	cout << endl << Tabs(3) << "___________________________[GAME RESULTS]___________________________\n";
	cout << Tabs(3) << "Game Rounds        :" << GameResults.GameRound << endl;
	cout << Tabs(3) << "Player won times   :" << GameResults.PlayerWonTimes << endl;
	cout << Tabs(3) << "Computer won times :" << GameResults.ComputerWonTimes << endl;
	cout << Tabs(3) << "Draw times         :" << GameResults.DrawTimes << endl;
	cout << Tabs(3) << "Final Winner       :" << GameResults.WinnerName << endl;
	cout << Tabs(3) << "________________________________________________________________________\n\n";
	SetWinnerScreenColor(GameResults.GameWinner);
};

// Fill Game Results
stGameResults FillGameResults(short GameRounds, short PlayWinTims, short ComputerWinTimes, short Draw) {
	
	stGameResults GameResults;

	GameResults.GameRound = GameRounds;
	GameResults.PlayerWonTimes = PlayWinTims;
	GameResults.ComputerWonTimes = ComputerWinTimes;
	GameResults.DrawTimes = Draw;
	GameResults.GameWinner = WhoWinnerTheGame(PlayWinTims, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

//Play Game
stGameResults PlayGame(int RoundNumber) {

	stRoundInfo RoundInfo;
	short PlayWinTims = 0, ComputerWinTimes = 0, Draw = 0;

	for (short GameRound = 1; GameRound <= RoundNumber; GameRound++)
	{
		cout << "Round[" << GameRound << "]  Begins: \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinnerTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
		PrintRoundInfo(RoundInfo);
		SetWinnerScreenColor(RoundInfo.Winner);

		if (enWinner::Computer == RoundInfo.Winner)
			ComputerWinTimes++;
		else if (enWinner::Player == RoundInfo.Winner)
			PlayWinTims++;
		else
			Draw++;
	}
	return FillGameResults(RoundNumber, PlayWinTims, ComputerWinTimes, Draw);
}

// start Game
void StartGame() {
	char PlayAgain = 'Y';
	do
	{
		ReSetColorScreen();
		stGameResults GameResults = PlayGame(RoundNumber());
		ShowGameOverScreen();
		ShowFinalResults(GameResults);

		cout << "Do you want play again Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}