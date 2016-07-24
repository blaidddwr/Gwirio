#ifndef GWR_UTEST_HH
#define GWR_UTEST_HH
#include <string>
#include <vector>
#include <memory>
namespace gwr {



class UTest
{
public:
   using string = std::string;
   using fp = void (*)(void);
   class Run;
   UTest() = default;
   UTest(const UTest&) = delete;
   UTest& operator=(const UTest&) = delete;
   UTest(UTest&&) = delete;
   UTest& operator=(UTest&&) = delete;
   Run& add(const string& name, fp in, fp out);
   bool execute();
private:
   using list = std::vector<std::unique_ptr<Run>>;
   list _runs;
};



class UTest::Run
{
public:
   using string = std::string;
   using fp = UTest::fp;
   using tfp = void (*)(Run&);
   struct Fail {};
   Run(const string& name, fp in, fp out);
   Run(const Run&) = delete;
   Run& operator=(const Run&) = delete;
   Run(Run&&) = delete;
   Run& operator=(Run&&) = delete;
   void add(const string& name, tfp test);
   int execute();
   void next();
private:
   using pair = std::pair<std::string,void(*)(Run&)>;
   using list = std::vector<pair>;
   string _name;
   fp _in;
   fp _out;
   list _tests;
   int _count {0};
   int _tCount {0};
};



}
#endif
