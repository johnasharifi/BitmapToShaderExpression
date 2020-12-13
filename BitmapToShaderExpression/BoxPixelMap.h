#pragma once
#include "IUVPixelMap.h"
#include "ReadFile.h"

/*
A class for looking up pixel colors within certain bounds.
*/
class BoxPixelMap :
	public IUVPixelMap
{
public:
	BoxPixelMap(float _uvumin, float _uvumax, float _uvvmin, float _uvvmax, const Pixel & _px);
	~BoxPixelMap();
	Pixel Get(float uvu, float uvv);

private:
	float uvumin;
	float uvumax;
	float uvvmin;
	float uvvmax;

	Pixel px;
};

