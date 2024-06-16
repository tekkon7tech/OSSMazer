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

#include "clsMazeCells.hpp"
#include "bitwise.hpp"

namespace nsMazer
{
	clsMazeCells::clsMazeCells(int width, int height, cellLoc locStart, cellLoc locEnd)
	{
		_cellStart = locStart;
		_cellEnd = locEnd;
		MazeWidth = width >= _minMazeSize ? width : _minMazeSize;
		MazeHeight = height >= _minMazeSize ? height : _minMazeSize;
		_cellsWorking = new int[MazeWidth * MazeHeight];
		cellsInit();
		initStartEnd();
	} // Constructor

	clsMazeCells::~clsMazeCells() { delete _cellsWorking; delete _metrics; } // Deconstructor

	void clsMazeCells::cellsInit() { for (int x = 0; x < MazeWidth; x++) { for (int y = 0; y < MazeHeight; y++) { _cellsWorking[y * MazeHeight + x] = WALL; } } } // cellsInit

	bool clsMazeCells::checkSuccess(cellLoc src, cellLoc tgt, int oppSearchMode)
	{
		cellLoc delta = coordHalf(src, tgt);
		if (IsSetCellsBit(tgt.X, tgt.Y, oppSearchMode)
			|| IsSetCellsBit(tgt.X + delta.X, tgt.Y + delta.Y, oppSearchMode)) return true;
		return false;
	} // checkSuccess

	cellLoc clsMazeCells::coordHalf(cellLoc src, cellLoc tgt)
	{
		cellLoc z;
		z.X = (src.X - tgt.X) / 2;
		z.Y = (src.Y - tgt.Y) / 2;
		return z;
	} // coordHalf

	void clsMazeCells::setCellOpen(cellLoc tgt, enCellState searchMode)
	{
		ClearCellsBit(tgt.X, tgt.Y, enCellState::WALL);
		SetCellsBit(tgt.X, tgt.Y, searchMode);
	} // setCellOpen

	void clsMazeCells::setTargetCell(enMoveDir moveDir, cellLoc src, cellLoc tgt, enCellState searchMode)
	{
		if (bitwise::isSet(searchMode, enCellState::INVISITED)) clsMazeCells::_metrics->entrySearch(); else clsMazeCells::_metrics->exitSearch();
		setCellOpen(tgt, searchMode);
		switch (moveDir)
		{
			case enMoveDir::UP: setCellOpen({ src.X, src.Y - 1 }, searchMode); break;
			case enMoveDir::RIGHT: setCellOpen({ src.X + 1, src.Y }, searchMode); break;
			case enMoveDir::DOWN: setCellOpen({ src.X, src.Y + 1 }, searchMode); break;
			case enMoveDir::LEFT: setCellOpen({ src.X - 1, src.Y }, searchMode); break;
		}
	} // setTargetCell

	void clsMazeCells::initStartEnd()
	{
		ClearCellsBit(_cellStart.X, _cellStart.Y, enCellState::WALL);
		SetCellsBit(_cellStart.X, _cellStart.Y, enCellState::INVISITED);
		SetCellsBit(_cellStart.X, _cellStart.Y, enCellState::ENTRY);
		ClearCellsBit(_cellEnd.X, _cellEnd.Y, enCellState::WALL);
		SetCellsBit(_cellEnd.X, _cellEnd.Y, enCellState::OUTVISITED);
		SetCellsBit(_cellEnd.X, _cellEnd.Y, enCellState::EXIT);
	} // initStartEnd

	bool clsMazeCells::checkReject(cellLoc tgt, enCellState searchMode)
	{
		if (bitwise::isSet(_cellsWorking[tgt.Y * MazeHeight + tgt.X], searchMode)) return false;
		if (tgt.X < 1 || tgt.X > (MazeWidth-2)) return false;
		if (tgt.Y < 1 || tgt.Y > (MazeHeight-2)) return false;
		return true;
	} // checkReject

	bool clsMazeCells::IsSetCellsBit(int x, int y, int mask) { return bitwise::isSet(_cellsWorking[y * MazeHeight + x], mask); }
	void clsMazeCells::SetCellsBit(int x, int y, int mask) { bitwise::setBit(_cellsWorking[y * MazeHeight + x], mask); }
	void clsMazeCells::ClearCellsBit(int x, int y, int mask) { bitwise::clearBit(_cellsWorking[y * MazeHeight + x], mask); }
	void clsMazeCells::ToggleCellsBit(int x, int y, int mask) { bitwise::toggleBit(_cellsWorking[y * MazeHeight + x], mask); }
	int clsMazeCells::get_CellData(int x, int y) { return _cellsWorking[y * MazeHeight + x]; }
} // nsMazer
