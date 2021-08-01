#pragma once

#include <string>
#include <iostream>
#include <vector>

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

	std::string getBits() const {
		std::string result;

		for (short rgba : {r, g, b, a}) {
			const int len = 8;
			std::string channel = "";
			for (int i = 0; i < len; ++i) {
				channel = std::to_string(rgba & 1) + channel;
				rgba = rgba >> 1;
			}
			result += channel + "\t";
		}

		return result;
	}
};
