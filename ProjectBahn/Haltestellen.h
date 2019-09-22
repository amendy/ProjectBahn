#ifndef HALTESTELLEN_H
#define HALTESTELLEN_H

#pragma once

#include <string>
#include <list>
#include "Node.h"
#include "Linie.h"

using namespace std;

// forward-deklaration
class Linie;

class Haltestellen : public Node
{
public:

	~Haltestellen() {};
	Haltestellen() {};
	Haltestellen(std::string name, Linie* linie) : Node(name) {
		m_listLinie.push_back(linie);
	};

	void setId(std::string id) { m_id = id; };

	list<Linie*>& getlinieList() { return m_listLinie; };

	std::string getersteLinie();

	void addLinie(std::string linie) { m_listLinie.push_back(new Linie(linie, to_string(rand() % 1000000))); };

	void addLinie(Linie* linie) { m_listLinie.push_back(linie); };

	std::string toString() const;

private:
	list<Linie*> m_listLinie;

};
#endif // !HALTESTELLEN_H




