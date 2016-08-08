#ifndef GWIRIO_UTEST_HH
#define GWIRIO_UTEST_HH
#include <string>
#include <vector>
#include <memory>
namespace Gwirio {



class UTest
{
public:
   using String = std::string;
   using Fp = void (*)(void);
   class Run;
   UTest() = default;
   UTest(const UTest&) = delete;
   UTest& operator=(const UTest&) = delete;
   UTest(UTest&&) = delete;
   UTest& operator=(UTest&&) = delete;
   Run& add(const String& name, Fp in, Fp out);
   bool execute();
private:
   using List = std::vector<std::unique_ptr<Run>>;
   List _runs;
};



class UTest::Run
{
public:
   using String = UTest::String;
   using Fp = UTest::Fp;
   using Tfp = void (*)(Run&);
   struct Fail {};
   Run(const String& name, Fp in, Fp out);
   Run(const Run&) = delete;
   Run& operator=(const Run&) = delete;
   Run(Run&&) = delete;
   Run& operator=(Run&&) = delete;
   void add(const String& name, Tfp test);
   int execute();
   void next();
private:
   using Pair = std::pair<String,Tfp>;
   using List = std::vector<Pair>;
   String _name;
   Fp _in;
   Fp _out;
   List _tests;
   int _count {0};
   int _tCount {0};
};



}
#endif
