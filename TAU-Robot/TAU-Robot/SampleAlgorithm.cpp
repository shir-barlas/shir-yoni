#include "AbstractAlgorithm.h"
#include "Direction.h"
#include <cstdlib>

class SampleAlgorithm : public AbstractAlgorithm
{
	int maxStepsAfrterWinner;
	int batteryCapacity;
	int batteryConsumptionRate;
	int batteryRechargeRate;
	int stepsToFinish;
	const AbstractSensor *algorithmSensor;

public:
	SampleAlgorithm() {}

	void setSensor(const AbstractSensor& sensor)
	{
		algorithmSensor = &sensor;
	}

	void setConfiguration(map<string, int> config)
	{
		maxStepsAfrterWinner = config["maxStepsAfterWinner"];
		batteryCapacity = config["batteryCapacity"];
		batteryConsumptionRate = config["batteryConsumptionRate"];
		batteryRechargeRate = config["batteryRechargeRate"];
		stepsToFinish = INFINITY;
	}

	// step is called by the simulation for each time unit 
	Direction step()
	{
		while (true)
		{
			int randomStep = rand() % 5;
			SensorInformation info = algorithmSensor->sense();
			if (!info.isWall[randomStep])
				return (Direction)randomStep;
		}
	}

	// this method is called by the simulation either when there is a winner or 
	// when steps == MaxSteps - MaxStepsAfterWinner 
	// parameter stepsTillFinishing == MaxStepsAfterWinner 
	void aboutToFinish(int stepsTillFinishing) 
	{
		stepsToFinish = stepsTillFinishing;
	}
};
