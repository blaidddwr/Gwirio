#include "utest.h"
#include "../src/gwirio.h"
#include <iostream>



using namespace gwr;



int gCount {0};



void infunc(void)
{
   ++gCount;
}



void outfunc(void)
{
   gCount+=2;
}



void testfunc1(UTest::Run& rn)
{
   gCount+=4;
}



void testfunc2(UTest::Run& rn)
{
   gCount+=8;
}



void testfunc3(UTest::Run& rn)
{
   rn.next();
   rn.next();
   throw int(-1);
   gCount = 0;
}



void utest()
{
   {
      UTest test;
      UTest::Run& run {test.add("Test Run",infunc,outfunc)};
      run.add("Test1",testfunc1);
      run.add("Test2",testfunc2);
      bool pass {test.execute()};
      if (gCount!=15||!pass)
      {
         std::cout << "\n\nUNIT TESTING FAILED!\n";
         exit(1);
      }
   }
   {
      gCount = 0;
      UTest test;
      UTest::Run& run {test.add("Test Run",infunc,outfunc)};
      run.add("Test1",testfunc1);
      run.add("Test2",testfunc2);
      UTest::Run& sRun {test.add("Second Test Run",nullptr,outfunc)};
      sRun.add("Test2",testfunc2);
      bool pass {test.execute()};
      if (gCount!=25||!pass)
      {
         std::cout << "\n\nUNIT TESTING FAILED!\n";
         exit(1);
      }
   }
   {
      gCount = 0;
      UTest test;
      UTest::Run& run {test.add("Test Run",infunc,outfunc)};
      run.add("Test1",testfunc1);
      run.add("Test2",testfunc2);
      UTest::Run& sRun {test.add("Second Test Run",nullptr,nullptr)};
      sRun.add("Test2",testfunc2);
      bool pass {test.execute()};
      if (gCount!=23||!pass)
      {
         std::cout << "\n\nUNIT TESTING FAILED!\n";
         exit(1);
      }
   }
   {
      gCount = 0;
      UTest test;
      UTest::Run& run {test.add("Test Run",infunc,outfunc)};
      run.add("Test1",testfunc1);
      run.add("Test2",testfunc2);
      UTest::Run& sRun {test.add("Second Test Run",nullptr,outfunc)};
      sRun.add("Test1",testfunc1);
      sRun.add("Test2",testfunc2);
      sRun.add("Test3",testfunc3);
      sRun.add("Test4",testfunc1);
      bool pass;
      try
      {
         pass = test.execute();
      }
      catch (int)
      {}
      if (gCount!=29||pass)
      {
         std::cout << gCount << "\n\nUNIT TESTING FAILED!\n";
         exit(1);
      }
   }
   {
      gCount = 0;
      UTest test;
      UTest::Run& run {test.add("Test Run",infunc,outfunc)};
      run.add("Test1",testfunc1);
      run.add("Test2",testfunc2);
      UTest::Run& sRun {test.add("Second Test Run",nullptr,nullptr)};
      sRun.add("Test1",testfunc1);
      sRun.add("Test2",testfunc2);
      sRun.add("Test3",testfunc3);
      sRun.add("Test4",testfunc1);
      bool pass;
      try
      {
         pass = test.execute();
      }
      catch (int)
      {}
      if (gCount!=27||pass)
      {
         std::cout << gCount << "\n\nUNIT TESTING FAILED!\n";
         exit(1);
      }
   }
}
