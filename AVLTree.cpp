// AVLTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"

int main()
{
	Driver* driver = new Driver();
	int exitcode; 
	do
	{
	exitcode = driver->Menu();
	} while (exitcode != 0);

	
}



