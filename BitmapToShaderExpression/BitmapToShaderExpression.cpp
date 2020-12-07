// BitmapToShaderExpression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ReadFile.h"

int main()
{
    std::cout << "Hello World!\n"; 

	std::string text = ReadFile::ReadText("GXvmX.csv");
	// std::map<Pixel, int> sparsePixelData = ReadFile::TextToSparsePixels(text);
	// std::cout << "whitespace count " << sparsePixelData[Pixel{ 1.0, 1.0, 1.0 }] << std::endl;

	std::map<std::pair<int,int>, Pixel> ijPixelData = ReadFile::TextToPixelTable(text);
	// Pixel px{ 0.5f, 0.6f, 0.9f };
	// std::cout << "hardcoded rgb " << (std::string) px << std::endl;
	std::cout << "rgb at index [32,32] = " << (std::string) ijPixelData[{32, 32}] << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
