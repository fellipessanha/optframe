#include <catch2/catch.hpp>
// Some instructions for Catch2
// https://github.com/catchorg/Catch2/blob/master/docs/test-cases-and-sections.md

// system
#include <limits>

// core includes
#include <TSP2/src/ConstructiveNearestNeighbor.h>
#include <TSP2/TSP2.h>

using namespace std;
//using namespace optframe;

// basics

// =======================
// memory management tests
// =======================

TEST_CASE("ExamplesTSP2Tests : Matrix_Is_Zero")
{
   //BigInteger big;
   //EXPECT_EQ(big.Length(), 1);
   Matrix<int> m(1);
   REQUIRE(m.getNumRows() == 1);
}