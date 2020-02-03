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

#ifndef OPTFRAME_DECODER_RANDOM_KEYS_HPP_
#define OPTFRAME_DECODER_RANDOM_KEYS_HPP_

#include "../../Evaluation.hpp"
#include "../../Evaluator.hpp"
#include "../../Solution.hpp"
#include "../../Solutions/CopySolution.hpp"

namespace optframe {

typedef vector<double> random_keys;

template<Representation R>
class DecoderRandomKeys
{
public:
   virtual ~DecoderRandomKeys()
   {
   }

   virtual pair<Evaluation<>, CopySolution<R>*> decode(const random_keys& rk) = 0;

   virtual bool isMinimization() const = 0;
};

// ========================================================
// Basic implementation to use class Evaluator<random_keys>
// ========================================================

template<Representation R>
class DecoderRandomKeysEvaluator : public DecoderRandomKeys<R>
{
public:

   //using RKEvaluator = Evaluator<random_keys, OPTFRAME_DEFAULT_ADS, CopySolution<random_keys,OPTFRAME_DEFAULT_ADS>;

   Evaluator<random_keys>& evaluator;

   DecoderRandomKeysEvaluator(Evaluator<random_keys>& _evaluator)
     : evaluator(_evaluator)
   {
   }

   virtual ~DecoderRandomKeysEvaluator()
   {
   }

   virtual pair<Evaluation<>, CopySolution<R>*> decode(const random_keys& rk) override
   {
      return pair<Evaluation<>, CopySolution<R>*>(evaluator.evaluate(rk, nullptr), nullptr);
   }

   virtual bool isMinimization() const
   {
      return evaluator.isMinimization();
   }
};

class EvaluatorPermutationRandomKeys : public DecoderRandomKeys<vector<int>>
{
public:
   Evaluator<vector<int>>& ev; // evaluator for permutation
   int a, b;                   // decode in interval [a,b]

   EvaluatorPermutationRandomKeys(Evaluator<vector<int>>& _ev, int _a, int _b)
     : ev(_ev)
     , a(_a)
     , b(_b)
   {
      assert(a <= b);
   }

   virtual pair<Evaluation<>, CopySolution<vector<int>>*> decode(const random_keys& rk) override
   {
      int sz = b - a + 1;
      vector<pair<double, int>> v(sz);
      int k = 0;
      for (int i = a; i <= b; i++, k++)
         v[k] = pair<double, int>(rk[i], k);

      sort(v.begin(), v.end(), [](const pair<double, int>& i, const pair<double, int>& j) -> bool {
         return i.first < j.first;
      });

      vector<int> p(v.size());
      for (unsigned i = 0; i < v.size(); i++)
         p[i] = v[i].second;

      Evaluation<> e = ev.evaluate(p, nullptr);

      // you have the option to actually return a Solution<vector<int>> for post-decoding purposes
      return pair<Evaluation<>, CopySolution<vector<int>>*>(e, new CopySolution<vector<int>>(p));
   }

   virtual bool isMinimization() const
   {
      return ev.isMinimization();
   }
};

class EvaluatorSubsetRandomKeys : public DecoderRandomKeys<vector<bool>>
{
public:
   Evaluator<vector<bool>>& ev; // evaluator for permutation
   int a, b;                    // decode in interval [a,b]
   double limit;                // limit to decide membership (default=0.5)

   EvaluatorSubsetRandomKeys(Evaluator<vector<bool>>& _ev, int _a, int _b, double _limit = 0.5)
     : ev(_ev)
     , a(_a)
     , b(_b)
     , limit(_limit)
   {
      assert(a <= b);
   }

   virtual pair<Evaluation<>, CopySolution<vector<bool>>*> decode(const random_keys& rk) override
   {
      vector<bool> v(b - a + 1);
      for (unsigned i = 0; i < v.size(); i++)
         v[i] = rk[i] >= limit;

      Evaluation e = ev.evaluate(v, nullptr);

      // you have the option to actually return a Solution<vector<bool>> for post-decoding purposes
      return pair<Evaluation<>&, CopySolution<vector<bool>>*>(e, nullptr);
   }

   virtual bool isMinimization() const
   {
      return ev.isMinimization();
   }
};
}

#endif /*OPTFRAME_DECODER_RANDOM_KEYS_HPP_*/
