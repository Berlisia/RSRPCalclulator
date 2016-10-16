#include <iostream>
#include "IMapDataProvider.h"
#include "MapDataProvider.h"
#include <memory>

int main()
{
    std::shared_ptr<IMapDataProvider> MapDataProv = std::make_shared<MapDataProvider>();
}
