/* file QuaternionOperatorUT.h
 * 
 * Copyright (c) Nikos Kazazakis, 2016
 *
 * \brief Define class QuaternionOperatorUT for unit testing of Quaternion operators
 * \author Nikos Kazazakis
 */

#ifndef QUATERNION_OPERATOR_UT_H
#define QUATERNION_OPERATOR_UT_H

#include <cppunit/TestCase.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Quaternion.h"
//
using namespace Quaternions;

class QuaternionOperatorUT : public CppUnit::TestCase {
public:
	// Default constructor
	QuaternionOperatorUT(std::string name) : CppUnit::TestCase(name){}
	QuaternionOperatorUT(){}

	void myTest();
	void setUp() { }      // need not implement
	void tearDown() { }   // need not implement

//    void run(TestResult *result);

//    std::string getName() const;

    //! FIXME: this should probably be pure virtual.
//    virtual void runTest();


	// Define CPP test suite
	CPPUNIT_TEST_SUITE(QuaternionOperatorUT);
	CPPUNIT_TEST(myTest);
	CPPUNIT_TEST_SUITE_END();

private:

};

#endif // End of macro
