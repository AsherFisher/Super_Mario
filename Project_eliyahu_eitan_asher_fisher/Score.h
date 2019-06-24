#pragma once

//===============   include section   =============================

#include"FileReader.h"

//==================    class score   =============================

class Score
{
	int bestScore; // best score ever achived in this game (also in diffrent running) 
	int m_score;

public:

	// c'tor
	Score();
	void setScore(int temp);
	// read from file "best.txt" the highest score so far
	int readBest();
	// get the score of the game
	int getScore() { return m_score; }
	// get the score
	int getBest() { return bestScore; }
	// set a new value to be the best score
	void setBest(int best);
	// check if giving value grater than current high score
	bool checkBest(int toCheck) { return toCheck > bestScore; }
	// d'tor
	~Score();
};

