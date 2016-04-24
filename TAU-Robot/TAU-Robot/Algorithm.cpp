#include "AbstractAlgorithm.h";

class Algorithm : AbstractAlgorithm {
	// Inherited via AbstractAlgorithm
	virtual void setSensor(const AbstractSensor & sensor) override
	{
	}
	virtual void setConfiguration(map<string, int> config) override
	{
	}
	virtual Direction step() override
	{
		return Direction();
	}
	virtual void aboutToFinish(int stepsTillFinishing) override
	{
	}
};