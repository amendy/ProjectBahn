#pragma once
#include "GUI.h"
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <iomanip>
#include "Exception.h"


//-------------------------------------------------------------------------------------------------------------
bool GUI::ReadDatafromfile()
{
	std::string puffer;
	cout << "Bitte geben Sie den Name von file ein :" << endl;
	getline(cin, puffer);
	try {
		m_bahn.readData(puffer);
		return true;
	}
	catch (exception e)
	{
		return false;
	}
}



//-------------------------------------------------------------------------------------------------------------

int GUI::startMenu()
{
	//--------test area start-----------------

	//Node* choice = inputNode("Please select a Node:");

	//--------test area end-------------------

	string question = "------------------------------------------------------------------------\n"
		"Bitte waehlen Sie:\n"
		"1. Insert Data\n"
		"2. New Haltestelle\n"
		"3. Delete Haltestelle\n"
		"4. Edit Haltestelle\n"
		"5. Add Path\n"
		"6. View The Netz-Daten\n"
		"7. Find shortest Destination\n"
		"8. Find fastes Destination\n"
		"9. Save new Data\n"
		"10. Ausgabe aller Linie als jpg\n"
		"11. Beenden\n";

	int eingabe = inputLimitedNumber(question, 1, 11);
	return eingabe;
}

//-------------------------------------------------------------------------------------------------------------

bool GUI::NewHaltestelle()
{
	try {
		Haltestellen* halt;
		std::string puffer;
		cout << "Bitte geben Sie den Name von Haltstelle ein :" << endl;
		getline(cin, puffer);
		std::istringstream iss(puffer);
		std::vector<std::string> results(std::istream_iterator<std::string>{iss},
			std::istream_iterator<std::string>());
		puffer = "";
		for (auto temp : results)
		{
			puffer += temp;
		}
		string question = "------------------------------------------------------------------------\n"
			"Bitte wählen Sie die Linie von Haltstelle  :\n"
			"1. U1\n"
			"2. U2\n"
			"3. U3\n"
			"4. U4\n"
			"5. U5\n"
			"6. U6\n"
			"7. U7\n"
			"8. U8\n"
			"9. U9\n";
		int eingabe = inputLimitedNumber(question, 1, 9);
		stringstream ss;
		ss << eingabe;
		string str = ss.str();
		halt = new Haltestellen(puffer, new Linie("U" + str, to_string(rand() % 1000000)));
		m_bahn.addHaltestelle(halt);
		return true;
	}
	catch (Exception e)
	{
		cout << e.getMessage() << endl;
		return false;
	}
}

//-------------------------------------------------------------------------------------------------------------


bool GUI::DeleteHaltestelle() {
	Haltestellen* halt;
	std::string puffer;
	cout << "Bitte geben Sie den Name von Haltstelle ein :" << endl;
	getline(cin, puffer);
	if (!m_bahn.findHaltestellenById(puffer))
	{
		Exception::ExceptionType type = Exception::ExceptionType::HALTESTELLEN_NOT_FOUND;
		std::string str = std::string(Exception::ErrorName[type]);
		throw new Exception(str);
		return false;
	}
	else
	{
		halt = m_bahn.findNodeById(puffer);
		m_bahn.remove(*halt);
		return true;
	}
}

//-------------------------------------------------------------------------------------------------------------

bool GUI::EditHaltestelle() {
	Haltestellen* halt;
	std::string puffer;
	cout << "Bitte geben Sie den Name von Haltstelle ein :" << endl;
	getline(cin, puffer);
	if (!m_bahn.findHaltestellenByID(puffer))
	{
		Exception::ExceptionType type = Exception::ExceptionType::HALTESTELLEN_NOT_FOUND;
		std::string str = std::string(Exception::ErrorName[type]);
		throw new Exception(str);
		return false;
	}
	else
	{
		halt = m_bahn.findNodeByID(puffer);
		std::cout << halt->toString() << std::endl;
		bool finisched = false;
		while (!finisched)
		{
			string question = "------------------------------------------------------------------------\n"
				"Bitte wählen Sie:\n"
				"1. Edit Haltestelle Name\n"
				"2. Edit Haltestelle Linie\n"
				"3. End Editing";
			int eingabe = inputLimitedNumber(question, 1, 3);
			if (eingabe == 1)
			{
				cout << "Bitte geben Sie den Nueue Name von Haltstelle ein :" << endl;
				getline(cin, puffer);
				halt->setID(puffer);
			}
			if (eingabe == 2)
			{
				cout << "Bitte geben Sie den Nueue Name von Linie ein :" << endl;
				getline(cin, puffer);
				halt->setID(puffer);
			}
			if (eingabe == 3)
				finisched = true;
		}

		return true;
	}


}

//-------------------------------------------------------------------------------------------------------------

