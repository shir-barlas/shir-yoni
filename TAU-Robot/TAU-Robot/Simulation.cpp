#include "Simulation.h"




Simulation::Simulation(AbstractAlgorithm *_algorithm, House _currHouse, int conf[5])
: algorithm(_algorithm), currHouse(_currHouse)
{
	//docking = currHouse.getDocking;//ToCheck: not sure if this field needed
	robotLocation = Point(docking.getX(),docking.getY());//ToCheck: need to check if it is constructed well
	dirtLeft = currHouse.getTotalDirt();
	maxSteps = conf[0];
	maxStepsAfterWinner = conf[1];
	batteryCapacity = conf[2];
	batteryConsumptionRate = conf[3];
	batteryRechargeRate = conf[4];
	currentBattery = batteryCapacity;
	numOfStepsToFinish = maxStepsAfterWinner;

	Sensor sensor = Sensor(&currHouse, &robotLocation);//TODO: need to check if it is constructed well

	map<string, int> configs;
	configs["maxSteps"] = maxSteps;
	configs["maxStepsAfterWinner"] = maxStepsAfterWinner;
	configs["batteryCapacity"] = batteryCapacity;
	configs["batteryConsumptionRate"] = batteryConsumptionRate;
	configs["batteryRechargeRate"] = batteryRechargeRate;

	algorithm->setSensor(sensor);
	algorithm->setConfiguration(configs);
}

Simulation::~Simulation()//ToDo
{
}

Simulation::status Simulation::simulateStep(bool thereIsWinner)
{
	//handle battery use
	if (currHouse.getLocationInfo(robotLocation.getX(), robotLocation.getY()) == House::DOCKING)
		currentBattery = min(batteryCapacity, currentBattery + batteryRechargeRate);
	else
	{
		if (currentBattery <= 0)
			return BatteryEmpty;
		currentBattery = max(currentBattery - batteryConsumptionRate, 0);
	}

	if (thereIsWinner || (numOfStepsMade >= maxSteps - maxStepsAfterWinner)) 
	{
		if (numOfStepsToFinish == 0)
			return OutOfMoves;
		algorithm->aboutToFinish(numOfStepsToFinish);
		numOfStepsToFinish--;
	}
	
	//handle algorithm step
	Direction move = algorithm->step();

	switch (move) {
	case Direction::East:
		return makeMove(1, 0);
	case Direction::West:
		return makeMove(-1, 0);
	case Direction::South:
		return makeMove(0, -1);
	case Direction::North:
		return makeMove(0, 1);
	case Direction::Stay:
		return makeMove(0, 0);
	}
}

bool Simulation::isLegalMove(int x, int y)
{
	if (currHouse.getLocationInfo(robotLocation.getX() + x, robotLocation.getY() + y) == House::WALL)
		return false;
	else
		return true;
}

bool Simulation::isDone()
{
	if (dirtLeft == 0)
		return true;
	else
		return false;
}

Simulation::status Simulation::makeMove(int x, int y)
{
	if (!isLegalMove(x, y))
		return IllegalMove;

	robotLocation.setXY(robotLocation.getX() + x, robotLocation.getY() + y);
	char content = currHouse.getLocationInfo(robotLocation.getX(), robotLocation.getY());

	numOfStepsMade++;

	switch (content)
	{
	case '0':
	case ' ':
		break;
	case House::DOCKING:
		if (isDone())
			return Done;
		break;
	default:
		currHouse.cleanDirt(robotLocation.getX(), robotLocation.getY());
		dirtLeft--;
		break;
	}
	return StepMade;
}

int Simulation::getDirtLeft()
{
	return dirtLeft;
}

bool Simulation::isRobotInDocking()
{
	if (currHouse.getLocationInfo(robotLocation.getX(), robotLocation.getY() == House::DOCKING))
		return true;
	return false;
}

int Simulation::getNumOfStepsMade()
{
	return numOfStepsMade;
}

int Simulation::getPositionInCompetition()
{
	return positionInCompetition;
}

void Simulation::setPositionInCompetition(int position)
{
	positionInCompetition = position;
}

int Simulation::getScore()
{
	return score;
}

void Simulation::setScore(int new_score)
{
	score = new_score;
}


