#pragma once

#include "AbstractAlgorithm.h";
#include "Sensor.cpp";
#include "SensorInformation.h";
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
	int dirtLeft;
	int maxSteps;
	int maxStepsAfterWinner;
	int batteryCapacity;
	int batteryConsumptionRate;
	int batteryRechargeRate;


public:
	Simulation(AbstractAlgorithm *_algorithm, House _currHouse ,int totalDirt, int conf[5]);
	~Simulation();

};

