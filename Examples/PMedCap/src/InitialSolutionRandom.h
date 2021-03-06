// OptFrame - Optimization Framework

// Copyright (C) 2009-2015
// http://optframe.sourceforge.net/
//
// This file is part of the OptFrame optimization framework. This framework
// is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License v3 as published by the
// Free Software Foundation.

// This framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License v3 for more details.

// You should have received a copy of the GNU Lesser General Public License v3
// along with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.

#ifndef PCAP_INITIALSOLUTION_RandomInitalSolution_HPP_
#define PCAP_INITIALSOLUTION_RandomInitalSolution_HPP_

#include <OptFrame/Constructive.hpp>
//#include "../../OptFrame/Util/TestSolution.hpp"
#include <OptFrame/RandGen.hpp>

#include "ProblemInstance.h"

#include "Representation.h"
#include "Solution.h"

#include "Evaluator.h"

#include <list>

#include <algorithm>
#include <stdlib.h>

using namespace std;
using namespace optframe;

class PCAPInitialSolutionRandom : public Constructive<SolutionPCAP>
{
private:
   PCAPProblemInstance& pPCAP;
   RandGen& rg;
   // Your private vars

public:
   PCAPInitialSolutionRandom(PCAPProblemInstance& _pPCAP, RandGen& _rg)
     : // If necessary, add more parameters
     pPCAP(_pPCAP)
     , rg(_rg)
   {
   }

   std::optional<SolutionPCAP> generateSolution(double timelimit) override
   {
      RepPCAP newRep;
      bool med[pPCAP.nCidades];
      for (int i = 0; i < pPCAP.nCidades; i++) {
         med[i] = false;
      }

      for (int i = 0; i < pPCAP.nMedianas; i++) {

         int x = rg.rand(pPCAP.nCidades);
         while (med[x] == true)
            x = rg.rand(pPCAP.nCidades);

         newRep.first.push_back(x);
      }

      for (int i = 0; i < pPCAP.nCidades; i++) {
         newRep.second.push_back(-1);

         for (int j = 0; j < pPCAP.nMedianas; j++) {
            if (i == newRep.first[j])
               newRep.second[i] = j;
         }

         if (newRep.second[i] == -1)
            newRep.second[i] = rg.rand(pPCAP.nMedianas);
      }

      return make_optional(SolutionPCAP(newRep));
   }
};

#endif /*PCAP_INITIALSOLUTION_RandomInitalSolution_HPP_*/
