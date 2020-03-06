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

#ifndef OPTFRAME_OPTIMIZATION_DIRECTION_HPP_
#define OPTFRAME_OPTIMIZATION_DIRECTION_HPP_

#include <float.h>
#include <limits>
#include <iostream>
#include <assert.h>

#include "Solution.hpp"
#include "ADSManager.hpp"
#include "Evaluation.hpp"
#include "Move.hpp"
#include "MoveCost.hpp"


#include "Component.hpp"
#include "Action.hpp"
#include "BaseConcepts.hpp" // Base concepts

using namespace std;
using namespace scannerpp;

namespace optframe
{

// Direction 'betterThan' depends on a 'totally_ordered' type
////template<optframe::totally_ordered ObjType = evtype, XEvaluation XEv = Evaluation<ObjType>>
class Direction: public Component
{
protected:
	///MoveCost<evtype, Evaluation<>> nullCost;
   Evaluation<evtype> nullCost;

public:

	Direction() :
			///nullCost(MoveCost<>(0))
         nullCost(Evaluation<>(0))
   {
	}
   

	virtual ~Direction()
	{
	}

	// ============ betterThan ===========

	//! abstract method betterThan: true when a < b for minimization problems; and true when a > b for maximization problems.
	/*!
	 betterThan is the method in OptFrame used to guide the search methods into the solution space.
	 with betterThan the search methods are able to compare good and poor solutions, in one of the two directions: minimization and maximization.
	 It must be implemented by the final user in one of these ways:
	 - for minimization problems, returns a < b;
	 - for maximization problems, returns a > b.
	 */
	//virtual bool betterThan(evtype a, evtype b) = 0;

	// true if 'mc1' is better than 'mc2'
	virtual inline bool betterThan(const MoveCost<>& mc1, const MoveCost<>& mc2)
	{
		if(isMinimization())
			return (mc2.cost() - mc1.cost()) >= optframe::get_numeric_zero<evtype>();
		else
			return (mc1.cost() - mc2.cost()) >= optframe::get_numeric_zero<evtype>();
	}

	// true if 'e1' is better than 'e2'
	virtual inline bool betterThan(const Evaluation<>& e1, const Evaluation<>& e2)
	{
      //cout << "BETTER THAN! (isMin=" << isMinimization() << ")" << endl;
      //e1.print();
      //e2.print();

      //bool r = true;

      evtype diff;
		if(isMinimization())
      {
         diff = e2.evaluation() - e1.evaluation();
			//r = (e2.evaluation() - e1.evaluation()) >= optframe::get_numeric_zero<evtype>();
      }
		else
      {
         diff = e1.evaluation() - e2.evaluation();
			//r = (e1.evaluation() - e2.evaluation()) >= optframe::get_numeric_zero<evtype>();
      }
      bool r = !(optframe::numeric_is_zero<evtype>(diff)) && (diff > optframe::get_numeric_zero<evtype>());

      //printf("r=%d e1=%.7f e2=%.7f zero=%.7f nzero=%.7f\n",r,e1.evaluation(), e2.evaluation(), optframe::get_numeric_zero<evtype>(), t);
      
      return r;
	}

	/*
	virtual inline bool betterThan(const vector<pair<evtype, evtype> >& altCosts1, const vector<pair<evtype, evtype> >& altCosts2)
	{
		if(altCosts1.size() != altCosts2.size())
			return false;
		for(unsigned i = 0; i < altCosts1.size(); i++)
			if(!betterThan(altCosts1[i].first + altCosts1[i].second, altCosts2[i].first + altCosts2[i].second))
				return false;
		return true;
	}
	*/

	// ============ betterOrEquals ===========

	/*
	inline bool betterOrEquals(const vector<pair<evtype, evtype> >& altCosts1, const vector<pair<evtype, evtype> >& altCosts2)
	{
		return betterThan(altCosts1, altCosts2) || equals(altCosts1, altCosts2);
	}
	*/


// abolishing MoveCost
/*
	inline bool betterOrEquals(const MoveCost<>& mc1, const MoveCost<>& mc2)
	{
		return betterThan(mc1, mc2) || equals(mc1, mc2);
	}
*/

	inline bool betterOrEquals(const Evaluation<>& e1, const Evaluation<>& e2)
	{
		return betterThan(e1, e2) || equals(e1, e2);
	}

	/*
	inline bool betterOrEquals(evtype a, evtype b)
	{
		return betterThan(a, b) || equals(a, b);
	}
	*/

