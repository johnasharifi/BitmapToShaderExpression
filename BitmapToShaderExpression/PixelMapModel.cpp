#include "pch.h"
#include "PixelMapModel.h"

namespace {
	const int pixelMapChunkMaxCount = 16;
}

PixelMapModel::PixelMapModel(std::map<std::pair<int, int>, Pixel> _map)
{
	subModels = std::vector<PixelMapModel>();

	// check how many unique pixels will be in this map
	std::set<Pixel> pixelUniques;
	for (std::pair<std::pair<int, int>, Pixel> kv : _map) {
		pixelUniques.insert(kv.second);
	}

	// note the span of ij coordinates from lowest corner to highest corner
	std::pair<int, int> lowest = _map.begin()->first;
	std::pair<int, int> highest = _map.rbegin()->first;
	minx = lowest.first;
	miny = lowest.second;
	maxx = highest.first + 1;
	maxy = highest.second + 1;
	
	// case: is a large collection of exact same pixel
	if (pixelUniques.size() == 1) {
		// minxy / maxxy already set
		// just need to set my pixel
		m_Pixel = _map.begin()->second;
	}
	// case: is such a big chunk, that we should cut down
	else if (_map.size() > pixelMapChunkMaxCount) {
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
	else {
		for (std::pair<std::pair<int, int>, Pixel> kv : _map) {
			// create a map with just one pair - coord ij to Pixel ij
			std::map<std::pair<int, int>, Pixel> ijMap;
			ijMap.emplace(kv.first, kv.second);

			// create a model with just one value - ij
			PixelMapModel ijModel(ijMap);
			subModels.push_back(ijModel);
		}
	}
}

std::string PixelMapModel::getPixelSpan()
{
	const int digitPadSize = 3;
	std::ostringstream stringStream;

	stringStream <<
		std::setw(digitPadSize) << minx << " < x < " << std::setw(digitPadSize) << maxx <<
		", " <<
		std::setw(digitPadSize) << miny << " < y < " << std::setw(digitPadSize) << maxy <<
		": pixel " << (std::string) m_Pixel;

	return stringStream.str();
}

PixelMapModel::operator std::string() {
	std::ostringstream stringStream;

	if (subModels.size() == 0) {
		stringStream << getPixelSpan();
	}
	else {
		// case: have submodels. each submodel is a new line, tabbed in
		for (PixelMapModel elem : subModels) {
			stringStream << "\t" << (std::string) elem << std::endl;
		}
	}

	return stringStream.str();
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
