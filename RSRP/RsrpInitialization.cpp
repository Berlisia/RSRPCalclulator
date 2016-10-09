#include "RsrpInitialization.h"

RsrpInitialization::RsrpInitialization() :
    numberOfResourceBlocks
    {
        {1.4,  6},
        {3.0,  15},
        {5.0,  25},
        {10.0, 50},
        {15.0, 75},
        {20.0, 100}
    },
    numberOfSubcarriersInBlock(12)
{
}

int RsrpInitialization::getNumberOfSubcarriersInBlock()
{
    return numberOfSubcarriersInBlock;
}

int RsrpInitialization::getNumberOfResourceBlocks(double bandwith)
{
    int numberOfBlocks = 0;
    const auto & resourceBlocks = numberOfResourceBlocks.find(bandwith);
    if(resourceBlocks != numberOfResourceBlocks.end())
    {
        numberOfBlocks = resourceBlocks->second;
    }
    return numberOfBlocks;
}
