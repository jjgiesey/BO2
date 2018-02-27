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

Players::Players(int value)
{
	for (int i = 0; i < numberPlayers; i++)
	{
		cash[i] = 0;
		networth[i] = 0;
		for (int j = 0; j < maxCompanies; j++)
		{
			shares[i][j] = 0;
			sold[i][j] = 0;
		}
	}

}

void Players::getInfo(int player)
{
	cout <<  name[player] << " has $" << cash << " and a networth of $" << networth << " and a turn order of " << turnorder << endl;

}

int  Players::getCash(int player)
{
	return (cash[player]);
}

int  Players::getNetworth(int player)
{
	return (networth[player]);
}

int  Players::getOrder(int player)
{
	return (order[player]);
}

int  Players::getShares(int player, int company)
{
	return (shares[player][company]);
}

int  Players::getSold(int player, int company)
{
	return (sold[player][company]);
}

int  Players::setCash(int player, int amount)
{
	cash[player] = amount;
	return(cash[player]);
}

int  Players::setNetworth(int player, int amount)
{
	networth[player] = amount;
	return(networth[player]);
}

int  Players::setOrder(int player, int porder)
{
	order[player] = porder;
	return(porder);
}
int  Players::setShares(int player, int company, int pshares)
{
	shares[player][company] = pshares;
	return(pshares);
}
int  Players::setSold(int player, int company)
{
	sold[player][company] = 1;
	return(1);
}
int  Players::clearSold(int player, int company)
{
	sold[player][company] = 0;
	return(0);
}

int  Players::changeCash(int player, int amount)
{
	cash[player] += amount;
	return(cash[player]);
}
int  Players::changeShares(int player, int company, int amount)
{
	shares[player][company] += amount;
	return(shares[player][company]);
}
