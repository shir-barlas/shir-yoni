#include "Simulation.h"
#include "SampleAlgorithm.cpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <boost/program_options.hpp>
namespace commandParser = boost::program_options;
using namespace std;

class Simulator
{
	static int numOfWinnerSteps;
	const string usage_error_message = "Usage: simulator [-config <config path>]";

	const string MaxSteps_head = "MaxSteps";
	const string MaxStepsAfterWinner_head = "MaxStepsAfterWinner";
	const string BatteryCapacity_head = "BatteryCapacity";
	const string BatteryConsumptionRate_head = "BatteryConsumptionRate";
	const string BatteryRachargeRate_head = "BatteryRachargeRate";

	int main(int argc, char* argv[])
	{
		string configFileSuffix = "config.ini";
		string configFilePath;
		int config[5];

		if (argc == 1) 
		{
			configFilePath = "config.ini";
		}
		else if (argc == 3 && argv[1] == "-config")
		{
			string configDirectoryPath = argv[2];
			if (configDirectoryPath.back() != '\\')
				configDirectoryPath.push_back('\\');
			configFilePath = configDirectoryPath + configFileSuffix;
		}
		else
		{
			cout << usage_error_message;
			return 0;
		}

		ifstream configFile(configFilePath);
		string line;
		

		if (configFile.is_open()) //TODO: error message
		{
			int equalSignIndex;
			string argName, argValue;
			while (!configFile.eof())
			{
				getline(configFile, line);
				equalSignIndex = line.find('=');//TODO: check what find returns if not found
				argName = line.substr(0, equalSignIndex);
				argValue = line.substr(equalSignIndex);

				if (argName == MaxSteps_head)
					config[0] = stoi(argValue);//TODO: what happens if it is not a string that represents an int
				else if (argName == MaxStepsAfterWinner_head)
					config[1] = stoi(argValue);
				else if (argName == BatteryCapacity_head)
					config[2] = stoi(argValue);
				else if (argName == BatteryConsumptionRate_head)
					config[3] = stoi(argValue);
				else if (argName == BatteryRachargeRate_head)
					config[4] = stoi(argValue);
			}
		}


		
		numOfWinnerSteps = config[0];//TODO: make sure it is 0
		bool isThereAWinner = false;
		House house = House();
		AbstractAlgorithm * algorithm = &SampleAlgorithm();
		Simulation simulation = Simulation(algorithm, house, config);

		while (!isThereAWinner)
		{
			Simulation::status simulationStatus = simulation.simulateStep(isThereAWinner);

			switch (simulationStatus)
			{
			case Simulation::StepMade:
				break;
			case Simulation::IllegalMove:
				isThereAWinner = true;//TODO: only relevant for ex 1
				break;
			case Simulation::BatteryEmpty:
				//break;
			case Simulation::OutOfMoves:
				simulation.setPositionInCompetition(10);
				isThereAWinner = true;//TODO: only relevant for ex 1
				break;
			case Simulation::Done:
				simulation.setPositionInCompetition(1);
				isThereAWinner = true;
				numOfWinnerSteps = simulation.getNumOfStepsMade();
				break;
			default:
				break;
			}

		}
		int score = calculateScore(simulation);
		simulation.setScore(score);
		cout << "[" << house.getName() << "]\t" << score << "\r\n";

		return 0;
		

		/*string confFile = "config.ini";
		string houseSuffix = ".house";
		string algoSuffix = "_.so"; //irrelevant for ex1

		int config[5];
		int numOfAlgorithms;
		int numOfHouses;

		vector<House> allHouses;
		vector<Simulation> allSimulations;
		vector<AbstractAlgorithm> allAlgorithms;

		//House Generator
		string currentHousePath;
		allHouses.push_back(House(currentHousePath));

		for each (House house in allHouses)
		{
			for each (AbstractAlgorithm algorit in allAlgorithms)
			{
				allSimulations.push_back(Simulation(&algorit, house, config));
			}

		}
		//Semulation Generator*/



	}

private: 
	int calculateScore(Simulation& simulate)
	{
		int score = 2000;
		score -= (simulate.getPositionInCompetition() - 1) * 50;
		score -= (simulate.getNumOfStepsMade() - numOfWinnerSteps);
		score -= 3 * simulate.getDirtLeft();
		score += simulate.isRobotInDocking() ? 50 : -200;
		return max(0, score);
	}
};