#pragma once

#include "AbstractAlgorithm.h";
#include "AbstractSensor.h";
#include "Sensor.cpp";
//#include "SensorInformation.h";
#include "Direction.h"
#include "House.h";
#include "Point.h";
#include <map>;
using namespace std;

class Simulation
{
	AbstractAlgorithm * algorithm;
	House currHouse;
	Point robotLocation;
	Point docking;	
	int battery;
	int dirtLeft;
	int maxSteps;
	int maxStepsAfterWinner;
	int batteryCapacity;
	int batteryConsumptionRate;
	int batteryRechargeRate;


public:
	Simulation(AbstractAlgorithm *_algorithm, House _currHouse ,int totalDirt, int conf[5]);

	~Simulation();
	
	enum { IllegalStep , StepMade , BatteryEmpty , Done };

	void simulateStep();

	//check if move is legal. x and y are relative to robot location
	bool isLegalMove(int x, int y);

	//move as requsted. x and y are relative to robot location
	void makeMove(int x, int y);

};

