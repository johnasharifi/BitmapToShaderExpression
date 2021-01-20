#include "pch.h"
#include "PixelMapModel.h"

namespace {
	const int pixelMapChunkMaxCount = 64;
}

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

	// case: is such a big chunk, that we should cut down
	// TODO fix issue where large solid color chunks are needlessly broken down into smaller chunks
	if (_map.size() > pixelMapChunkMaxCount) {
		std::pair<int, int> medial((lowest.first + highest.first) / 2, (lowest.second + highest.second) / 2);

		std::map<std::pair<int, int>, Pixel> mapLL;
		std::map<std::pair<int, int>, Pixel> mapLG;
		std::map<std::pair<int, int>, Pixel> mapGL;
		std::map<std::pair<int, int>, Pixel> mapGG;

		// iterate through all pixels, send into one of 4 sub-models
		for (std::pair<std::pair<int, int>, Pixel> kv : _map) {
			if (kv.first.first < medial.first && kv.first.second < medial.second) {
				// case: pixel x < medial x and pixel y < medial y
				mapLL.emplace(kv.first, kv.second);
			}
			else if (kv.first.first < medial.first) {
				// case: pixel x < medial x and pixel y >= medial y
				mapLG.emplace(kv.first, kv.second);
			}
			else if (kv.first.second < medial.second) {
				// case: pixel x >= medial x and pixel y < medial y
				mapGL.emplace(kv.first, kv.second);
			}
			else {
				// case: pixel x >= medial x and pixel y >= medial y
				mapGG.emplace(kv.first, kv.second);
			}
		}

		// now spawn sub-models for each map
		// and register each sub-model
		for (auto subMap : {mapLL, mapLG, mapGL, mapGG}) {
			PixelMapModel subModel(subMap);
			subModels.push_back(subModel);
		}
	}

	// case: is an n-element pixel map
	else if (_map.size() > 1) {
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