bool  GUI::AddNewPath()
{
	std::string puffer;
	std::string puffer2;
	cout << "Bitte geben Sie den Name von Haltstelle 1 ein :" << endl;
	getline(cin, puffer);
	cout << "Bitte geben Sie den Name von Haltstelle 2 ein :" << endl;
	getline(cin, puffer2);
	string question = "------------------------------------------------------------------------\n"
		"Bitte wählen Sie die Linie von Haltstelle  :\n"
		"1. U1\n"
		"2. U2\n"
		"3. U3\n"
		"4. U4\n"
		"5. U5\n"
		"6. U6\n"
		"7. U7\n"
		"8. U8\n"
		"9. U9\n";
	int eingabe = inputLimitedNumber(question, 1, 9);
	stringstream ss;
	ss << eingabe;
	string str = ss.str();
	char* EndPtr;
	try
	{
		Haltestellen& halt2 = m_bahn.addNode(new Haltestellen(puffer2, new Linie(str, to_string(rand() % 1000000))));
		Haltestellen& halt = m_bahn.addNode(new Haltestellen(puffer, new Linie(str, to_string(rand() % 1000000))));
	}
	catch (...)
	{
	}
	if (!m_bahn.findHaltestellenByID((*m_bahn.findNodeByID(puffer)).getID()))
	{
		m_bahn.addHaltestelle(&*m_bahn.findNodeByID(puffer));
		if (!m_bahn.findHaltestellenByID((*m_bahn.findNodeByID(puffer2)).getID()))
			m_bahn.addHaltestelle(&*m_bahn.findNodeByID(puffer2));
	}
	else
	{
		if (!m_bahn.findHaltestellenByID((*m_bahn.findNodeByID(puffer2)).getID()))
			m_bahn.addHaltestelle(&*m_bahn.findNodeByID(puffer2));
	}
	cout << "Bitte geben Sie Entfernung-Km :" << endl;
	std::string puffer3;
	getline(cin, puffer3);
	if (!is_number(puffer3)) {
		throw new Exception("field Input");
	}
	char* chr = const_cast<char*>(puffer3.c_str());
	cout << "Bitte geben Sie Zeitbedarf :" << endl;
	std::string puffer4;
	getline(cin, puffer4);
	if (!is_number(puffer4)) {
		throw new Exception("field Input");
	}
	char* chr2 = const_cast<char*>(puffer4.c_str());
	double d = strtod(chr2, &EndPtr);
	Path& path = m_bahn.addEdge(new Path(*m_bahn.findNodeByID(puffer), *m_bahn.findNodeByID(puffer2), strtod(chr, &EndPtr), strtod(chr2, &EndPtr)));
	Path& path1 = m_bahn.addEdge(new Path(*m_bahn.findNodeByID(puffer2), *m_bahn.findNodeByID(puffer), strtod(chr, &EndPtr), strtod(chr2, &EndPtr)));
	m_bahn.addPath(&path);
	m_bahn.addPath(&path1);
	return true;
}

//-------------------------------------------------------------------------------------------------------------

bool GUI::is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
//-------------------------------------------------------------------------------------------------------------

bool  GUI::ViewAllData()
{
	cout << m_bahn.DatatoString() << endl;
	return true;
}

//-------------------------------------------------------------------------------------------------------------

int GUI::inputNumber(string question)
{
	int n;
	bool fail = true;

	while (fail)
	{
		cout << question << endl;
		cout << "Eingabe: ";
		cin >> n;

		if (!cin) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nFehlerhafte Eingabe! Nur Zahlen sind zulaessing...\n" << endl;

		}
		else {
			fail = false;
		}
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return n;
}

//-------------------------------------------------------------------------------------------------------------
int GUI::inputLimitedNumber(string question, int min, int max)
{
	int n;
	bool fail = true;

	while (fail)
	{
		cout << question << endl;
		cout << "Eingabe: ";
		cin >> n;

		if (!cin) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nFehlerhafte Eingabe! Nur Zahlen sind zulaessing...\n" << endl;

		}
		else if ((n < min) || (n > max)) {

			cout << "\nFehlerhafte Eingabe! Nur zahlen zwischen " << min << " und " << max << " sind zulaessig\n" << endl;
		}

		{
			fail = false;
		}
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return n;
}

//-------------------------------------------------------------------------------------------------------------
string GUI::inputString(string question)
{
	string input;
	bool fail = true;

	while (fail)
	{
		cout << question << endl;
		getline(cin, input);

		if (!cin) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Fehlerhafte Eingabe!" << endl;
		}
		else {
			fail = false;
		}
	}
	return input;
}

