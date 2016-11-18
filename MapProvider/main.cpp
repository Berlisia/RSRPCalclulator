#include <iostream>
#include "IMapDataProvider.h"
#include "MapDataProvider.h"
#include <memory>

int main()
{
    std::shared_ptr<IMapDataProvider> MapDataProv = std::make_shared<MapDataProvider>();
    std::cout << MapDataProv->coutMediumHeightBetwenTwoPixels(std::pair<int, int>(0, 0), std::pair<int, int>(3000, 2000), 10000) << std::endl;
    std::cout << MapDataProv->coutMediumHeightBetwenTwoPixels(std::pair<int, int>(0, 0), std::pair<int, int>(3000, 2000), 1000) << std::endl;
    std::cout << MapDataProv->coutMediumHeightBetwenTwoPixels(std::pair<int, int>(0, 0), std::pair<int, int>(3000, 2000), 100) << std::endl;
    std::cout << MapDataProv->coutMediumHeightBetwenTwoPixels(std::pair<int, int>(0, 0), std::pair<int, int>(3000, 2000), 10) << std::endl;
    std::cout << MapDataProv->coutMediumHeightBetwenTwoPixels(std::pair<int, int>(0, 0), std::pair<int, int>(3000, 2000), 1) << std::endl;
}
