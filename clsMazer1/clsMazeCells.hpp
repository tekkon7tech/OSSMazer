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

#ifndef clsmazecells_hpp
#define clsmazecells_hpp

#include "mazerBase.hpp"
#include "clsMazerMetric.hpp"

namespace nsMazer
{
	const int _minMazeSize = 10;

	class clsMazeCells
	{
	public:
		clsMazeCells(int, int, cellLoc, cellLoc);
		~clsMazeCells();
		bool IsSetCellsBit(int, int, int);
		void SetCellsBit(int, int, int);
		void ClearCellsBit(int, int, int);
		void ToggleCellsBit(int, int, int);
		bool checkReject(cellLoc, enCellState);
		void setCellOpen(cellLoc, enCellState);
		void setTargetCell(enMoveDir, cellLoc, cellLoc, enCellState);
		bool checkSuccess(cellLoc, cellLoc, int);
		cellLoc coordHalf(cellLoc, cellLoc);

		static clsMazerMetric* _metrics;
		int MazeWidth;
		int MazeHeight;

		// accessors
		int get_CellData(int, int);
	private:
		int* _cellsWorking;
		cellLoc _cellStart = { 0,0 };
		cellLoc _cellEnd = { 9,9 };

		void cellsInit();
		void initStartEnd();
	};
} // nsMazer

#endif /* clsmazecells_hpp */
