
//===============  include section   =======================================

#include "Score.h"
#include <fstream>
#include <iostream>
#include <sstream>

//--------- c'tor  ---------------------------------------

Score::Score()
{
	bestScore = readBest();
}

//---------------   set score   ----------------------------------------

void Score::setScore(int temp)
{
	m_score = temp;
}

//-------------   read best   --------------------------------------------------

int Score::readBest()
{
	bool m = true;
	std::ifstream in;
	in.open("best.txt");
	FileReader file;
	std::string line;
	line = file.readLine(in, m);
	std::istringstream iss;
	iss.str(line);
	int best;
	iss >> best;
	in.close();
	return best;
}

//---------------------------   set best  --------------------------------

void Score::setBest(int best)
{
	bestScore = best;
	std::ofstream file;
	file.open("best.txt", std::ofstream::out | std::ofstream::trunc);
	file << std::to_string(best);
	file.close();
}

//---------  d'tor  ------------------------------------------------

Score::~Score()
{
}
