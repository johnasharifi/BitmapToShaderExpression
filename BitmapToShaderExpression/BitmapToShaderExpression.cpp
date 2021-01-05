// BitmapToShaderExpression.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ReadFile.h"
#include "BoxPixelMap.h"
#include "PixelMapModel.h"

int main()
{
    std::cout << "Hello World!\n"; 

	std::string text = ReadFile::ReadText("GXvmX_64_64.csv");
	// std::map<Pixel, int> sparsePixelData = ReadFile::TextToSparsePixels(text);
	// std::cout << "whitespace count " << sparsePixelData[Pixel{ 1, 1, 1 }] << std::endl;

	std::map<std::pair<int,int>, Pixel> ijPixelData = ReadFile::TextToPixelTable(text);
	// Pixel px{ 0.5f, 0.6f, 0.9f };
	// std::cout << "hardcoded rgb " << (std::string) px << std::endl;
	std::cout << "rgb at index [32,32] = " << (std::string) ijPixelData[{32, 32}] << std::endl;

	BoxPixelMap map = BoxPixelMap(0, 18.0f / 64, 0, 21.0f / 64, Pixel{255,255,255});

	std::cout << "rgb for uv(0,0) is " << (std::string) map.Get(0, 0) << std::endl;

	PixelMapModel ijPixelModel(ijPixelData);
	for (int i = 24; i < 48; i++) {
		Pixel ijPixelDataPixel = ijPixelData[{i, i}];
		std::cout << "ijPixelDataPixel " << i << ", " << i << " has rgb " << (std::string) ijPixelDataPixel << std::endl;

		Pixel ijPixelModelPixel = ijPixelModel.GetPixel(std::pair<int, int>(i, i));
		std::cout << "ijPixelModelPixel " << i << ", " << i << " has rgb " << (std::string) ijPixelModelPixel << std::endl;
	}
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
