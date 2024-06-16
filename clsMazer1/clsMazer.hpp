/*
Licensed to the Apache Software Foundation(ASF) under one
or more contributor license agreements.See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.The ASF licenses this file
to you under the Apache License, Version 2.0 (the
	"License"); you may not use this file except in compliance
	with the License.You may obtain a copy of the License at

	http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.See the License for the
specific language governing permissions and limitations
under the License.

Copyright 2024 Tekkon7 Technologies Ltd.
// */

#ifndef clsmazer3_hpp
#define clsmazer3_hpp

#include <vector>
#include "mazerBase.hpp"
#include "clsRndStack.hpp"
#include "clsCellJobs.hpp"
#include "clsMazeCells.hpp"

using namespace std;

namespace nsMazer
{
	class clsMazer
	{
	public:
		clsMazer();
		~clsMazer();

		clsMazeCells* _mazeCells;
		bool hasFlag(int, enCellState);
		void evalCell(cellJob);
		bool configureMaze(int, int, cellLoc, cellLoc);
		void buildMaze();
		bool Validate(int, int, cellLoc, cellLoc);
		vector<string> MazerLog;

		// accessors
		int get_MazeWidth();
		int get_MazeHeight();
	private:
		clsRndStack* rndStack;
		vector<enMoveDir> historyStart;
		vector<enMoveDir> historyEnd;
		clsCellJobs* _cellJobs;

		int rndRange(int, int);
		cellLoc dirToCoord(cellLoc, enMoveDir);
		int oppSearchMode();
		enMoveDir oppDirection(enMoveDir);
	}; // clsMazer3
} // nsMazer

#endif /* clsmazer3_hpp */
