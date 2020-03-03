#pragma once

#ifndef $project_NSSEQ$neighborhood_H_
#define $project_NSSEQ$neighborhood_H_

// Framework includes
#include "../../OptFrame/Move.hpp"
#include "../../OptFrame/MoveCost.hpp"
#include "../../OptFrame/NSIterator.hpp"
#include "../../OptFrame/NSSeq.hpp"
#include "../../OptFrame/RandGen.hpp"

// Own includes
#include "ProblemInstance.h"
#include "Representation.h"

using namespace std;

namespace $project
{

class Move$neighborhood: public Move< Solution$project >
{
private:
    // MOVE PARAMETERS

public:

    Move$neighborhood() // ADD PARAMETERS
    {
    }

    virtual ~Move$neighborhood()
    {
    }
    
    void print() const override
    {
        cout << id() << " with params: '" << "ADD MY PARAMETERS" << "'" << endl;
    }
    
    string id() const override
    {
        return Move<Solution$project >::idComponent().append(":Move$neighborhood");
    }
    
    bool operator==(const Move< Solution$project >& _m) const
    {
        const Move$neighborhood& m = (const Move$neighborhood&) _m;
        // COMPARE PARAMETERS AND RETURN TRUE IF EQUALS
        return false;
    }
    
    // Implement these methods in the .cpp file
    
    bool canBeApplied(const Solution$project& rep) override;

    uptr<Move< Solution$project >> apply(Solution$project& rep) override;
    
    op< Evaluation$project > cost(const pair< Solution$project , Evaluation$project >& se, bool allowEstimated) override;
};



class NSIterator$neighborhood: public NSIterator< Solution$project >
{
private:
    // ITERATOR PARAMETERS

public:
    NSIterator$neighborhood() // ADD ITERATOR PARAMETERS
    {
    }

    virtual ~NSIterator$neighborhood()
    {
    }
    
    // Implement these methods in the .cpp file

    void first() override;
    void next() override;
    bool isDone() override;
    uptr<Move< Solution$project >> current() override;
};



class NSSeq$neighborhood: public NSSeq< Solution$project >
{
private:
    // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
    ProblemInstance& p$project; // problem instance data
    RandGen& rg;                // random number generator

public:

    // YOU MAY REMOVE THESE PARAMETERS IF YOU DON'T NEED (BUT PROBABLY WILL...)
    NSSeq$neighborhood(ProblemInstance& _p$project, RandGen& _rg):
        p$project(_p$project), rg(_rg)
    {
    }

    virtual ~NSSeq$neighborhood()
    {
    }
    
    void print() const override
    {
        cout << "NSSeq$neighborhood" << endl;
    }
    
    string id() const override
    {
        return NSSeq<Solution$project >::idComponent().append(":NSSeq$neighborhood");
    }
    
    uptr<NSIterator<Solution$project >> getIterator(const Solution$project& rep) override
    {
        // return an iterator to the neighbors of 'rep' 
        return uptr<NSIterator<Solution$project >>(new NSIterator$neighborhood );  // ADD POSSIBLE ITERATOR PARAMETERS
    }
        
    // Implement this method in the .cpp file

    uptr<Move<Solution$project >> randomMove(const Solution$project& rep) override;
    
    // Move<Solution$project >* validRandomMove(const Solution$project& rep) override;
};

}

#endif /*$project_NSSEQ$neighborhood_H_*/
