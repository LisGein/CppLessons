// Stask.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Enter.h"



int _tmain(int argc, _TCHAR* argv[])
{
	Enter objEnter;

	std::cout << "Hello world!" << std::endl;
	int mass[10];
	int scores[10];
	//Ввод массива
	for (int i = 1; i < 11; i++){
		std::cout << "Enter the " << i << " element of the array" << std::endl;
		std::cin >> mass[i];
	}
	objEnter.cin(mass);//сохранение массива в объект класса Enter
		
	
	return 0;
	}
	
