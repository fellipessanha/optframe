// OptFrame - Optimization Framework

// Copyright (C) 2009, 2010, 2011
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

#ifndef OPTFRAME_ELITISM_HPP_
#define OPTFRAME_ELITISM_HPP_

#include "../../Solution.hpp"
#include "../../Evaluation.hpp"

#include "../../Population.hpp"

namespace optframe
{

template<XESolution XES, XEvaluation XEv = Evaluation<>>
class Elitism
{
protected:

   typedef S chromossome;
   //typedef vector<chromossome*> Population;
   typedef vector<Evaluation<>*> FitnessValues;

public:

   virtual Population<S, XEv> & doElitism(const Population<S, XEv> &p, const FitnessValues& fv_p, unsigned popElitistSize) const = 0;

};

}

#endif /*OPTFRAME_ELITISM_HPP_*/
