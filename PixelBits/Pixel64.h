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

	/// Given a query to a channel 0,1,2,3: get 0-255 / 8-bit data for that channel
	unsigned short getChannel(int channel) const {
		// channel = 0,1,2,3. shift by 0/8/16/24 bits
		return (backer & (255 << (8 * channel))) >> (8 * channel);
	}

	unsigned short getR() const { return getChannel(0); }
	unsigned short getG() const { return getChannel(1); }
	unsigned short getB() const { return getChannel(2); }
	unsigned short getA() const { return getChannel(3); }

	explicit operator std::string () const {
		std::string result;

		for (unsigned short rgba : {getR(), getG(), getB(), getA()}) {
			std::string channel = std::to_string(rgba);
			const int minLen = 3;
			while (channel.size() < minLen) channel = "0" + channel;
			result += channel + "\t";
		}
		return result;
	}

	std::string getBits() const {
		std::string result;

		for (unsigned short rgba : {getR(), getG(), getB(), getA()}) {
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
