#pragma once
#include "Graph.h"
#include <limits>
#include <iostream>
#include <list>
#include <iterator>
#include <iomanip> 
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include "Bahn.h"



int Bahn::s_numInstances = 0;
string color = "000000";
string linie = "U1";

//---------------------------------------------------------------------------------------------------------------------


std::string Bahn::DatatoString()
{
	std::string result = m_id + "\n";
	for (std::list<Path*>::iterator it = m_paths.begin(); it != m_paths.end(); ++(++it))
	{
		Path* p = *it;
		Haltestellen* halt = p->getrSrc();
		Haltestellen* halt2 = p->getrDst();
		std::string l = (getHaltestellenById(halt->getID())).getersteLinie();
		std::string str = l + " " + halt->getID() + " " + "->" + " " + halt2->getID() + ": ";
		double d = p->getEntfernung();
		stringstream tmp;
		tmp << setprecision(2) << fixed << d;
		str += tmp.str();
		str += +" ";
		d = p->getZeitbedarf();
		stringstream tmp2;
		tmp2 << setprecision(0) << fixed << d;
		str += tmp2.str();
		result += str + "\n";
	}
	return result;
}

//---------------------------------------------------------------------------------------------------------------------

Haltestellen& Bahn::getHaltestellenById(std::string id)
{
	for (std::list<Haltestellen*>::iterator it = m_Haltestellen.begin(); it != m_Haltestellen.end(); it++)
	{
		Haltestellen* tt = *it;
		string str = tt->getID();
		if (!str.compare(id))
		{
			return *tt;
		}
	}
	return Haltestellen();

}

//---------------------------------------------------------------------------------------------------------------------

bool Bahn::findHaltestellenById(std::string id)
{
	for (std::list<Haltestellen*>::iterator it = m_Haltestellen.begin(); it != m_Haltestellen.end(); it++)
	{
		Haltestellen* tt = *it;
		string str = tt->getID();
		if (!str.compare(id))
		{
			return true;
		}
	}
	return false;

}

//---------------------------------------------------------------------------------------------------------------------

void Linetolist(std::vector<std::string>& results1, std::string line)
{
	std::istringstream iss(line);
	std::vector<std::string> results(std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>());
	if (results[2].compare("->") != 0)
	{
		results[1] += " " + results[2];
		results[2] = "->";
		results[3] = results[4];
		results[4] = results[5];
		results[5] = results[6];
		if (!isdigit(results[4][0]))
		{
			results[3] += " " + results[4];
			results[4] = results[5];
			results[5] = results[7];
		}
	}
	else
		if (!isdigit(results[4][0]))
		{
			results[3] += " " + results[4];
			results[4] = results[5];
			results[5] = results[6];
		}
	results[3] = results[3].substr(0, results[3].length() - 1);
	std::cout << results[0] << " " << results[1] << " " << results[2] << " " << results[3] << " " << results[4] << " " << results[5] << std::endl;
	for (int i = 0; i < results[4].length(); i++)
	{
		if (results[4][i] == ',')
			results[4][i] = '.';
	}
	results1 = results;
}


//--------------------------------------------------------------------------------------------------------------------

string randomColor()
{
	return to_string(rand() % 1700 * 526 + 100000);

}


//---------------------------------------------------------------------------------------------------------------------

void listToData(std::vector<std::string>& results, Bahn& bahn)
{
	char* EndPtr;
	try
	{
		if (results[0].compare(linie) != 0)
		{
			color = randomColor();
			linie = results[0];
		}
		Haltestellen& halt2 = bahn.addNode(new Haltestellen(results[3], new Linie(results[0], color)));
		Haltestellen& halt = bahn.addNode(new Haltestellen(results[1], new Linie(results[0], color)));

	}
	catch (...)
	{
	}
	if (!bahn.findHaltestellenById((*bahn.findNodeById(results[1])).getID()))
	{
		bahn.addHaltestelle(&*bahn.findNodeById(results[1]));
		if (!bahn.findHaltestellenById((*bahn.findNodeById(results[3])).getID()))
			bahn.addHaltestelle(&*bahn.findNodeById(results[3]));
	}
	else
	{
		if (!bahn.findHaltestellenById((*bahn.findNodeById(results[3])).getID()))
			bahn.addHaltestelle(&*bahn.findNodeById(results[3]));
	}
	char* chr = const_cast<char*>(results[4].c_str());
	char* chr2 = const_cast<char*>(results[5].c_str());
	double d = strtod(chr2, &EndPtr);
	Path& path = bahn.addEdge(new Path(*bahn.findNodeById(results[1]), *bahn.findNodeById(results[3]), strtod(chr, &EndPtr), strtod(chr2, &EndPtr)));
	Path& path1 = bahn.addEdge(new Path(*bahn.findNodeById(results[3]), *bahn.findNodeById(results[1]), strtod(chr, &EndPtr), strtod(chr2, &EndPtr)));
	bahn.addPath(&path);
	bahn.addPath(&path1);


}

//---------------------------------------------------------------------------------------------------------------------
Bahn& Bahn::readData(const std::string& rFilename)
{
	Bahn* bahn = new Bahn("Deutsche Bahn");
	std::string line;
	std::ifstream myfile(rFilename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::vector<std::string> results;
			Linetolist(results, line);
			try {
				listToData(results, *bahn);
			}
			catch (std::string e)
			{
				std::cout << e << std::endl;
			}
		}
		myfile.close();
		return *bahn;
	}

	else std::cout << "Unable to open file";
	return *bahn;
}

//---------------------------------------------------------------------------------------------------------------------

void Bahn::WriteData(const std::string& rFilename, Bahn& bahn)
{
	std::ofstream  myfile(rFilename);
	if (myfile.is_open())
	{
		std::list<Path*> paths = bahn.getPaths();
		for (std::list<Path*>::iterator it = paths.begin(); it != paths.end(); ++(++it))
		{
			Path* p = *it;
			Haltestellen* halt = p->getrSrc();
			Haltestellen* halt2 = p->getrDst();
			std::string l = (bahn.getHaltestellenById(halt->getID())).getersteLinie();
			std::string str = l + " " + halt->getID() + " " + "->" + " " + halt2->getID() + ": ";
			double d = p->getEntfernung();
			stringstream tmp;
			tmp << setprecision(2) << fixed << d;
			str += tmp.str();
			str += +" ";
			d = p->getZeitbedarf();
			stringstream tmp2;
			tmp2 << setprecision(0) << fixed << d;
			str += tmp2.str();
			myfile << str << "\n";

		}
		myfile.close();
	}
	else cout << "Unable to open file";
}


//---------------------------------------------------------------------------------------------------------------------

