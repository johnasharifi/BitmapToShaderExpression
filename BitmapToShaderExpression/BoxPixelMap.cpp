#include "pch.h"
#include "BoxPixelMap.h"

BoxPixelMap::BoxPixelMap(float _uvumin, float _uvumax, float _uvvmin, float _uvvmax, const Pixel& _px)
{
	uvumin = _uvumin;
	uvumax = _uvumax;
	uvvmin = _uvvmin;
	uvvmax = _uvvmax;

	Pixel px { _px.r, _px.g, _px.b };
}

BoxPixelMap::~BoxPixelMap()
{
}

Pixel BoxPixelMap::Get(float uvu, float uvv) {
	return Pixel{ 0,0,0 };
}
