#pragma once


class Players
{
public:
	Players(int value);

	char name[maxPlayers][20];
	void getInfo(int player);
	int getCash(int player);
	int getNetworth(int player);
	int getOrder(int player);
	int getShares(int player, int company);
	int getSold(int player, int company);

	int setCash(int player, int amount);
	int setNetworth(int player, int amount);
	int setOrder(int player, int order);
	int setShares(int player, int company, int amount);
	int setSold(int player, int company);
	int clearSold(int player, int company);

	int changeCash(int player, int amount);
	int changeShares(int player, int company, int amount);



private:


int cash[maxPlayers];
int networth[maxPlayers];
int turnorder[maxPlayers];
int shares[maxPlayers][maxCompanies];
int sold[maxPlayers][maxCompanies];

};

