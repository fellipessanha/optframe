#ifndef OPTFRAME_MOVEVVSwapkIntra_HPP_
#define OPTFRAME_MOVEVVSwapkIntra_HPP_

// Framework includes
#include "../../Move.hpp"

#include "../NSVector.hpp"

using namespace std;

//============================================================================
//                           VVSwapkIntra Move
//============================================================================

template<class T, class M>
class MoveVVSwapkIntra : public Move<vector<vector<T> >, M>
{
public:
	int k1,k2,v,p1,p2;

	MoveVVSwapkIntra(int k1,int k2,int v,int p1,int p2)
	{
		this->k1 = k1;
		this->k2 = k2;
		this->v = v;
		this->p1 = p1;
		this->p2 = p2;
	}

	virtual bool canBeApplied(const vector<vector<T> >&)
	{
		return true;
	}

	virtual Move<vector<vector<T> >, M>& apply(vector<vector<T> >& rep)
	{
		pair<pair<int,int>,pair<int,int> > m;
		m.first.first = k1;
		m.first.second = k2;
		m.second.first = p1;
		m.second.second = p2;
		NSVector<T>::swapk_apply(rep[v],m); //TODO

		return * new MoveVVSwapkIntra<T,M>(k1,k2,v,p2,p1);
	}

	virtual Move<vector<vector<T> >, M>& apply(M& m, vector<vector<T> > & r)
	{
		if (!m.empty())
		{
			m[v].first = -1;
			m[v].second.first = p1;
			m[v].second.second = r[v].size()-1;
		} else
		{
			//e->setMemory(new MemVRP(r.size(),make_pair(-1,make_pair(0,r.size()-1))));
			m = MemVRPTW(r.size(),make_pair(-1,make_pair(0,r.size()-1)));
		}

		return apply(r);
	}

	virtual void print() const
	{
		cout << "Move VRP SwapkIntra("<< k1 << " " << k2 << " " << v << " " << p1 << " " << p2 <<")"<<endl;
	}

	virtual bool operator==(const Move<vector<vector<T> >,M>& m) const
	{
		return false; //TODO
	}
};

#endif /*OPTFRAME_MOVEVVSwapkIntra_HPP_*/