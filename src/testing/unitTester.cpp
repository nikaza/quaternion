/*
 * unitTester.cpp
 *
 * \brief Main Unit Tester program for the quaternion library
 * \author Nikos Kazazakis
 */

#define CATCH_CONFIG_MAIN
#include "Quaternion.h"
#include <catch.hpp>

using namespace Quaternions;
TEST_CASE("Test quaternion comparison operators"){

	// Initialize test quaternions
	Quaternion q = Quaternion(1,1,1,1);
	Quaternion q1 = Quaternion(1,1,1,1);
	Quaternion q2 = Quaternion(0,1,1,1);

	Quaternion qPartial;
	qPartial[qw]=2.0;

	// Require true
	REQUIRE(q==q1); // Require true
	REQUIRE((q!=q2)); // Require true

	// Require false
	REQUIRE(!(q==q2)); // Require false
	REQUIRE(!(q!=q1)); // Require false
	REQUIRE((qPartial!=q2)); // Require false
	// - Add another element, then test again
	qPartial[qj]=3.0;
	REQUIRE((qPartial!=q2)); // Require false
}

TEST_CASE("Test quaternion multiplication"){
	Quaternion q = Quaternion(1,0,1,0);
	Quaternion q1 = Quaternion(1,0.5,0.5,0.75);
	double myDouble = 2.0;
	int myInt = 2;

	// Require true
	REQUIRE((q*q1==Quaternion(0.5, 1.25, 1.5, 0.25)));
	REQUIRE(( (myDouble*q1)==Quaternion(2, 1, 1, 1.5)));
	REQUIRE(( (q1*myDouble)==Quaternion(2, 1, 1, 1.5)));
	REQUIRE(( (q1*myInt)==Quaternion(2, 1, 1, 1.5)));
	REQUIRE(( (myInt*q1)==Quaternion(2, 1, 1, 1.5)));
}

TEST_CASE("Test quaternion addition and subtraction"){
	Quaternion q = Quaternion(1,0,1,0);
	Quaternion q1 = Quaternion(1,0.5,0.5,0.75);
	double myDouble = 2.0;
	int myInt = 2;

	// Require true
	REQUIRE(q+q1==Quaternion(2, 0.5, 1.5, 0.75));
	REQUIRE(q-q1==Quaternion(0, -0.5, 0.5, -0.75));

	REQUIRE(myDouble+q1==Quaternion(3, 2.5, 2.5, 2.75));
	REQUIRE(myDouble-q1==Quaternion(1, 1.5, 1.5, 1.25));

	REQUIRE(myInt+q1==Quaternion(3, 2.5, 2.5, 2.75));
	REQUIRE(myInt-q1==Quaternion(1, 1.5, 1.5, 1.25));

	REQUIRE(q1+myDouble==Quaternion(3, 2.5, 2.5, 2.75));
	REQUIRE(q1-myDouble==Quaternion(-1, -1.5, -1.5, -1.25));

	REQUIRE(q1+myInt==Quaternion(3, 2.5, 2.5, 2.75));
	REQUIRE(q1-myInt==Quaternion(-1, -1.5, -1.5, -1.25));
}

TEST_CASE("Test quaternion misc methods"){
	Quaternion q = Quaternion(1,2,2,1);

	REQUIRE(q.norm()==std::sqrt(1+4+4+1));
	REQUIRE(q.conjugate()==Quaternion(1,-2,-2,-1));
}

TEST_CASE("Test quaternion math chaining"){
	Quaternion q = Quaternion(-1,-2,-1,-2);
	Quaternion q1 = Quaternion(1,0.5,0.5,0.75);

	REQUIRE( (2+q)*q1+2.25 == Quaternion(2.75, 3.5, 3.75, 2.5));
	REQUIRE( 2.25+(q+2)*q1 == Quaternion(2.75, 3.5, 3.75, 2.5));

}
