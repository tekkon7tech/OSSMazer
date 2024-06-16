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

#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>
#include <iostream>
#include "clsMazer.hpp"
#include "bitwise.hpp"

using namespace std;

namespace nsMazer
{
    clsMazer::clsMazer()
    {
        rndStack = new clsRndStack(); // random direction stack
    } // Constructor

    clsMazer::~clsMazer() { delete _mazeCells; delete _cellJobs; } // Deconstructor

    bool clsMazer::configureMaze(int width, int height, cellLoc locStart, cellLoc locEnd)
    {
        if (!Validate(width, height, locStart, locEnd)) return false;
        _mazeCells = new clsMazeCells(width, height, locStart, locEnd);
        _cellJobs = new clsCellJobs(locStart, locEnd); // builds a job for the start and end cell
        return true;
    } // configureMaze

    void clsMazer::buildMaze()
    {
        while (_cellJobs->JobsCount() > 0)
        {
            cellJob j = _cellJobs->GetJob();
            evalCell(j);
        }
    } // buildMaze

    void clsMazer::evalCell(cellJob job)
    {
        bool finalSuccess = false;
        rndStack->randomize();
        for(int x = 0;x<rndStack->stk.size();x++) // x is the direction from enMoveDir
        {
            enMoveDir moveDir = rndStack->stk[x];
            cellLoc tgt = dirToCoord(job.coord, moveDir);
            if (!_mazeCells->checkReject(tgt, job.searchMode)) continue;
            bool finalSuccess = _mazeCells->checkSuccess(job.coord, tgt, oppSearchMode());

            if (bitwise::isSet(job.searchMode, enCellState::INVISITED)) historyStart.push_back(moveDir);
            else historyEnd.push_back(moveDir);

            _cellJobs->AddJob(tgt, job.searchMode); // target cell is good, add it to the queue
            _mazeCells->setTargetCell(moveDir, job.coord, tgt, job.searchMode); // set the target cell and intermediate cell as an open area
            _cellJobs->CompleteJob();

            if (finalSuccess) { _cellJobs->ClearJobs(); clsMazeCells::_metrics->setSuccessCell(tgt); }
            return;
        }
        // if we got here there was no eligible target cell
        if (bitwise::isSet(job.searchMode, enCellState::INVISITED))
        {
            _cellJobs->AddJob(dirToCoord(job.coord, oppDirection(historyStart.back())), job.searchMode);
            historyStart.erase(historyStart.end()-1);
            clsMazeCells::_metrics->entryReverse(); // metric
        }
        else if (bitwise::isSet(job.searchMode, enCellState::OUTVISITED))
        {
            _cellJobs->AddJob(dirToCoord(job.coord, oppDirection(historyEnd.back())), job.searchMode);
            historyEnd.erase(historyEnd.end()-1);
            clsMazeCells::_metrics->exitReverse(); // metric
        }
        _cellJobs->CompleteJob();
    } // evalCell

    enMoveDir clsMazer::oppDirection(enMoveDir dir) 
    { 
        switch (dir)
        {
            case enMoveDir::UP: return enMoveDir::DOWN;
            case enMoveDir::RIGHT: return enMoveDir::LEFT;
            case enMoveDir::DOWN: return enMoveDir::UP;
        }
        return enMoveDir::RIGHT;
    } // oppDirection

    int clsMazer::oppSearchMode() { return bitwise::isSet(_cellJobs->GetJob().searchMode, enCellState::INVISITED) ? enCellState::OUTVISITED : enCellState::INVISITED; }

    cellLoc clsMazer::dirToCoord(cellLoc z, enMoveDir dir)
    {
        cellLoc newLoc = z;
        switch (dir)
        {
            case enMoveDir::UP: newLoc.Y -= 2; break;
            case enMoveDir::RIGHT: newLoc.X += 2; break;
            case enMoveDir::DOWN: newLoc.Y += 2; break;
            default: newLoc.X -= 2;
        }
        return newLoc;
    } // dirToCoord

    int clsMazer::rndRange(int low, int high)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(low, high); // distribution in range between low and high

        return dist6(rng);
    } // rndRange
    bool clsMazer::hasFlag(int cell, enCellState flag) { return ((int)cell & (int)flag) != 0; } // hasFlag

    bool clsMazer::Validate(int width, int height, cellLoc locStart, cellLoc locEnd)
    {
        if (width < _minMazeSize || height < _minMazeSize) { MazerLog.push_back("Maze is less than minimum size."); return false; }

        if ((locStart.X <= 0 && locStart.Y <= 0) 
            || (locStart.X <= 0 && locStart.Y >= height)
            || (locStart.X >= width && locStart.Y <= 0)
            || (locStart.X >= width && locStart.Y >= height)) { MazerLog.push_back("Start location cannot be a corner."); return false; }

        if ((locEnd.X <= 0 && locEnd.Y <= 0)
            || (locEnd.X <= 0 && locEnd.Y >= height)
            || (locEnd.X >= width && locEnd.Y <= 0)
            || (locEnd.X >= width && locEnd.Y >= height)) { MazerLog.push_back("Start location cannot be a corner."); return false; }

        if (abs(locStart.X - locEnd.X) < 5 || abs(locStart.Y - locEnd.Y) < 5) { MazerLog.push_back("Start and end location are too close"); return false; }

        return true;
    } // Validate

    int clsMazer::get_MazeWidth() { return _mazeCells->MazeWidth; } // get_MazeWidth
    int clsMazer::get_MazeHeight() { return _mazeCells->MazeHeight; } // get_MazeHeight
} // ns
