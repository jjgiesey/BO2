#include "stdafx.h"
#include "Companies.h"
#include <iostream>

using namespace std;


Companies::Companies(int cashVal[maxCompanies], int netprofitVal[maxCompanies], int valuationVal[maxCompanies], int sharesVal[maxCompanies], int orphansVal[maxCompanies], int presidentVal[maxCompanies], int turnorderVal[maxCompanies], bool startedVal[maxCompanies], bool soldVal[maxCompanies], bool recievershipVal[maxCompanies])

{
	for (int j = 0; j < maxCompanies; j++)
	{
		cash[j] = cashVal[j];
		netprofit[j] = netprofitVal[j];
		valuation[j] = valuationVal[j];
		shares[j] = sharesVal[j];
		orphans[j] = orphansVal[j];
		president[j] = presidentVal[j];
		turnorder[j] = turnorderVal[j];
		started[j] = startedVal[j];
		sold[j] = soldVal[j];
		recievership[j] = recievershipVal[j];
		for (int k = 0; k < maxCities; k++)
		{
			cities[j][k] = false;
		}
	}
}
// Simple Get Routines


int Companies::getCash(int company)
{
	return (cash[company]);
}

int Companies::getPresident(int company)
{
	return (president[company]);
}

int Companies::getValuation(int company)
{
	return (valuation[company]);
}

int Companies::getNetprofit(int company)
{
	return (netprofit[company]);
}

int Companies::getShares(int company)
{
	return (shares[company]);
}


int Companies::getOrphans(int company)
{
	return (orphans[company]);
}

bool Companies::getCity(int company, int city)
{
	return(cities[company][city]);
}

bool Companies::getStarted(int company)
{
	return (started[company]);
}

bool Companies::getSold(int company)
{
	return (sold[company]);
}

bool Companies::getRecievership(int company)
{
	return (recievership[company]);
}

bool Companies::getAvailable(int company, int techLevel)
{
    return ((available[company] <= techLevel));
}

int Companies::getTurn(int company)
{
	return (turnorder[company]);
}

// Complex Get Routines

void Companies::getInfo(int company)
{
	cout << name[company] << "Cash: $" << cash[company] << netprofit[company] << " val $" <<
		valuation[company] << " shr " << shares[company] << " pres " <<
		orphans[company] << " orp " << president[company] << " TO " <<
		turnorder[company] << " strt " << started[company] << "sold " << sold[company] << endl;
		return;
}


int Companies::getNext(int order)
{
	int next = maxCompanies;
	for (int j = 0; j < maxCompanies; j++)
	{
		if (order == turnorder[j])
		{
			next = j;
		}
	}
	return (next);
}

int Companies::getorderCompany(int oldTurnorder[])
{
 for (int j=0; j< maxCompanies; j++)
 {
    oldTurnorder[turnorder[j]]=j; 
 }
 return 0;
}



// Setting Modifiers



int Companies::setStarted(int company)
{
	started[company] = true;
	return (started[company]);
}

int Companies::clearStarted(int company)
{
	started[company] = false;
	return (started[company]);
}

int Companies::setSold(int company)
{
	sold[company] = true;
	return (sold[company]);
}

int Companies::clearSold()
{
	for (int j = 0; j< maxCompanies; j++)
		sold[j] = true;
	return (0);
}

int Companies::clearSold(int company)
{
	sold[company] = false;
	return (sold[company]);
}

int Companies::setRecievership(int company)
{
	recievership[company] = true;
	return (recievership[company]);
}

int Companies::clearRecievership(int company)
{
	for (int j = 0; j< maxCompanies; j++)
		recievership[j] = false;
	return (0);
}



int Companies::setInitialValuation(int company, int value)
{
    valuation[company] = value;
    return (valuation[company]);
}

int Companies::setCity(int company, int city)
{
	cities[company][city] = true;
	return (cities[company][city]);
}
int Companies::clearCity(int company, int city)
{
	cities[company][city] = false;
	return (cities[company][city]);
}

int Companies::setCash(int company, int value)
{
    cash[company] = value;
    return (cash[company]);
}

int Companies::setNetprofit(int company, int netprofitVal)
{
    netprofit[company] = netprofitVal;
    return(netprofit[company]);
}

int Companies::setPresident(int company, int player)
{
    president[company] = player;
    return(president[company]);
}

int Companies::setTurn(int company, int turn)
{
	turnorder[company] = turn;
	return (turn);
}


int Companies::setTurnorder(int company, int direction)
{
    int turnorderChange = 0;

    if (direction < 0) // Valuation decrement
    {
        for (int j = 0; j < maxCompanies; j++)
        {
            if ((turnorder[company] < turnorder[j]) && (valuation[company] < valuation[j]))
            {
                turnorder[j] --; // bump up j one
                turnorderChange ++; // bumn down company one
            }
        }
        turnorder[company] += turnorderChange;
    }
    else
    { 
        for (int j = 0; j < maxCompanies; j++)
        {
            if ((turnorder[company] > turnorder[j]) && (valuation[company] > valuation[j]))
            {
                turnorder[j] ++; // bump down j one
                turnorderChange --; // bumn up company one
            }
        }
        turnorder[company] += turnorderChange;
    } 
    return(turnorder[company]);
}

int Companies::increaseValuation(int company)
{
	if (valuation[company] < 26)
	{
		valuation[company] ++;
		setTurnorder(company, 1);
	}
//	cout << name[company] << " now has a valuation of $" << valuations[valuation[company]] << " per share \n";
	return(valuation[company]);
}


int Companies::decreaseValuation(int company)
{
	if (valuation[company] > 0)
	{
		valuation[company] --;
		setTurnorder(company, -1);
	}
//	cout << name[company] << " now has a valuation of $" << valuations[valuation[company]] << " per share \n";
	return(valuation[company]);
}

int Companies::changeCash(int company, int value)
{
	cash[company] += value;
	return (shares[company]);
}


int Companies::changeShares(int company, int value)
{
    shares[company] += value;
    return (shares[company]);
}


int Companies::changeOrphans(int company, int value)
{
    orphans[company] += value;
    return (orphans[company]);
}


