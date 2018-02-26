#pragma once
#include "stdafx.h"
#include "Players.h"
#include <iostream>

using namespace std;



class Players
{
public:
	Players();

	void getInfo(int player);
	char getName(int player);
	int getCash(int player);
	int getOrder(int player);
	int getShares(int player, int company);
	int getSold(int player, int company);

	int setName(int player, char name[20]);
	int setCash(int player, int amount);
	int setOrder(int player, int order);
	int setShares(int player, int company);
	int setSold(int player, int company);
	int clearSold(int player, int company);

	int changeCash(int player, int amount);
	int changeShares(int player, int company, int amount);



private:

char name[maxPlayers][20];
int cash[maxPlayers];
int networth[maxPlayers];
int turnorder[maxPlayers];
int shares[maxPlayers][maxCompanies];
int sold[maxPlayers][maxCompanies];

};

