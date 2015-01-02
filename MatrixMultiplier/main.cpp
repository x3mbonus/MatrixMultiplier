#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "MatrixContainer.h"

using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ios_base;
using std::begin;
using std::end;
using std::endl;

void showHelp();

int main (int argc, char ** args)
{
	if (argc < 2)
	{
		showHelp();
		return -1;
	}
	string fileName(args[1]);	
	MatrixContainer container;
	if (!container.LoadFromFile(fileName))
	{
		const string & errors = container.GetErrorMessage();
		cout << errors << endl;
	}
	container.Print();
	bool exit = false;
	string command;
	while(!exit)
	{
		cout << "Enter command (exit = exit): ";
		cin >> command;
		if (command == "quit" ||
			command == "exit")
		{
			exit = true;
			break;
		}
	};
}

void showHelp()
{
	cout << "First parameter - Full file name with the matrixes.";
}