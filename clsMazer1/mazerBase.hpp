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

#ifndef mazerbase_hpp
#define mazerbase_hpp

using namespace std;

namespace nsMazer
{
	enum enCellState
	{
		WALL = 1,
		ENTRY = 16,
		EXIT = 32,
		INVISITED = 64,
		OUTVISITED = 128
	};
	enum enMoveDir
	{
		UP = 1,
		RIGHT = 2,
		DOWN = 4,
		LEFT = 8
		//FORWARD = 32,
		//REVERSE = 64
	};

	enum enErrorMode
	{
		INVALIDENTRY, // either at a corner or not on an edge
		INVALIDSIZE
	};

	struct cellLoc
	{
		int X;
		int Y;
	};

	struct cellJob
	{
		cellLoc coord;
		enCellState searchMode;
	};
} // nsMazer

#endif /* mazerbase_hpp */
