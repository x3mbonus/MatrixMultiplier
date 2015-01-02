#pragma once
#include <string>
#include <map>
#include "Matrix.h"

using std::map;
using std::string;

class MatrixContainer
{
	map<string, Matrix *> _matrixCollection;
	bool _success;
	string _errorMessage;
	void setError(const string & message);
	void setError(char c);
	bool addValue(const string & expression, vector<double> & values);
public:
	const string & GetErrorMessage() { return _errorMessage; }
	bool LoadFromFile(const string & fileName);
	void AddMatrix(const string & name, const Matrix & matrix);
	Matrix * GetMatrix(const string & name);
	void Print();
	MatrixContainer(void);
	~MatrixContainer(void);
};