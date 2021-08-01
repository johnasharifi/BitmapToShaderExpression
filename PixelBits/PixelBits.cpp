// PixelBits.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Pixel64.h"

// debug utility
std::string toBits(int value) {
	std::string result;
	const int bitCount = 64;
	for (int i = 0; i < bitCount; ++i) {
		result = std::to_string(value & 1) + result;
		value = value >> 1;
	}
	return result;
}

int main()
{
	Pixel64 mpixel0(0);
	Pixel64 mpixel1(3503345872); // 11010000 x 4
	Pixel64 mpixel2(UINT_MAX);

	for (Pixel64 mpixel : {mpixel0, mpixel1, mpixel2}) {
		std::cout << "mpixel value is " << (std::string) mpixel << "with bits " << mpixel.getBits() << "\n";
	}

	int code;
	std::cin >> code;
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
