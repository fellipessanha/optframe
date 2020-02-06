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

#ifndef OPTFRAME_SINGLE_OBJ_SEARCH_TO_LOCAL_SEARCH_HPP_
#define OPTFRAME_SINGLE_OBJ_SEARCH_TO_LOCAL_SEARCH_HPP_

#include <math.h>
#include <vector>

#include "../Constructive.hpp"
#include "../Evaluation.hpp"
#include "../Evaluator.hpp"
#include "../LocalSearch.hpp"
#include "../SingleObjSearch.hpp"

namespace optframe {

template<XSolution S, XEvaluation XEv=Evaluation<>>
class SingleObjSearchToLocalSearch : public LocalSearch<S, XEv>
{
protected:
   Evaluator<S, XEv>& evaluator;
   SingleObjSearch<S, XEv>& sios;

public:
   SingleObjSearchToLocalSearch(Evaluator<S, XEv>& _evaluator, SingleObjSearch<S, XEv>& _sios)
     : evaluator(_evaluator)
     , sios(_sios)
   {
   }

   virtual ~SingleObjSearchToLocalSearch()
   {
   }

   virtual void exec(S& s, SOSC& sosc) override
   {
      Evaluation<> e = evaluator.evaluateSolution(s);

      exec(s, e, sosc);
   }

   virtual void exec(S& s, Evaluation<>& e, SOSC& sosc) override
   {
      pair<S, Evaluation<>>* r = sios.search(sosc, &s, &e);

      if (r) {
         s = r->first;
         e = r->second;
         delete r;
      }
   }

   virtual bool compatible(string s)
   {
      return (s == idComponent()) || (LocalSearch<S, XEv>::compatible(s));
   }

   static string idComponent()
   {
      stringstream ss;
      ss << SingleObjSearch<S, XEv>::idComponent() << "SingleObjSearchToLocalSearch";
      return ss.str();
   }

   virtual string id() const
   {
      return idComponent();
   }

   virtual void print() const
   {
      cout << "SingleObjSearchToLocalSearch with sios: ";
      sios.print();
   }
};

template<XSolution S, XEvaluation XEv=Evaluation<>>
class SingleObjSearchToLocalSearchBuilder : public LocalSearchBuilder<S, XEv>
{
public:
   virtual ~SingleObjSearchToLocalSearchBuilder()
   {
   }

   virtual LocalSearch<S, XEv>* build(Scanner& scanner, HeuristicFactory<S, XEv>& hf, string family = "")
   {
      Evaluator<S, XEv>* eval;
      hf.assign(eval, scanner.nextInt(), scanner.next()); // reads backwards!

      string rest = scanner.rest();

      pair<SingleObjSearch<S, XEv>*, std::string> method;
      method = hf.createSingleObjSearch(rest);

      SingleObjSearch<S, XEv>* h = method.first;

      scanner = Scanner(method.second);

      return new SingleObjSearchToLocalSearch<S, XEv>(*eval, *h);
   }

   virtual vector<pair<string, string>> parameters()
   {
      vector<pair<string, string>> params;
      params.push_back(make_pair(Evaluator<S, XEv>::idComponent(), "evaluation function"));
      params.push_back(make_pair(SingleObjSearch<S, XEv>::idComponent(), "single obj search"));

      return params;
   }

   virtual bool canBuild(string component)
   {
      return component == SingleObjSearchToLocalSearch<S, XEv>::idComponent();
   }

   static string idComponent()
   {
      stringstream ss;
      ss << LocalSearchBuilder<S, XEv>::idComponent() << "SingleObjSearchToLocalSearch";
      return ss.str();
   }

   virtual string id() const
   {
      return idComponent();
   }
};
}

#endif
