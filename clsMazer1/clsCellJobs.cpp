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
#include "clsCellJobs.hpp"
#include "clsMazer.hpp"

using namespace std;

namespace nsMazer
{
    clsCellJobs::clsCellJobs(cellLoc start, cellLoc end)
    {
        AddJob(start, enCellState::INVISITED);
        AddJob(end, enCellState::OUTVISITED);
    } // Constructor

    void clsCellJobs::AddJob(cellLoc z, enCellState searchMode) 
    { 
        cellJob job = { z,searchMode };
        _cellJobs.push_back(job);
    }
    cellJob clsCellJobs::GetJob() { return _cellJobs[0]; }
    void clsCellJobs::CompleteJob() { if(_cellJobs.size() > 0) _cellJobs.erase(_cellJobs.begin()); }
    size_t clsCellJobs::JobsCount() { return _cellJobs.size(); }
    void clsCellJobs::ClearJobs() { _cellJobs.clear(); }
} // ns
