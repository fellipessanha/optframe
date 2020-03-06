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

#ifndef OPTFRAME_NSSEQUNIONADAPTER_HPP_
#define OPTFRAME_NSSEQUNIONADAPTER_HPP_

// Framework includes
#include "../../Move.hpp"
#include "../../NSSeq.hpp"
#include "../../NSIterator.hpp"

#include "./Moves/MoveNSSeqUnion.hpp"
#include "./NSIterators/IteratorNSSeqUnion.hpp"

using namespace std;

//template<class R, class ADS = OPTFRAME_DEFAULT_ADS, class MOVE = MoveNSSeqUnion<R, ADS> >
template<class R, class ADS = OPTFRAME_DEFAULT_ADS, XBaseSolution<R,ADS> S = CopySolution<R,ADS>, XEvaluation XEv = Evaluation<>, XESolution XES = pair<S, XEv>, class MOVE = MoveNSSeqUnion<XES, XEv>>
class NSSeqUnionAdapter: public NSSeq<XES, XEv>
{
private:
	vector<NSSeq<S>*> ns;

public:

	NSSeqUnionAdapter(NSSeq<S>& _n1, NSSeq<S>& _n2)
	{
		ns.push_back(&_n1);
		ns.push_back(&_n2);
	}

	void add_ns(NSSeq<S>& _ns)
	{
		ns.push_back(&_ns);
	}

	virtual ~NSSeqUnionAdapter()
	{
	}

	Move<R, ADS>& move(const R& r, const ADS& ads)
	{
		int x = rand() % ns.size();

		return *new MOVE(x, ns[x]->move(r, ads));
	}

	Move<R, ADS>* validMove(const R& r, const ADS& ads)
	{
		Move<R, ADS>* m = &move(r, ads);
		if(m->canBeApplied(r, ads))
			return m;
		else
		{
			delete m;
			return nullptr;
		}
	}

	virtual NSIterator<S, XEv>& getIterator(const R& r, const ADS& ads)
	{
		vector<NSIterator<S, XEv>*> it;
		for(unsigned int i = 0; i < ns.size(); i++)
			it.push_back(&ns[i]->getIterator(r, ads));

		return *new IteratorNSSeqUnion<R, ADS, MOVE>(it);
	}

	virtual string toString() const
	{
		stringstream ss;
		ss << "NSSeqUnionAdapter: [";
		for(unsigned int i = 0; i < ns.size(); i++)
		{
			ss << ns[i]->toString();

			if(i != ns.size() - 1)
				ss << ",";
		}
		ss << "] ";
		return ss.str();
	}
};

#endif /*OPTFRAME_NSSEQUNIONADAPTER_HPP_*/
