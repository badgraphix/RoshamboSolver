#include <iostream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h> 

using namespace std;
//Research: https://www.telegraph.co.uk/men/thinking-man/11051704/How-to-always-win-at-rock-paper-scissors.html

enum Sign {rock, paper, scissors, none};
vector<Sign> opponentPlays;
vector<Sign> yourPlays;

int roundNo = 1;

enum Sign getSignFromString(string input)
{
	if (input.compare("r") == 0)
	{
		return rock;
	} else if (input.compare("p") == 0) {
		return paper;
	} else if (input.compare("s") == 0) {
		return scissors;
	}
	return none;
}

//Matchup functions
enum Sign getSignWeakness(Sign sign)
{
	switch (sign)
	{
		case rock:
			return paper;
		case paper:
			return scissors;
		case scissors:
			return rock;
		case none:
			return none;
	}
	return none;
}
enum Sign getSignAdvantage(Sign sign)
{
	switch (sign)
	{
		case rock:
			return scissors;
		case paper:
			return rock;
		case scissors:
			return paper;
		case none:
			return none;
	}
	return none;
}

bool leftBeatsRight(Sign leftSign, Sign rightSign)
{
	if (getSignAdvantage(leftSign) == rightSign)
	{
		return true;
	}
	return false;
}

string getSignName(Sign signEnum)
{
	switch (signEnum)
	{
		case rock:
			return "rock";
		case paper:
			return "paper";
		case scissors:
			return "scissors";
		case none:
			return "none";
	}
	return "none";
}


string returnNotice (int noticeNo)
{
	string returnString;
	vector<string> notices = {"", "(Opponent is subconsciously copying the sign that beat them.)", "(Opponent is changing sign because they threw two in a row of the same sign.)"};

	return notices[noticeNo];
}

string returnRoundStatus(Sign playerSign, Sign opponentSign)
{
	if (leftBeatsRight(playerSign, opponentSign) == true)
	{
		return "WIN";
	}
	else if (leftBeatsRight(opponentSign, playerSign) == true)
	{
		return "LOSS";
	}
	return "DRAW";
}

bool mainLoop(Sign defaultOpponentSign)
{
	Sign expectedOpponentSign = defaultOpponentSign; //This is used to calculate the plannedPlayerSign if one isn't explicitly suggested.
	Sign plannedPlayerSign = none; //This is what actually determines the sign you should throw.
	int roundNo = yourPlays.size();	//Round no starts at 0
	int noticeNo = 0;

	if (roundNo >= 1) //Second round and up
	{
		//Opponent won't use a throw they just lost with.
		//Some players unconsciously copy the sign that just beat them
		if (leftBeatsRight(yourPlays[roundNo-1], opponentPlays[roundNo-1]) == true)
		{
			noticeNo = 1;
			expectedOpponentSign = yourPlays[roundNo-1];
		}

		if (roundNo >= 2) //Third round and up
		{	
			
			if (opponentPlays[roundNo-1] == opponentPlays[roundNo-2])
			{ 
			//Players won't repeat same throw more than twice in a row (so choose whatever the doubled sign would beat).
				noticeNo = 2;
				plannedPlayerSign = getSignAdvantage(expectedOpponentSign);
			}
		}
	}
	
	if (plannedPlayerSign == none)
	{
		plannedPlayerSign = getSignWeakness(expectedOpponentSign);
	}
	
	cout << endl << "ROUND " << roundNo+1 << ": " << endl;
	cout << "Play " << getSignName(plannedPlayerSign) << ". " << returnNotice(noticeNo) << "\n";

	
	string input;
	cout << endl << "Did they play r, p, or s? ";
	getline(cin, input);
	Sign opponentSign = getSignFromString(input);
	
	if (opponentSign == none)
	{
		return false;
	}
	else
	{
		opponentPlays.push_back(opponentSign);
		yourPlays.push_back(plannedPlayerSign);
		return true;	
	}
}

int main(int argc, char** argv) 
{
	string sex;
	string opponentName;

	cout << "Enter opponent's name: ";
	getline(cin, opponentName);
	cout << "m or f? ";
	getline(cin, sex);
	Sign defaultOpponentSign = rock;
	if (sex.compare("f") == 0)
	{
		defaultOpponentSign = scissors;
	}
	
	bool continueLoop = true;
	while (continueLoop == true)
	{
		continueLoop = mainLoop(defaultOpponentSign);
	}
	
	//Write results of game to records.
	string pathToTheOutputFile = "rps_results.txt";
	ofstream file;
	file.open (pathToTheOutputFile, ios::app);
	file << opponentName << endl; 
	for(std::size_t i=0; i<yourPlays.size(); ++i)  
	{
		file << "ROUND " << i << ": " << getSignName(yourPlays[i]) << " VS. " << getSignName(opponentPlays[i]) << "(" << returnRoundStatus(yourPlays[i], opponentPlays[i]) << ")" << endl;
	}
	file << endl;
	cout << endl << "Data saved to " << pathToTheOutputFile << "." << endl;
}

//Additional functionality not present:
//Announce what sign you're going to throw to the player, then throw it.
