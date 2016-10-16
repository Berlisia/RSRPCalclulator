#include <iostream>
#include "RuskiTest/rsrptestcase.h"
#include "RuskiTest/AntennaLossFileParserTest.h"
#include <gtest/gtest.h>
using namespace std;

int main(int argc, char *argv[])
{
    //RsrpTestCase testRsrp;
    //testRsrp.rsrpCalculationTest();
    //AntennaLossFileParserTest parserTest;

    //gtest wariant
    ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
}
