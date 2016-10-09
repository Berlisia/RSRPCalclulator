#ifndef RSRPINITIALIZATION_H
#define RSRPINITIALIZATION_H
#include <map>


class RsrpInitialization
{
public:
    RsrpInitialization();

    int getNumberOfSubcarriersInBlock();
    int getNumberOfResourceBlocks(double bandwith);

private:
     const std::map<double,int> numberOfResourceBlocks;
     const int numberOfSubcarriersInBlock;
};

#endif // RSRPINITIALIZATION_H
