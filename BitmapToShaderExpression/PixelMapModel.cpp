#include "pch.h"
#include "PixelMapModel.h"

namespace {
	const int pixelMapChunkMaxCount = 32;
}

bool isFirstDimUniform(const std::pair<int, int> &init, const std::map<std::pair<int, int>, Pixel>& map, int span) {
	Pixel initValue = map.at(init);
	for (int i = init.first; i < init.first + span; ++i) {
		std::pair<int, int> ij = std::pair<int, int>(i, init.second);
		// if not in map, or a mismatch in R/G/B, return false
		if (map.count(ij) == 0) {
			return false;
		}
		if (!(initValue &= map.at(ij))) {
			Pixel p = map.at(ij);
			return false;
		}
	}
	// must all match
	return true;
}

std::pair<int, int> getSpanFrom(const std::pair<int, int> &init, const std::map<std::pair<int, int>, Pixel>& map) {
	const int max = 8;

	int maxi = 0;
	int maxj = 0;

	while (isFirstDimUniform(init, map, maxi + 1)) {
		++maxi;
	}

	return std::pair<int, int>(init.first + maxi, init.second);
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
		// first case: take up as much space from first index, as possible, in single sub-map
		std::pair<int, int> ijStart = _map.begin()->first;
		std::pair<int, int> ijEnd = getSpanFrom(ijStart, _map);
		std::cout << "\tconsolidate span from " << ijStart.first << ", " << ijStart.second << " to " << ijEnd.first << ", " << ijEnd.second << " as single map of pixel " << (std::string) _map.begin()->second << std::endl;

		// fallback - add additional maps
		for (std::pair<std::pair<int, int>, Pixel> kv : _map) {
			// create a map with just one pair - coord ij to Pixel ij
			std::map<std::pair<int, int>, Pixel> ijMap;
			ijMap.emplace(kv.first, kv.second);

			std::pair<int, int> result = getSpanFrom(kv.first, _map);
			
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
		stringStream << getPixelSpan() << std::endl;

		// case: have submodels. each submodel is a new line, tabbed in
		for (PixelMapModel elem : subModels) {
			std::stringstream ssElem((std::string) elem);
			std::string holder;
			// split the child's string content on newline
			while (std::getline(ssElem, holder, '\n')) {
				// shift all of the child steams over by 1 tab
				stringStream << "\t" << holder << std::endl;
			}
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
