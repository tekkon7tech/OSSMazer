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

#ifndef bitwise_hpp
#define bitwise_hpp

namespace nsMazer
{
	class bitwise
	{
	public:
		static bool isSet(int x, int mask) { return (x & mask) == mask; }
		static void toggleBit(int& x, int bit) { x = (x ^ bit); }
		static void setBit(int& x, int bit) { x = (x | bit); }
		static void clearBit(int& x, int bit) { x = (x & ~bit); }
	};
} // nsMazer

#endif /* bitwise_hpp */
