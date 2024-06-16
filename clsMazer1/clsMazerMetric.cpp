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

#include "clsMazerMetric.hpp"

namespace nsMazer
{
	clsMazerMetric::clsMazerMetric()
	{
		Metrics.entrySearchCells = 0;
		Metrics.exitSearchCells = 0;
		Metrics.entryReverse = 0;
		Metrics.exitReverse = 0;
		Metrics.successCell = { 0,0 };
	}
	void clsMazerMetric::entrySearch() { Metrics.entrySearchCells++; }
	void clsMazerMetric::exitSearch() { Metrics.exitSearchCells++; }
	void clsMazerMetric::entryReverse() { Metrics.entryReverse++; }
	void clsMazerMetric::exitReverse() { Metrics.exitReverse++; }
	void clsMazerMetric::setSuccessCell(cellLoc tgt) { Metrics.successCell = tgt; }
} // nsMazer
