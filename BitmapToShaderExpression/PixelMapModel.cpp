#include "pch.h"
#include "PixelMapModel.h"

PixelMapModel::PixelMapModel(std::map<std::pair<int, int>, Pixel> _map)
{
	subModels = std::vector<PixelMapModel>();

	// objective: for now, create a single sub-PixelMapModel for each ij coordinate

	// case: is an n-element pixel map of many pixels
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
			minx = kv.first.first;
			miny = kv.first.second;
			maxx = kv.first.first + 1;
			maxy = kv.first.second + 1;

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
	if (ijCoord.first >= minx && ijCoord.first <= maxx &&
		ijCoord.second >= miny && ijCoord.second <= maxy)
		return true;

	for (PixelMapModel elem : subModels) {
		if (elem.Contains(ijCoord)) return elem.Contains(ijCoord);
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
