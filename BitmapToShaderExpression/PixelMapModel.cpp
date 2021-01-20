#include "pch.h"
#include "PixelMapModel.h"

PixelMapModel::PixelMapModel(std::map<std::pair<int, int>, Pixel> _map)
{
	subModels = std::vector<PixelMapModel>();

	// objective: for now, create a single sub-PixelMapModel for each ij coordinate
	std::pair<int, int> lowest = _map.begin()->first;
	std::pair<int, int> highest = _map.rbegin()->first;
	minx = lowest.first;
	miny = lowest.second;
	maxx = highest.first + 1;
	maxy = highest.second + 1;

	// case: is an n-element pixel map
	if (_map.size() > 1) {
		for (std::pair<std::pair<int, int>, Pixel> kv : _map) {
			// create a map with just one pair - coord ij to Pixel ij
			std::map<std::pair<int, int>, Pixel> ijMap;
			ijMap.emplace(kv.first, kv.second);

			// create a model with just one value - ij
			PixelMapModel ijModel(ijMap);
			subModels.push_back(ijModel);
		}
	}
	// case: is an ij pixel map with a single element
	else {
		// for now just iterate through all elements. should just be 1 element...!
		for (std::pair<std::pair<int, int>, Pixel> kv : _map) {
			m_Pixel.r = kv.second.r;
			m_Pixel.g = kv.second.g;
			m_Pixel.b = kv.second.b;
		}
	}
}

PixelMapModel::~PixelMapModel()
{
}

bool PixelMapModel::Contains(std::pair<int, int> ijCoord)
{
	if (ijCoord.first >= minx && ijCoord.first < maxx &&
		ijCoord.second >= miny && ijCoord.second < maxy)
		return true;

	for (PixelMapModel elem : subModels) {
		if (elem.Contains(ijCoord)) return true;
	}

	return false;
}

Pixel PixelMapModel::GetPixel(std::pair<int, int> ijCoord)
{
	for (PixelMapModel elem : subModels) {
		if (elem.Contains(ijCoord)) return elem.GetPixel(ijCoord);
	}
	return m_Pixel;
}
