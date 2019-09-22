#pragma once
#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "Graph.h"
#include "Haltestellen.h"
#include "Path.h"
#include "Bahn.h"

using namespace std;

class Path;
class Graph;
class Bahn;


class GUI
{
public:

	GUI(Bahn& bahn) :m_bahn(bahn) {};

	int startMenu();

	bool NewHaltestelle();

	bool DeleteHaltestelle();

	bool ReadDatafromfile();

	bool EditHaltestelle();

	bool AddNewPath();

	bool ViewAllData();

	bool FindShortestDestination();

	bool FindfastesDestination();

	bool SaveData();

	bool AusgabeAlsjpg();

private:

	Bahn& m_bahn;
	int inputNumber(string question);
	int inputLimitedNumber(string question, int min, int max);
	string inputString(string question);
	bool is_number(const std::string& s);

};



#endif