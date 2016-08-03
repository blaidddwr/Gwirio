#include "utest.h"
#include <iostream>
namespace Gwirio {



UTest::Run& UTest::add(const string& name, fp in, fp out)
{
   _runs.emplace_back(new Run(name,in,out));
   return *_runs.back();
}



bool UTest::execute()
{
   bool pass {true};
   int count {0};
   for (auto i = _runs.begin();i!=_runs.end();++i)
   {
      int tmp = (*i)->execute();
      if (tmp<0)
      {
         pass = false;
         break;
      }
      count += tmp;
   }
   if (pass)
   {
      std::cout << count << " unit test(s) passed.\n";
   }
   return pass;
}



UTest::Run::Run(const string& name, fp in, fp out):
   _name {name},
   _in {in},
   _out {out}
{}



void UTest::Run::add(const string& name, tfp test)
{
   _tests.emplace_back(pair(name,test));
}



int UTest::Run::execute()
{
   _tCount = 0;
   std::cout << _name;
   if (_in)
   {
      _in();
   }
   for (auto i = _tests.begin();i!=_tests.end();++i)
   {
      _count = 1;
      ++_tCount;
      std::cout << "." << std::flush;
      try
      {
         i->second(*this);
      }
      catch (...)
      {
         std::cout << "\n" << i->first << ":" << _count << " FAILED.\n";
         if (_out)
         {
            _out();
         }
         _tCount = -1;
         break;
      }
   }
   if (_tCount>=0)
   {
      if (_out)
      {
         _out();
      }
      std::cout << "\n";
   }
   return _tCount;
}



void UTest::Run::next()
{
   std::cout << "." << std::flush;
   ++_count;
   ++_tCount;
}



}
