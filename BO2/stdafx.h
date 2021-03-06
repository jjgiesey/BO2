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
#include <fstream>
#include <windows.h>

const int maxPlayers = 6;
const int maxCompanies = 10;
const int maxTrains = 30;
const int maxCities = 40;
const int initialCash[6] = { 1500, 750, 500, 375, 300, 250 };
const int valuations[26] = { 34, 37, 41, 45, 50, 55, 60, 66, 74, 82, 91, 100, 110, 121, 133, 146, 160, 176, 194, 213, 234, 257, 282, 310, 341, 375 };
const int initialValuations[6][3] = { { 5, 6, 7 },
{ 6, 7, 8 },
{ 7, 8, 9 },
{ 8, 9, 10 },
{ 9, 10, 11 } };
//const int trainCost[30] = { 100, 95,90,85,80,140,130,120,110,100,200,185,170,155,135,280,260,240,220,200,380,355,330,305,280,500,470,440,410,380 };
//const int trainLevel[30] = { 1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6 };
//const int trainScrap[30] = { 20,20,20,20,20,40,40,40,40,40,60,60,60,60,60,80,80,80,80,80,100,100,100,100,100,120,120,120,120,120 };
//const int trainNumber[30] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };
/*const int level[6] = { 1,2,3,4,5,6 };
const int buildLimit[6] = { 1,2,3,4,5,6 };
const int companiesPerCity[6] = { 2,2,3,4,5,6 };
const int maintenanceCost[6] = { 10, 20,30,40,50,60 };
const int techLevelLowVal[6] = { 5,6,7,8,9,10 };
const int techLevelHighVal[6] = { 7,8,9,10,11,12 };
const int techLevelMedVal[6] = { 6, 7, 8, 9, 10, 11 };*/