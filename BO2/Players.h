#pragma once
#include "stdafx.h"
#include "Players.h"
#include <iostream>

using namespace std;



class Players
{
public:
//	Players(char nameVal[20], int cashVal, int networthVal, int sharesVal[maxCompanies]);
	Players();

	void getInfo();
 




char name[20];
int cash;
int networth;
int turnorder;
int shares[maxCompanies];
int sold[maxCompanies];

private:




};

