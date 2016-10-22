#ifndef IMAPDATAPROVIDERMOCK_H
#define IMAPDATAPROVIDERMOCK_H
#include <gmock/gmock.h>
#include "MapProvider/IMapDataProvider.h"

class IMapDataProviderMock : public IMapDataProvider
{
    MOCK_METHOD1(pixelHeight, unsigned int(std::pair<int,int>));
    MOCK_METHOD2(coutDistance, float(std::pair<int,int>,std::pair<int,int>));
};

#endif // IMAPDATAPROVIDERMOCK_H
