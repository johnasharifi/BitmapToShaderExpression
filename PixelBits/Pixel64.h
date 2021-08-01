#pragma once

#include <string>
#include <iostream>
#include <vector>

struct Pixel64
{
public:
	unsigned int backer;

	Pixel64(unsigned int bits) {
		// assume that backer is an int32_t
		// flush out the bigger bits
		bits = (bits << 32) >> 32;
		backer = bits;
	}

	explicit operator std::string () const {
		std::string result;

		unsigned short r = (backer & (255 << 24)) >> 24;
		unsigned short g = (backer & (255 << 16)) >> 16;
		unsigned short b = (backer & (255 << 8)) >> 8;
		unsigned short a = (backer & (255 << 0)) >> 0;

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

		unsigned short r = (backer & (255 << 24)) >> 24;
		unsigned short g = (backer & (255 << 16)) >> 16;
		unsigned short b = (backer & (255 << 8)) >> 8;
		unsigned short a = (backer & (255 << 0)) >> 0;

		for (unsigned short rgba : {r, g, b, a}) {
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
