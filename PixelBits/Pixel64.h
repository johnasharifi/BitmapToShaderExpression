#pragma once

#include <string>
#include <iostream>
#include <vector>

struct Pixel64
{
public:
	unsigned int backer;

	/// Construct a Pixel64 from user-specified int of format [[32 unused bits...], [8x r], [8x g], [8x b], [8x a]]
	Pixel64(unsigned int bits) {
		// assume that backer is an int32_t
		// flush out the bigger bits
		bits = (bits << 32) >> 32;
		backer = bits;
	}

	void setChannel(int channel, unsigned short value) {
		// this will be our new backer
		unsigned int fValue = 0x00000000;

		int maxi = 8 * (channel + 1);
		int mini = 8 * (channel + 0);
		for (int i = 0; i < 64; ++i) {
			// check if bit in mini - maxi span. if so, get bit from value. else get bit from backer
			int b = (backer & (1 << i));
			if (mini <= i && i < maxi) {
				// get ith bit of value
				b = value & (1 << (i % 8));
				// move into position to be logically OR'd with the unsigned int
				b = b << (i - i % 8);
			}
			fValue = fValue | b;
		}

		// move bits
		backer = fValue;
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
