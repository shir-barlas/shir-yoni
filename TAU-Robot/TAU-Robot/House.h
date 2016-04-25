#pragma once
#include "Point.h"
#include <map>
#include <fstream>
#include <string>
//#include <iostream>
using namespace std;

class House
{
	string name;
	string description;
	int row;
	int col;
	int totalDirt = 0;
	char ** houseMap;
	Point docking;

public:
	enum { DOCKING = 'D', WALL = 'W' };
	House(string housePath);
	//House(int _row, int _col, char ** _houseMap, Point _docking);
	House();
	~House();
	char getLocationInfo(int x, int y);

	char getDirtInfo(int x, int y);

	int getTotalDirt();

	string getName();

	//cleans one unit of dirt in the requested location
	void cleanDirt(int x, int y);

	Point getDocking();
		
private:
	void frameHouse();

	void findDocking();

	void findAllDirt();
};

