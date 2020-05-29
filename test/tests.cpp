/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_CircbufTestSuite_init = false;
#include "/home/mash/src/c/circbuf.git/test/circbuf_test.hpp"

static CircbufTestSuite suite_CircbufTestSuite;

static CxxTest::List Tests_CircbufTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CircbufTestSuite( "test/circbuf_test.hpp", 6, "CircbufTestSuite", suite_CircbufTestSuite, Tests_CircbufTestSuite );

static class TestDescription_suite_CircbufTestSuite_test_circbuf_head_forward : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CircbufTestSuite_test_circbuf_head_forward() : CxxTest::RealTestDescription( Tests_CircbufTestSuite, suiteDescription_CircbufTestSuite, 28, "test_circbuf_head_forward" ) {}
 void runTest() { suite_CircbufTestSuite.test_circbuf_head_forward(); }
} testDescription_suite_CircbufTestSuite_test_circbuf_head_forward;

static class TestDescription_suite_CircbufTestSuite_test_circbuf_head_forward_error : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CircbufTestSuite_test_circbuf_head_forward_error() : CxxTest::RealTestDescription( Tests_CircbufTestSuite, suiteDescription_CircbufTestSuite, 68, "test_circbuf_head_forward_error" ) {}
 void runTest() { suite_CircbufTestSuite.test_circbuf_head_forward_error(); }
} testDescription_suite_CircbufTestSuite_test_circbuf_head_forward_error;

static class TestDescription_suite_CircbufTestSuite_test_circbuf_create : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CircbufTestSuite_test_circbuf_create() : CxxTest::RealTestDescription( Tests_CircbufTestSuite, suiteDescription_CircbufTestSuite, 80, "test_circbuf_create" ) {}
 void runTest() { suite_CircbufTestSuite.test_circbuf_create(); }
} testDescription_suite_CircbufTestSuite_test_circbuf_create;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
