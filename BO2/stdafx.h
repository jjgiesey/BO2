// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <stdlib.h>     
#include <time.h>   

const int maxPlayers = 6;
const int maxCompanies = 10;
const int initialCash[6] = { 1500, 750, 500, 375, 300, 250 };
const int valuations[26] = { 34, 37, 41, 45, 50, 55, 60, 66, 74, 82, 91, 100, 110, 121, 133, 146, 160, 176, 194, 213, 234, 257, 282, 310, 341, 375 };
const int initialValuations[6][3] = { { 5, 6, 7 },
{ 6, 7, 8 },
{ 7, 8, 9 },
{ 8, 9, 10 },
{ 9, 10, 11 } };



// TODO: reference additional headers your program requires here
