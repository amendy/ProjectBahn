#pragma once
#ifndef LINIE_H
#define LINIE_H

#include <string>
#include <list>
#include "Haltestellen.h"

using namespace std;
class Linie
{
public:
	Linie() { m_name = "U1"; };
	Linie(string liniename, string liniencolor) : m_name(liniename), m_color(liniencolor) {};
	~Linie() {};
	void setLinieName(string name) { m_name = name; };
	string getLinieName() { return m_name; };

	void setColor(string liniencolor) { m_color = liniencolor; };
	string getColor() { return m_color; };
private:
	string m_name;
	string m_color;

};




#endif