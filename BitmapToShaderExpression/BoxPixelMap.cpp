#include "pch.h"
#include "BoxPixelMap.h"


BoxPixelMap::BoxPixelMap()
{
}

BoxPixelMap::~BoxPixelMap()
{
}

Pixel BoxPixelMap::Get(float uvu, float uvv) {
	return Pixel{ 0,0,0 };
}
