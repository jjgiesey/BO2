#include "stdafx.h"
#include "Players.h"


/*
Players::Players(char nameVal[20], int cashVal, int networthVal, int sharesVal[maxCompanies])
{
 strcpy_s(name, nameVal);
 cash = cashVal;
 networth = networthVal;
 for (int j = 0; j < maxCompanies; j++)
 {
	 shares[j] = sharesVal[j];
 }
} */

Players::Players()
{

}

void Players::getInfo()
{
	cout <<  name << " has $" << cash << " and a networth of $" << networth << " and a turn order of " << turnorder << endl;

}


