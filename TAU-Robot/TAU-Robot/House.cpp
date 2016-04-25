#include "House.h"

House::House(string housePath)
{
	ifstream houseFile(housePath);
	string line;

	if (houseFile.is_open()) //ToDo: fix undefined func and illegal house conf file
	{
		getline(houseFile, line);
		name = line;
		getline(houseFile, line);
		description = line;
		getline(houseFile, line);
		row = stoi(line);
		getline(houseFile, line);
		col = stoi(line);
		houseMap = new char*[row]();
		for (int i = 0; i < row; i++)
			houseMap[i] = new char[col]();

		string dirtLevels = "123456789";
		for (int i = 0; i < row; i++)
		{
			getline(houseFile, line);
			if (houseFile.eof())
			{
				for (int r = i; r < row; r++) {
					for (int c = 0; c < col;c++)
					{
						houseMap[r][c] = ' ';
					}
				}
				break;
			}
			for (int j = 0; j < col; j++)
			{
				if (line.length -1 < j) 
					houseMap[i][j] = ' ';

				else if ((char)toupper(line[j]) == House::WALL)
					houseMap[i][j] = House::WALL;

				else if ((char)toupper(line[j]) == House::DOCKING)
					houseMap[i][j] = House::DOCKING;

				else if (dirtLevels.find(line[j]) != string::npos)
					houseMap[i][j] = line[j];

				else
					houseMap[i][j] = ' ';
			}

		}
		houseFile.close();
		frameHouse();
		findDocking();
		findAllDirt();
	}

}

House::House()
{
	name = "Hard coded house";
	description = "A special hard coded house for ex01";
	row = 19;
	col = 80;
	totalDirt = 0;
	houseMap = new char*[19];
	char hardCodedHouse[19][81] = {
		//             1         2         3         4         5         6         7        
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W  99                  1234321                                                 W", // 1
		"W  99      WWWWWWW     1234321                                             1   W", // 2
		"W              W                                               W           2   W", // 3
		"W              W                                               W           3   W", // 4
		"W              W      WWWWWWW    11      11        00099       W           4   W", // 5
		"W              W     W       W     11  11         00  88       W           5   W", // 6
		"W              W    W  WWWWWWWW      11     WWWW      77       W           6   W", // 7
		"W                    W             11  11             66                   7   W", // 8
		"W                      WWWWWW    11      11       001234500                8   W", // 9
		"W              W                                               W           9   W", // 10
		"W              W                                               W           8   W", // 11
		"W              W                                               W           7   W", // 12
		"W              W                                               W           6   W", // 13
		"W              W                                               W           5   W", // 14
		"W              W                                               W           4   W", // 15
		"W              W                       D                       W           3   W", // 16
		"W              W                                               W               W", // 17
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" // 18
	};
	for (int i =0 ; i < 19; i++)
	{
		houseMap[i] = hardCodedHouse[i];
	}
	frameHouse();
	findDocking();
	findAllDirt();
}
/*House::House(int _row, int _col, char ** _houseMap)
	: row(_row), col(_col), houseMap(_houseMap) {}*/


House::~House()//Todo:
{
}

char House::getLocationInfo(int x, int y)
{
	return houseMap[x][y];
}

char House::getDirtInfo(int x, int y)
{
	if (houseMap[x][y] == ' ' || houseMap[x][y] == House::DOCKING) {
		return '0';
	}
	return houseMap[x][y];
}

int House::getTotalDirt()
{
	return totalDirt;
}

string House::getName()
{
	return name;
}

void House::cleanDirt(int x, int y)
{
	houseMap[x][y]--;
}

Point House::getDocking()
{
	return this->docking;//ToCheck: if it returns a copy or the same Point
}

void House::frameHouse()
{
	for (int i; i < row; i++)
	{
		houseMap[i][0] = House::WALL;
		houseMap[i][col] = House::WALL;
	}
	for (int j; j < row; j++)
	{
		houseMap[0][j] = House::WALL;
		houseMap[row][j] = House::WALL;
	}
}

void House::findDocking()
{
	for (int i=0; i < row; i++) {
		for (int j = 0; j < col; j++) 
		{
			if(houseMap[i][j] == House::DOCKING)
			{
				if (docking.getX() == -1)
					docking.setXY(i, j);
				else
				{
					docking.setXY(-1, -1);
					return;
				}
					
			}
		}
	}
}

void House::findAllDirt()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
		{
			char content = houseMap[i][j];
			switch (content)
			{
			case WALL:
			case DOCKING:
			case ' ':
				break;
			default:
				totalDirt += content - '0';
				break;
			}
		}
	}
}

/*void houseFileParser(string path)
{
	ifstream houseFile(path);
	string line;

	if (houseFile.is_open())
	{
		getline(houseFile,line);
		name = 
		houseFile.close();
	}


}*/

