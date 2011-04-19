#ifndef EtII_INITIALSOLUTION_Greedy_HPP_
#define EtII_INITIALSOLUTION_Greedy_HPP_

#include "../../OptFrame/InitialSolution.h"
#include "../../OptFrame/Util/TestSolution.hpp"
#include "../../OptFrame/RandGen.hpp"

#include "ProblemInstance.hpp"

#include "Representation.h"
#include "Solution.h"

#include "Evaluator.hpp"

#include <list>

#include <algorithm>
#include <stdlib.h>

using namespace std;

class EtIIInitialSolutionGreedy: public InitialSolution<RepEtII>
{
private:
	EtIIProblemInstance& pEtII;
	RandGen& rg;

public:

	EtIIInitialSolutionGreedy(EtIIProblemInstance& _pEtII,RandGen& _rg) : // If necessary, add more parameters
		pEtII(_pEtII), rg(_rg)
	{
	}

	SolutionEtII& generateSolution()
	{
		RepEtII* tab = new RepEtII(pEtII.height, pEtII.width);

		vector<Piece> corner_pieces;
		vector<Piece> side_pieces;
		vector<Piece> center_pieces;

		for (int i = 0; i < pEtII.pieces.size(); i++)
		{
			int zeros = 0;

			if (pEtII.pieces[i].down == 0)
				zeros++;
			if (pEtII.pieces[i].left == 0)
				zeros++;
			if (pEtII.pieces[i].up == 0)
				zeros++;
			if (pEtII.pieces[i].right == 0)
				zeros++;

			if (zeros == 2)
				corner_pieces.push_back(pEtII.pieces[i]);
			if (zeros == 1)
				side_pieces.push_back(pEtII.pieces[i]);
			if (zeros == 0)
				center_pieces.push_back(pEtII.pieces[i]);
		}

		// shuffle elements
		rg.shuffle(corner_pieces);
		rg.shuffle(side_pieces);
		rg.shuffle(center_pieces);

		int x;
		Piece p;

		// random one piece for left-upper corner
		x = rg.rand(corner_pieces.size());
		p = corner_pieces[x];
		corner_pieces.erase(corner_pieces.begin() + x);

		while ((p.left != 0) || (p.up != 0))
			p.rotate();

		(*tab)(0, 0) = p;

		// random one piece for right-upper corner
		x = rg.rand(corner_pieces.size());
		p = corner_pieces[x];
		corner_pieces.erase(corner_pieces.begin() + x);

		while ((p.right != 0) || (p.up != 0))
			p.rotate();

		(*tab)(0, tab->getCols() - 1) = p;

		// random one piece for right-lower corner
		x = rg.rand(corner_pieces.size());
		p = corner_pieces[x];
		corner_pieces.erase(corner_pieces.begin() + x);

		while ((p.right != 0) || (p.down != 0))
			p.rotate();

		(*tab)(tab->getRows() - 1, tab->getCols() - 1) = p;

		// random one piece for left-lower corner
		x = rg.rand(corner_pieces.size());
		p = corner_pieces[x];
		corner_pieces.erase(corner_pieces.begin() + x);

		while ((p.left != 0) || (p.down != 0))
			p.rotate();

		(*tab)(tab->getRows() - 1, 0) = p;

		// choose the pieces for upper-bottom sides
		for (int i = 1; i < tab->getCols() - 1; i++)
		{
			// top
			int max = 0;
			int best = 0;
			for (int j = 0; j < side_pieces.size(); j++)
			{
				p = side_pieces[j];

				while (p.up != 0)
					p.rotate();

				int f = 0;
				if (p.left == (*tab)(0, i - 1).right)
				{
					f++;
					// best found!
					max = f;
					best = j;
					break;
				}
			}

			p = side_pieces[best];
			side_pieces.erase(side_pieces.begin() + best);

			while (p.up != 0)
				p.rotate();
			(*tab)(0, i) = p;

			// bottom
			max = 0;
			best = 0;
			for (int j = 0; j < side_pieces.size(); j++)
			{
				p = side_pieces[j];

				while (p.down != 0)
					p.rotate();

				int f = 0;
				if (p.left == (*tab)(tab->getRows() - 1, i - 1).right)
				{
					f++;
					// best found!
					max = f;
					best = j;
					break;
				}
			}

			p = side_pieces[best];
			side_pieces.erase(side_pieces.begin() + best);

			while (p.down != 0)
				p.rotate();
			(*tab)(tab->getRows() - 1, i) = p;
		}

		// random the pieces for left-right sides
		for (int i = 1; i < tab->getRows() - 1; i++)
		{
			// left
			int max = 0;
			int best = 0;
			for (int j = 0; j < side_pieces.size(); j++)
			{
				p = side_pieces[j];

				while (p.left != 0)
					p.rotate();

				int f = 0;
				if (p.up == (*tab)(i - 1, 0).down)
				{
					f++;
					// best found!
					max = f;
					best = j;
					break;
				}
			}

			p = side_pieces[best];
			side_pieces.erase(side_pieces.begin() + best);

			while (p.left != 0)
				p.rotate();
			(*tab)(i, 0) = p;

			// right
			max = 0;
			best = 0;
			for (int j = 0; j < side_pieces.size(); j++)
			{
				p = side_pieces[j];

				while (p.right != 0)
					p.rotate();

				int f = 0;
				if (p.up == (*tab)(i - 1, tab->getCols() - 1).down)
				{
					f++;
					// best found!
					max = f;
					best = j;
					break;
				}
			}

			p = side_pieces[best];
			side_pieces.erase(side_pieces.begin() + best);

			while (p.right != 0)
				p.rotate();
			(*tab)(i, tab->getCols() - 1) = p;
		}

		// choose the center pieces
		for (int i = 1; i < tab->getRows() - 1; i++)
			for (int j = 1; j < tab->getCols() - 1; j++)
			{
				int max = -1;
				int best_k = -1;
				int best_r = -1;

				for (int k = 0; k < center_pieces.size(); k++)
				{
					p = center_pieces[k];

					for (int r = 0; r < 4; r++)
					{
						int f = 0;
						if (p.left == (*tab)(i, j - 1).right)
							f++;
						if (p.up == (*tab)(i - 1, j).down)
							f++;

						if (f > max)
						{
							max = f;
							best_k = k;
							best_r = r;
						}

						p.rotate();
					}

					// last rotation
					p.rotate();

					if (max == 2) // best piece
						break;
				}

				p = center_pieces[best_k];
				center_pieces.erase(center_pieces.begin() + best_k);

				for (int r = 0; r < best_r; r++)
					p.rotate();

				(*tab)(i, j) = p;
			}

		if (corner_pieces.size() > 0 || side_pieces.size() > 0 || center_pieces.size() > 0)
		{
			cout << "Warning: construction problem!" << endl;
		}

		return *new TestSolution<RepEtII> (*tab);

	}

};

#endif /*EtII_INITIALSOLUTION_Greedy_HPP_*/