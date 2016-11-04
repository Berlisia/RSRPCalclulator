#include <iostream>
#include "RuskiTest/rsrptestcase.h"
#include "RuskiTest/AntennaLossFileParserTest.h"
#include "Worker.h"
#include <ctime>

//#include <gtest/gtest.h>
using namespace std;


int main(int argc, char *argv[])
{
//    RsrpTestCase testRsrp;
//    testRsrp.rsrpCalculationTest();
    Worker worker;

    int start_s=clock();
    worker.doCalculation();
    int stop_s=clock();
    cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

    worker.listInCoutRSPR();


//    //gtest wariant
//    ::testing::InitGoogleTest(&argc, argv);
//      return RUN_ALL_TESTS();

      //return a.exec();
}
