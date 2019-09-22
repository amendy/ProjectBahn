#pragma once
#ifndef BAHN_H
#define BAHN_H

#include <string>
#include <list>
#include "Graph.h"
#include "Path.h"
#include "Haltestellen.h"

class Graph;

class Bahn : public Graph {
public:

	Bahn(std::string FileName, std::string id) : Graph() { *this = readData(FileName); m_id = id; };

	Bahn(std::string id) : Graph(), m_id(id) { s_numInstances++; };

	~Bahn() { };

	std::string getID() const { return m_id; };

	std::list<Path*>& getPaths() { return m_paths; };
	std::list<Haltestellen*>& getHaltestellen() { return m_Haltestellen; };

	Haltestellen& getHaltestellenById(std::string id);
	void addPath(Path* path) { m_paths.push_back(path); };
	void addHaltestelle(Haltestellen* haltestelle) { m_Haltestellen.push_back(haltestelle); };

	bool findHaltestellenById(std::string id);

	Bahn& readData(const std::string& rFilename);


	void WriteData(const std::string& rFilename, Bahn& bahn);

	std::string DatatoString();

private:

	std::string m_id;

	std::list<Path*> m_paths;
	std::list<Haltestellen*> m_Haltestellen;

	static int s_numInstances;
	static string color;
	static string linie;

};


#endif
