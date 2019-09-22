#include "Graph.h"
#include <limits>
#include <iostream>
#include <list>
#include <iterator>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include "Bahn.h"




std::string Haltestellen::getersteLinie() {
	for (std::list<Linie*>::iterator it = m_listLinie.begin(); it != m_listLinie.end(); ++it)
	{
		Linie* l = (*it);
		return l->getLinieName();
	}
	return "";

}

std::string Haltestellen::toString() const
{
	std::string result = "";
	for (auto ltemp : m_listLinie)
		result += ltemp->getLinieName() + " " + m_Id + "\n";
	return result;
}