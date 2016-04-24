#include "Simulation.h"



Simulation::Simulation(AbstractAlgorithm *_algorithm, House _currHouse, int totalDirt, int conf[5])
: algorithm(_algorithm), currHouse(_currHouse), dirtLeft(totalDirt)
{
	docking = currHouse.getDocking;//ToCheck: not sure if this field needed
	robotLocation = *(new Point(docking.getX(),docking.getY()));//ToCheck:
	maxSteps = conf[0];
	maxStepsAfterWinner = conf[1];
	batteryCapacity = conf[2];
	batteryConsumptionRate = conf[3];
	batteryRechargeRate = conf[4];

	AbstractSensor sensor = new Sensor(&currHouse, &robotLocation);
	map config = new map();
	config.ins
	algorithm->setSensor(sensor);
	algorithm->setConfiguration();

}


Simulation::~Simulation()//ToDo
{
}

Simulation::simulateStep()
{

}