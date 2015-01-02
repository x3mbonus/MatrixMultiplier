#pragma once
#include <vector>

using std::vector;
using std::string;

class Matrix
{
	vector<vector<double>> _values;
	int _sizeX;
	int _sizeY;
	string _name;
public:
	/*int GetSizeX() const;
	int GetSizeY() const;
	void SetSize(int sizeX, int sizeY);
	double GetValue(int x, int y) const;
	void SetValue(int x, int y, double value);*/
	string GetName() const { return _name; }
	void SetName(const string & name) { _name = name; }
	/*Matrix operator+(const Matrix & matrix1) const;
	Matrix operator-(const Matrix & matrix1) const;
	Matrix operator*(const Matrix & matrix1) const;*/
	void Print();
	Matrix(void);
	Matrix(const vector<vector<double>> & values);
	~Matrix(void);
};

