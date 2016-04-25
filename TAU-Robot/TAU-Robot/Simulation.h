#pragma once

#include "AbstractAlgorithm.h";
#include "AbstractSensor.h";
#include "Sensor.cpp";
//#include "SensorInformation.h";
#include "Direction.h"
#include "House.h";
#include "Point.h";
#include <map>;
#include <algorithm>


using namespace std;

class Simulation
{
	AbstractAlgorithm * algorithm;
	House currHouse;
	Point robotLocation;
	Point docking;	
	int currentBattery;
	int dirtLeft;
	int numOfStepsMade = 0;
	int numOfStepsToFinish;
	int positionInCompetition;
	int score;

	int maxSteps;
	int maxStepsAfterWinner;
	int batteryCapacity;
	int batteryConsumptionRate;
	int batteryRechargeRate;


public:
	Simulation(AbstractAlgorithm *_algorithm, House _currHouse , int conf[5]);

	~Simulation();
	
	//enum of simulation status for informing simulator
	enum status { IllegalMove , StepMade , BatteryEmpty ,OutOfMoves, Done };

	//this method is caled by the simulator inorder to simulate one step of the algorithm
	status simulateStep(bool thereIsWinner);

	//check if move is legal. x and y are relative to robot location
	bool isLegalMove(int x, int y);

	//check if house is clean and robot is back in docking
	bool isDone();

	//move as requsted. x and y are relative to robot location
	status makeMove(int x, int y);

	//for score calculation
	int getDirtLeft();

	//check if robot is in docking
	bool isRobotInDocking();


	int getNumOfStepsMade();

	int getPositionInCompetition();

	void setPositionInCompetition(int position);

	int getScore();

	void setScore(int new_score);

};

