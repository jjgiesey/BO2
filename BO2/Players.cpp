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

char Players::getName(int player)
{
	return (name[player][]);
}
int  Players::getCash(int player)
{
	return (cash[player]);
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

int  Players::setName(int player, char pname[])
{
		strcpy_s(name[player],pname);
		return (0);

}
int  Players::setCash(int player, int amount)
{
	cash[player] = amount;
	return(cash[player]);
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
