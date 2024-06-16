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

#include <string>
#include <iostream>
#include <iomanip>
#include "clsMazeWorker.hpp"
#include "../clsMazer1/clsMazer.hpp"
#include "../clsMazer1/bitwise.hpp"

using namespace std;
using namespace nsMazer;
using namespace mazer1;

clsMazerMetric* clsMazeCells::_metrics = new clsMazerMetric();

int main(int argc, const char* argv[])
{
	clsMazeWorker* worker = new clsMazeWorker();
	cout << "Initialize" << endl ;
	int mazeSize = 60;
	cout << "Generating Maze..." << endl;
	clsMazer* maze = new clsMazer();
	maze->configureMaze(mazeSize, mazeSize, { 2,0 }, { mazeSize - 3, mazeSize - 1 });
	maze->buildMaze();

	worker->printRaw(maze, "##", "  ", ",");

	cout << endl << "End maze." << endl;

	// show the maze builder log
	for (const string& s : maze->MazerLog) cout << "LOG: " << s << endl;
	delete maze;
} // main
