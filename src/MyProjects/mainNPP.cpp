// ===================================
// Main.cpp file generated by OptFrame
// Project NumberPartitionProblem
// ===================================

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "../OptFrame/Util/RandGenMersenneTwister.hpp"

#include "../OptFrame/Util/CheckCommand.hpp"

#include "NPP.h"

using namespace std;
using namespace optframe;
using namespace NPP;

int main(int argc, char **argv)
{
   RandGenMersenneTwister rg; // not using system rand() anymore
   
   // Initialize here all your OptFrame components 
   // (ProblemInstance, Evaluator, Constructive, ...)

   auto *ifs = new std::ifstream("example.in", std::ifstream::in);
   Scanner scanner(ifs);
   ProblemInstance p(scanner);

   MyEvaluator ev(p);

   NSSeq2Opt ns1(p, rg);
   NSSeqSwap ns2(p, rg);

   ConstructiveGreedy c1(p);
   ConstructiveRand c2(p);

   CheckCommand<RepNPP> check;
   check.add(ev);
   check.add(c1);
   check.add(c2);
   check.add(ns1);
   check.add(ns2);

   check.run(10,10);

   cout << "Program ended successfully" << endl;
   ifs->close();
   
   return 0;
}
