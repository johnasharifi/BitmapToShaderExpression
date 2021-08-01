#pragma once

#include <string>
#include <iostream>

struct Pixel64
{
public:
	unsigned short r;
	unsigned short g;
	unsigned short b;
	unsigned short a;

	explicit operator std::string () const {
		std::string result;
		for (unsigned short rgba : {r, g, b, a}) {
			std::string channel = std::to_string(rgba);
			const int minLen = 3;
			while (channel.size() < minLen) channel = "0" + channel;
			result += channel + "\t";
		}
		return result;
	}
};
