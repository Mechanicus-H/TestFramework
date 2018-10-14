#include <iostream>
#include <vector>
#include <exception>
#include <sstream>
#include <map>
#include <set>
using namespace std;

/////////////////////////////////

class TestRunner
{
private:
	int failCount = 0;
public:
	TestRunner();
	virtual ~TestRunner();

	template<typename TestFunc>
	void runTest(TestFunc func, const string& testName = "runTest");
};

// Utilites

template<typename T, typename U>
void AssertEqual(const T& t, const U& u, const string& hint = "");

void Assert(bool b, const string& hint = "");

template<typename T, typename U>
ostream& operator<<(ostream& os, const map<T, U>& m);

template <class T>
ostream& operator << (ostream& os, const set<T>& s);




/////////////////////////////////

int Add(int a, int b) { return a + b; }
int Mult(int a, int b) { return a * b; }

void testAdd()
{
	AssertEqual(Add(2, 2), 4, "Add");
}
void testMult()
{
	AssertEqual(Mult(2, 5), 10, "Mult");
}

void testAll()
{
	TestRunner tr;
	tr.runTest(testAdd, "Add");
	tr.runTest(testMult, "Mult");
}



int main()
{
	testAll();
	cout << "Back to the main\n";
	return 0;
}


//-----------------------------------------------


/////////////////////////////////
///////////////////////////////////////
TestRunner::TestRunner()
{
}
//-----------------------------------------------
template<typename TestFunc>
void TestRunner::runTest(TestFunc func, const string& testName)
{
	try
	{
		func();
		cerr << testName << ": OK\n";
	}
	catch (runtime_error &e)
	{
		failCount++;
		cerr << testName << " fail: " << e.what() << endl;
	}
}
//-----------------------------------------------
TestRunner::~TestRunner()
{
	if (failCount > 0)
	{
		cerr << failCount << " test failed. Terminate\n";
		exit(1);
	}
}
//-----------------------------------------------

//
//-----------------------------------------------
// Utilites

template<typename T, typename U>
void AssertEqual(const T& t, const U& u, const string& hint)
{
	if (t != u)
	{
		ostringstream out;
		out.setf(ios::boolalpha);
		out << "AssertEqual failed: " << t << " != " << u << ", Hint: " << hint;
		throw runtime_error(out.str());
	}
}
//-----------------------------------------------
void Assert(bool b, const string & hint)
{
	AssertEqual(b, true, hint);
}
//-----------------------------------------------
template<typename T, typename U>
ostream & operator<<(ostream & os, const map<T, U>& m)
{
	bool isFirst = true;
	os << "{ ";
	for (const auto& it : m)
	{
		if (!isFirst) os << ", ";
		os << "{" << it.first << " : " << it.second << "}";
		isFirst = false;
	}
	os << " }";
	return os;
}
//-----------------------------------------------
template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}
