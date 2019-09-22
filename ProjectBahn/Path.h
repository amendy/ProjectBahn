#pragma once
#ifndef PATH_H
#define PATH_H

#include "Linie.h"
#include <string>
#include <list>
#include "Edge.h"

using namespace std;
class Path : public  Edge
{
public:

	//Path();
	Path(Node&rSrc, Node& rDst, double entfernung, double zeitbedarf) : Edge(rSrc, rDst) {
		m_entfernung = entfernung;  m_zeitbedarf = zeitbedarf;
	};
	~Path() {};

	Haltestellen* getrSrc() { return (dynamic_cast<Haltestellen*>(&m_rSrc)); };
	Haltestellen* getrDst() { return (dynamic_cast<Haltestellen*>(&m_rDst)); };
	//virtual double getWeight(int zeitbedarf) { return *(next(m_zeitbedarf.begin(), zeitbedarf)); }
	virtual double getWeight() { return m_zeitbedarf; }

	double getEntfernung() { return m_entfernung; }
	double getZeitbedarf() { return m_zeitbedarf; }
private:
	double m_entfernung;
	double m_zeitbedarf;
};











#endif