//-------------------------------------------------------------------------------------------------------------
bool GUI::FindShortestDestination() {
	std::string puffer;
	cout << "Bitte geben Sie den Name von Haltstelle 1 ein :" << endl;
	getline(cin, puffer);
	if (!m_bahn.findHaltestellenByID(puffer))
	{
		Exception::ExceptionType type = Exception::ExceptionType::HALTESTELLEN_NOT_FOUND;
		std::string str = std::string(Exception::ErrorName[type]);
		throw new Exception(str);
		return false;
	}
	std::string puffer2;
	cout << "Bitte geben Sie den Name von Haltstelle 2 ein :" << endl;
	getline(cin, puffer2);
	if (!m_bahn.findHaltestellenByID(puffer2))
	{
		Exception::ExceptionType type = Exception::ExceptionType::HALTESTELLEN_NOT_FOUND;
		std::string str = std::string(Exception::ErrorName[type]);
		throw new Exception(str);
		return false;
	}

	std::deque<Edge*>*test_3 = new std::deque<Edge*>();
	if (m_bahn.findSpeedPathDijkstra(*test_3, *m_bahn.findNodeByID(puffer), *m_bahn.findNodeByID(puffer2)))
	{
		int Umsteigen = 0;
		for (std::deque<Edge*>::const_iterator it = test_3->begin(); it != test_3->end(); ++it)
		{
			bool change = true;
			Linie L;
			for (Linie* ll : (dynamic_cast<Path*>(*it))->getrSrc()->getlinieList())
			{
				L = *ll;
				break;
			}
			for (auto ltemp : ((dynamic_cast<Path*>(*it))->getrDst()->getlinieList()))
			{
				if (ltemp->getLinieName().compare(L.getLinieName()) == 0)
				{
					L = *ltemp;
					change = false;
					break;
				}
			}

			if (change)
			{
				for (Linie* ll : (dynamic_cast<Path*>(*it))->getrDst()->getlinieList())
				{
					L = *ll;
					break;

				}

				Umsteigen++;
			}

			std::cout << (*it)->toString() << " " << L.getLinieName() << std::endl;
		}
		std::cout << "Sie mussen " << Umsteigen << " mal umsteigen" << std::endl;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------------------
bool GUI::FindfastesDestination() {
	std::string puffer;
	cout << "Bitte geben Sie den Name von Haltstelle 1 ein :" << endl;
	getline(cin, puffer);
	if (!m_bahn.findHaltestellenByID(puffer))
	{
		Exception::ExceptionType type = Exception::ExceptionType::HALTESTELLEN_NOT_FOUND;
		std::string str = std::string(Exception::ErrorName[type]);
		throw new Exception(str);
		return false;
	}
	std::string puffer2;
	cout << "Bitte geben Sie den Name von Haltstelle 2 ein :" << endl;
	getline(cin, puffer2);
	if (!m_bahn.findHaltestellenByID(puffer2))
	{
		Exception::ExceptionType type = Exception::ExceptionType::HALTESTELLEN_NOT_FOUND;
		std::string str = std::string(Exception::ErrorName[type]);
		throw new Exception(str);
		return false;
	}
	cout << "--------------------------------------------------------------------------------------------" << endl;
	std::deque<Edge*>*test_3 = new std::deque<Edge*>();
	if (m_bahn.findShortestPathDijkstra(*test_3, *m_bahn.findNodeByID(puffer), *m_bahn.findNodeByID(puffer2)))
	{
		int Umsteigen = 0;
		for (std::deque<Edge*>::const_iterator it = test_3->begin(); it != test_3->end(); ++it)
		{
			bool change = true;
			Linie L;
			for (Linie* ll : (dynamic_cast<Path*>(*it))->getrSrc()->getlinieList())
			{
				L = *ll;
				break;
			}

			for (auto ltemp : ((dynamic_cast<Path*>(*it))->getrDst()->getlinieList()))
			{
				if (ltemp->getLinieName().compare(L.getLinieName()) == 0)
				{
					L = *ltemp;
					change = false;
					break;
				}
			}
			if (change)
			{
				for (Linie* ll : (dynamic_cast<Path*>(*it))->getrSrc()->getlinieList())
				{
					L = *ll;
					break;
				}
				Umsteigen++;
			}

			std::cout << (*it)->toString() << " " << L.getLinieName() << std::endl;
		}
		std::cout << "Sie mussen " << Umsteigen << " mal umsteigen" << std::endl;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------------------

bool GUI::SaveData() {
	std::string puffer;
	cout << "Bitte geben Sie den File Name:" << endl;
	getline(cin, puffer);
	m_bahn.WriteData(puffer + ".txt", m_bahn);
	return true;
}

//-------------------------------------------------------------------------------------------------------------

voID executeBatch(char* BatchFile) {
	system(BatchFile);
}


//-------------------------------------------------------------------------------------------------------------

bool GUI::AusgabeAlsjpg() {
	try {
		m_bahn.saveAsDot("graph.dot");
		executeBatch("make.bat");
		system("out.png");
		return true;
	}
	catch (std::exception e)
	{
		cout << e.what() << endl;
		return false;
	}
}

//-------------------------------------------------------------------------------------------------------------
