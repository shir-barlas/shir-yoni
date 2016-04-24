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

	AbstractSensor * sensor = new Sensor(&currHouse, &robotLocation);

	map<string, int> configs;
	configs["maxSteps"] = maxSteps;
	configs["maxStepsAfterWinner"] = maxStepsAfterWinner;
	configs["batteryCapacity"] = batteryCapacity;
	configs["batteryConsumptionRate"] = batteryConsumptionRate;
	configs["batteryRechargeRate"] = batteryRechargeRate;

	algorithm->setSensor(*sensor);
	algorithm->setConfiguration(configs);
}


Simulation::~Simulation()//ToDo
{
}

void Simulation::simulateStep()
{
	Direction move = algorithm->step();

	switch (move) {
	case Direction::East:
		if (isLegalMove(1, 0))
			makeMove(1, 0);

		break;
	case Direction::West:
		cout << "West" << endl;
		break;
	case Direction::South:
		cout << "South" << endl;
		break;
	case Direction::North:
		cout << "North" << endl;
		break;
	case Direction::Stay:
		throw UnexpectedDirection(Direction::Stay);
		break;
	}
}

bool Simulation::isLegalMove(int x, int y)
{
	if (currHouse.getLocationInfo(robotLocation.getX() + x, robotLocation.getY() + y) == House::WALL)
		return false;
	return true;
}

void Simulation::makeMove(int x, int y)
{

	robotLocation.setXY(robotLocation.getX() + x, robotLocation.getY() + y);
	char content = currHouse.getLocationInfo(robotLocation.getX(), robotLocation.getY());

	switch (content)
	{
	case '0':
	case ' ':
		break;
	case House::DOCKING:
		break;
	default:
		currHouse.cleanDirt(robotLocation.getX(), robotLocation.getY());
		dirtLeft--;
		break;
	}
}