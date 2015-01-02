#include "MatrixContainer.h"
#include <iostream>
#include <string>
#include <fstream>

using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::ios_base;

void MatrixContainer::setError(const string & message)
{
	_success = false;
	_errorMessage = message;
}

void MatrixContainer::setError(char c)
{
	string message = "Invalid char '";
	message += c;
	message += "'"; 
	setError(message);
}

bool MatrixContainer::LoadFromFile(const string & fileName)
{
	ifstream file(fileName, ios_base::in);
	if (!file.is_open())
	{
		cout << "Error opening file " << fileName << endl;
		return false;
	}
	int start = file.tellg();
	file.seekg(0, ios_base::end);
	int end = file.tellg();
	int size = end - start;
	file.seekg(0, ios_base::beg);
	char * content = new char[size + 1];
	file.read(content, size);
	content[size] = '\0';
	char * cPtr = content;
	string expression = "";
	int countOpened = 0;
	vector<double> rowValues;
	vector<vector<double>> rows;
	string matrixName;
	/*Name[sizeX,sizeY] <SizeSetted> {<FirstLevel>{<SecondLevel>,,,}, <FirstLevel>{,,,}, {,,,}}*/
	enum Segment { Name, SizeY, SizeX, SizeSetted, FirstLevel, SecondLevel };
	int segment = Name;
	int sizeX, sizeY;
	_success = true;
	cout << content << endl;
	system("pause");
	int i = 0;
	while(i++ < size && _success)
	{
		char c = *cPtr;
		switch (*cPtr)
		{
		case '[':
			if (segment == Name)
			{
				segment ++;
				matrixName = expression;
				sizeX = sizeY = 0;
			}
			else
			{
				setError(c);
			}
			expression = "";
			break;
		case ']':
			if (segment == SizeX)
			{
				segment ++;
				if (!expression.empty())
				{				
					try
					{
						sizeX = std::stoi(expression);
					}
					catch(std::invalid_argument exception)
					{
						setError("Invalid argument");
						break;
					}
				}
			}
			else
			{
				setError(c);				
			}
			expression = "";
			break;
		case ',':
			if (segment == SizeY)
			{
				segment ++;
				if (!expression.empty())
				{
					try
					{
						sizeY = std::stoi(expression);
					}
					catch(std::invalid_argument exception)
					{
						setError("Invalid argument");
						break;
					}
				}
			}
			else if (segment == FirstLevel)
			{
				if (!expression.empty())
				{
					setError(c);
					break;
				}
				
			}
			else if (segment == SecondLevel)
			{
				if (!addValue(expression, rowValues))
				{
					break;
				}
			}
			else
			{
				setError(c);				
			}
			expression = "";
			break;
		case ' ':
		case '\r':
		case '\n':
		case '\t':
			break;
		case '{':
			if (segment == SizeSetted)
			{
				segment ++;
			}
			else if (segment == FirstLevel)
			{
				rowValues.clear();
				segment ++;
			}
			else
			{
				setError(c);
			}
			expression = "";
			break;
		case '}':
			if (segment == SecondLevel)
			{
				segment --;
				if (! addValue(expression, rowValues))
				{
					break;
				}
				if (sizeX != 0 && rowValues.size() != sizeX)
				{
					setError("Invalid amount of columns");
					break;
				}
				rows.push_back(rowValues);								
			}
			else if (segment == FirstLevel)
			{
				segment = Name;
				if (sizeY != 0 && rows.size() != sizeY)
				{
					setError("Invalid amount of rows");
					break;
				}
				Matrix * matrix = new Matrix(rows);
				matrix->SetName(matrixName);
				_matrixCollection.emplace(matrix->GetName(), matrix);
				rows.clear();
			}
			else
			{
				setError(c);
			}
			expression = "";
			break;		
		default:
			expression += c;
		}
		cPtr++;
	}
	delete [] content;	
	file.close();
	return _success;
}


bool MatrixContainer::addValue(const string & expression,  vector<double> & values)
{
	try
	{
		double value = std::stod(expression);
		values.push_back(value);
	}
	catch(std::invalid_argument exception)
	{
		setError("Invalid argument");					
		return false;
	}
	return true;
}

void MatrixContainer::AddMatrix(const string & name, const Matrix & matrix)
{
}

Matrix * MatrixContainer::GetMatrix(const string & name)
{
	return _matrixCollection.at(name);
}

void MatrixContainer::Print()
{
	for(auto m : _matrixCollection)
	{
		Matrix * matrix = m.second;
		if (matrix != nullptr)
		{
			matrix->Print();
		}
	}
}

MatrixContainer::MatrixContainer(void) :
	_success(true),
	_errorMessage("")
{
}


MatrixContainer::~MatrixContainer(void)
{
	for (auto m : _matrixCollection)
	{
		delete m.second;
		m.second = nullptr;
	}
}
