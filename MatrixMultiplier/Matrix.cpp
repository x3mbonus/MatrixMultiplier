#include "Matrix.h"
#include <iostream>

using std::cout;

Matrix::Matrix(const vector<vector<double>> & values) 
{
	_sizeY = values.size();
	if (_sizeY > 0)
	{
		_sizeX = values[0].size();
	}
	else
	{
		_sizeX = 0;
	}
	_values.resize(_sizeY);
	for (int i = 0; i < _sizeY; i++)
	{
		_values[i].resize(_sizeX);
		for (int j = 0; j < _sizeX; j++)
		{
			_values[i][j] = values[i][j];
		}
	}
	
}

void Matrix::Print()
{
	cout << "Matrix " << _name.c_str() << std::endl;
		
	for (int i = 0; i < _sizeY; i++)
	{
		for (int j = 0; j < _sizeX; j++)
		{
			std::cout << _values[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "****************************" << std::endl;
}

Matrix::Matrix(void):
	_sizeX(0),
	_sizeY(0),
	_name("")
{
}


Matrix::~Matrix(void)
{
}
