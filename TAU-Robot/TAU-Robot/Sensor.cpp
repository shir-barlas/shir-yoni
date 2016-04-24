#include "AbstractSensor.h"
#include "House.h"
#include "Direction.h"

class Sensor : public AbstractSensor {
	// Inherited via AbstractSensor
	House * myHouse;
	Point * robotLocation;

public:
	Sensor(House *house,Point *location)
		: myHouse(house), robotLocation(location){}

	//~Sensor();//ToDo:

	SensorInformation sense() const
	{		
		int row = (*(this->robotLocation)).getX();
		int col = (*(this->robotLocation)).getY();
		SensorInformation info;
		info.isWall[(int)Direction::East] = (*(this->myHouse)).getLocationInfo(row, col+1) == House::WALL;
		info.isWall[(int)Direction::West] = (*(this->myHouse)).getLocationInfo(row, col-1) == House::WALL;
		info.isWall[(int)Direction::South] = (*(this->myHouse)).getLocationInfo(row-1, col) == House::WALL;
		info.isWall[(int)Direction::North] = (*(this->myHouse)).getLocationInfo(row+1, col) == House::WALL;
		info.dirtLevel = (*(this->myHouse)).getLocationInfo(row, col) - '0';

		return info;
	}
};