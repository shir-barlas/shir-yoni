#include "House.h"

House::House(string housePath) : docking()
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

	}

}

/*House::House(int _row, int _col, char ** _houseMap)
	: row(_row), col(_col), houseMap(_houseMap) {}*/


House :: ~House()//Todo:
{
}
char House :: getLocationInfo(int x, int y)
{
	if (houseMap[x][y] == ' ' || houseMap[x][y] == House::DOCKING) {
		return '0';
	}
	return this->houseMap[x][y];
}
Point House::getDocking()
{
	return this->docking;//ToCheck: if it returns a copy or the same Point
}

void House :: frameHouse()
{
	for (int i; i < this->row; i++)
	{
		this->houseMap[i][0] = House::WALL;
		this->houseMap[i][this->col] = House::WALL;
	}
	for (int j; j < this->row; j++)
	{
		this->houseMap[0][j] = House::WALL;
		this->houseMap[this->row][j] = House::WALL;
	}
}
void House :: findDocking()
{
	for (int i=0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) 
		{
			if(this->houseMap[i][j] == House::DOCKING)
			{
				if (this->docking.getX() == -1)
					this->docking.setXY(i, j);
				else
				{
					this->docking.setXY(-1, -1);
					return;
				}
					
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

