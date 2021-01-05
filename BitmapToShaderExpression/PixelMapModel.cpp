#include "pch.h"
#include "PixelMapModel.h"

PixelMapModel::PixelMapModel(std::map<std::pair<int, int>, Pixel> _map)
{
	subModels = std::vector<PixelMapModel>();

	for (std::pair<std::pair<int, int>, Pixel> kv : _map) {
		std::cout << "index " << kv.first.first << "," << kv.first.second << " has value " << (std::string) kv.second << std::endl;
	}


}

PixelMapModel::~PixelMapModel()
{
}

bool PixelMapModel::Contains(std::pair<int, int> ijCoord)
{
	return false;
}

Pixel PixelMapModel::GetPixel(std::pair<int, int> ijCoord)
{
	return Pixel();
}
