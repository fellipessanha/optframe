// ===================================
// Main.cpp file generated by OptFrame
// Project Eternity II
// ===================================

#include <stdlib.h>
#include <math.h>

#include <iostream>

using namespace std;

#include <set>

#include "../OptFrame/OptFrame.hpp"
#include "EternityII.h"

int main(int argc, char **argv)
{
	srand(time(NULL));
	RandGen rg(time(NULL));

	Scanner scanner(new File("./OptFrame/Examples/EternityII/pieces_set_2/pieces_03x03.txt"));

	EtIIProblemInstance* p = new EtIIProblemInstance(scanner);

	EtIIInitialSolutionGreedy is(*p,rg);

	SolutionEtII& s = is.generateSolution();

	NSSeqRotate nsRotate(rg);
	NSSeqSwapCenter nsSwapCenter(rg);
	NSSeqSwapCorner nsSwapCorner(rg);
	NSSeqSwapRotateCenter nsSwapRotateCenter(rg);
	NSSeqSwapSide nsSwapSide(rg);

	s.print();

	EtIIEvaluator eval(*p);
	EvaluationEtII* e;

	e = &eval.evaluate(s);

	e->print();
	cout << endl;

	HeuristicFactory<RepEtII, MemEtII> factory(rg);
	factory.add_initsol(&is);
	factory.add_ev(&eval);
	factory.add_ns(&nsRotate);
	factory.add_ns(&nsSwapCenter);
	factory.add_ns(&nsSwapCorner);
	factory.add_ns(&nsSwapRotateCenter);
	factory.add_ns(&nsSwapSide);


	OptFrame<RepEtII, MemEtII> optframe(factory);
	optframe.execute();

	cout << "Program ended successfully" << endl;

	return 0;
}
