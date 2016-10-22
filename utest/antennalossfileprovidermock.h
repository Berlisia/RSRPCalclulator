#ifndef ANTENNALOSSFILEPROVIDERMOCK_H
#define ANTENNALOSSFILEPROVIDERMOCK_H
#include <gmock/gmock.h>
#include "AntennaLoss/IAntennaLossFileProvider.h"

class AntennaLossFileProviderMock : public IAntennaLossFileProvider
{
    MOCK_METHOD2(getLossFromFile, float(int, Charakteristic));
};

#endif // ANTENNALOSSFILEPROVIDERMOCK_H
