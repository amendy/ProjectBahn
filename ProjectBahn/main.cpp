#include <iostream>
#include "Graph.h"
#include "Bahn.h"
#include "GUI.h"
#include "Exception.h"


int main()
{


	Graph g;
	Bahn* bahn = new Bahn("Berlin.txt", "Berlin Bahn");
	GUI gui(*bahn);
	bool finished = false;

	// Endlosschleife, bis finished auf 'true' gesetzt wird 
	while (!finished)
	{
		try {
			int menuEntry = gui.startMenu();
			switch (menuEntry)
			{
			case 1:
				gui.ReadDatafromfile();
				break;
			case 2:
				gui.NewHaltestelle();
				break;
			case 3:
				gui.DeleteHaltestelle();
				break;
			case 4:
				gui.EditHaltestelle();
				break;
			case 5:
				gui.AddNewPath();
				break;
			case 6:
				gui.ViewAllData();
				break;
			case 7:
				gui.FindShortestDestination();
				break;
			case 8:
				gui.FindfastesDestination();
				break;
			case 9:
				gui.SaveData();
				break;
			case 10:
				gui.AusgabeAlsjpg();
				break;
			case 11:
				finished = true;
				break;
			default:
				break;
			}
		}
		catch (Exception* e)
		{
			cout << e->getMessage() << endl;
		}
	}
	system("pause"); 
	return 0;
}