	// ============ equals ============

protected:
/*
	virtual inline bool equals(const evtype& t1, const evtype& t2, const vector<pair<evtype, evtype> >& altCosts1, const vector<pair<evtype, evtype> >& altCosts2)
	{
      if(optframe::numeric_is_zero<evtype>(t1 - t2))
		//if(EVALUATION_ABS(t1 - t2) <= optframe::get_numeric_zero<evtype>()) // deprecated
			return true;

		if(t1 != t2)
			return false;

		assert(altCosts1.size() == altCosts2.size());

		for(unsigned i = 0; i < altCosts1.size(); i++)
			if((altCosts1[i].first + altCosts1[i].second) != (altCosts2[i].first + altCosts2[i].second))
				return false;

		return true;
	}
*/   

virtual inline bool equals(const evtype& t1, const evtype& t2)
	{
      if(optframe::numeric_is_zero<evtype>(t1 - t2))
		//if(EVALUATION_ABS(t1 - t2) <= optframe::get_numeric_zero<evtype>()) // deprecated
			return true;

		if(t1 != t2)
			return false;

		//assert(altCosts1.size() == altCosts2.size());

		//for(unsigned i = 0; i < altCosts1.size(); i++)
		//	if((altCosts1[i].first + altCosts1[i].second) != (altCosts2[i].first + altCosts2[i].second))
		//		return false;

		return true;
	}

public:

// Abolishing MoveCost
/*
	virtual inline bool equals(const MoveCost<>& mc1, const MoveCost<>& mc2)
	{
		return equals(mc1.cost(), mc2.cost(), mc1.getAlternativeCosts(), mc2.getAlternativeCosts());
	}
*/
	virtual inline bool equals(const Evaluation<>& e1, const Evaluation<>& e2)
	{
		//return equals(e1.evaluation(), e2.evaluation(), e1.getAlternativeCosts(), e2.getAlternativeCosts());
      return equals(e1.evaluation(), e2.evaluation());
	}




	/*
	virtual inline bool equals(evtype a, evtype b)
	{
		return (::abs(a - b) < OPTFRAME_EPSILON);
	}
	*/

	// ============= improvement =============

	///virtual bool isImprovement(const MoveCost<>& mc, const Evaluation<>& e1, const Evaluation<>& e2)
   virtual bool isImprovement(const Evaluation<>& mc, const Evaluation<>& e1, const Evaluation<>& e2)
	{
		//evtype ec1 = mc.cost() + e1.evaluation();
      evtype ec1 = mc.evaluation() + e1.evaluation();

		//if(isMinimization()  && (e2.evaluation() - ec1) >= EVALUATION_ZERO) // deprecated
      if(isMinimization()  && (e2.evaluation() - ec1) >= optframe::get_numeric_zero<evtype>())
			return true;

		//if(!isMinimization() && (ec1 - e2.evaluation()) >= EVALUATION_ZERO) // deprecated
      if(!isMinimization() && (ec1 - e2.evaluation()) >= optframe::get_numeric_zero<evtype>())
			return true;

		return false;
	}


	///virtual inline bool isImprovement(const MoveCost<>& mc)
   virtual inline bool isImprovement(const Evaluation<>& mc)
	{
		return betterThan(mc, nullCost);
	}


	// ============= direction ==============

	virtual bool isMinimization() const = 0;

	inline bool isMaximization() const
	{
		return !isMinimization();
	}

	// ============ estimation =============

   inline evtype ideal()
	{
		if(isMinimization())
			return min();
		else
			return max();
	}

	//inline evtype worst()
   inline evtype nadir()
	{
		if(isMinimization())
			return max();
		else
			return min();
	}



	// bad approximation!
	virtual inline evtype min()
	{
		////return -DBL_MAX;

		if(numeric_limits<evtype>::has_infinity)
			return -numeric_limits<evtype>::infinity();
		else
			return -numeric_limits<evtype>::max();
	}

	// bad approximation!
	virtual inline evtype max()
	{
		////return DBL_MAX;

		if(numeric_limits<evtype>::has_infinity)
			return numeric_limits<evtype>::infinity();
		else
			return numeric_limits<evtype>::max();
	}

	// ============= Component ===============

	virtual bool compatible(string s)
	{
		return (s == idComponent()) || (Component::compatible(s));
	}

	static string idComponent()
	{
		stringstream ss;
		ss << Component::idComponent() << "Direction";
		return ss.str();
	}

	virtual string id() const
	{
		return idComponent();
	}

	virtual string toString() const
	{
		if(isMinimization())
			return "Direction:MIN";
		else
			return "Direction:MAX";
	}

	virtual void print() const
	{
		cout << toString() << endl;
	}

};

//template<optframe::totally_ordered ObjType = evtype, XEvaluation XEv = Evaluation<ObjType>>
//class Minimization: public Direction<ObjType, XEv>
class Minimization: public Direction
{
public:

	virtual ~Minimization()
	{
	}

	/*
	inline bool betterThan(evtype f1, evtype f2)
	{
		// MINIMIZATION
		return (f1 < (f2 - OPTFRAME_EPSILON));
	}*/

	inline bool isMinimization() const
	{
		return true;
	}
};

//template<optframe::totally_ordered ObjType = evtype, XEvaluation XEv = Evaluation<ObjType>>
//class Maximization: public Direction<ObjType, XEv>
class Maximization: public Direction
{
public:

	virtual ~Maximization()
	{
	}

	/*
	inline bool betterThan(evtype f1, evtype f2)
	{
		// MAXIMIZATION
		return (f1 > (f2 + OPTFRAME_EPSILON));
	}*/

	inline bool isMinimization() const
	{
		return false;
	}
};

} // namespace optframe

#endif /*OPTFRAME_OPTIMIZATION_DIRECTION_HPP_*/
