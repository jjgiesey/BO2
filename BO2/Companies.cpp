#include "stdafx.h"
#include "Companies.h"


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
		order[j] = turnorderVal[j];
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

//Cash functions
int Companies::getCash(int company)
{
	return (cash[company]);
}
int Companies::setCash(int company, int value)
{
	cash[company] = value;
	return (cash[company]);
}
int Companies::changeCash(int company, int value)
{
	cash[company] += value;
	return (shares[company]);
}

//President functions
int Companies::getPresident(int company)
{
	return (president[company]);
}
int Companies::setPresident(int company, int player)
{
	president[company] = player;
	return(president[company]);
}

//Valuation functions
int Companies::getValuation(int company)
{
	return (valuation[company]);
}
int Companies::setValuation(int company, int value)
{
	valuation[company] = value;
	setTurnorders();
	return (valuation[company]);
}
int Companies::increaseValuation(int company)
{
	if (valuation[company] < 26)
	{
		valuation[company] ++;
		setTurnorders();
	}
	//	cout << name[company] << " now has a valuation of $" << valuations[valuation[company]] << " per share \n";
	return(valuation[company]);
}
int Companies::decreaseValuation(int company)
{
	if (valuation[company] > 0)
	{
		valuation[company] --;
		setTurnorders();
	}
	//	cout << name[company] << " now has a valuation of $" << valuations[valuation[company]] << " per share \n";
	return(valuation[company]);
}

//Net Profit functions
int Companies::getNetprofit(int company)
{
	return (netprofit[company]);
}
int Companies::setNetprofit(int company, int netprofitVal)
{
	netprofit[company] = netprofitVal;
	return(netprofit[company]);
}

//Shares fucntions
int Companies::getShares(int company)
{
	return (shares[company]);
}
int Companies::setShares(int company, int value)
{
	shares[company] = value;
	return (shares[company]);
}
int Companies::changeShares(int company, int value)
{
	shares[company] += value;
	return (shares[company]);
}

//Orphan functions
int Companies::getOrphans(int company)
{
	return (orphans[company]);
}
int Companies::setOrphans(int company, int value)
{
	orphans[company] = value;
	return (orphans[company]);
}
int Companies::changeOrphans(int company, int value)
{
	orphans[company] += value;
	return (orphans[company]);
}

//City functions
bool Companies::getCity(int company, int city)
{
	return(cities[company][city]);
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

//Started functions
bool Companies::getStarted(int company)
{
	return (started[company]);
}
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

//Recievership functions
bool Companies::getRecievership(int company)
{
	return (recievership[company]);
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

//Turn Order functions
int Companies::getOrder(int company)
{
	return (order[company]);
}
int Companies::setOrder(int company, int turn)
{
	order[company] = turn;
	return (order[company]);
}
int Companies::getTurnorders(int companyTurnorder[])
{
	for (int i = 0; i < maxCompanies; i++)
	{
		companyTurnorder[order[i]] = i; //Place local order in turnorder
	}
	return(0);
}
int Companies::setTurnorders()
{
	// Determine  company turn order		
	// do not change external turn order array
	int temp;
	int Turnorder[maxCompanies];
	for (int i = 0; i < maxCompanies; i++)
	{
		Turnorder[order[i]] = i; //Place local order in turnorder
	}
	for (int i = 0; i < maxCompanies - 1; i++)
	{
		for (int j = 0; j < maxCompanies - i - 1; j++)
		{
			if (valuation[Turnorder[j]] < valuation[Turnorder[j + 1]])
			{
				temp = Turnorder[j];
				Turnorder[j] = Turnorder[j + 1];
				Turnorder[j + 1] = temp;
			}
		}
	}
	//Store new turn order in local turn order
	for (int i = 0; i < maxCompanies; i++)
	{
		order[Turnorder[i]] = i;
	}
	return(0);
}
/*
int Companies::getorderCompany(int oldTurnorder[])
{
 for (int j=0; j< maxCompanies; j++)
 {
    oldTurnorder[turnorder[j]]=j; 
 }
 return 0;
}
int Companies::getTurn(int company)
{
	return (order[company]);
}
int Companies::getNext(int order)
{
	int next = maxCompanies;
	for (int j = 0; j < maxCompanies; j++)
	{
		if (order == order[j])
		{
			next = j;
		}
	}
	return (next);
}
int Companies::setTurnorders(int company, int direction)
{
	int turnorderChange = 0;

	if (direction < 0) // Valuation decrement
	{
		for (int j = 0; j < maxCompanies; j++)
		{
			if ((turnorder[company] < turnorder[j]) && (valuation[company] < valuation[j]))
			{
				turnorder[j] --; // bump up j one
				turnorderChange++; // bumn down company one
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
				turnorderChange--; // bumn up company one
			}
		}
		turnorder[company] += turnorderChange;
	}
	return(turnorder[company]);
}
*/
// Complex Get Routines
bool Companies::getAvailable(int company, int techLevel)
{
    return ((available[company] <= techLevel));
}
void Companies::getInfo(int company)
{
	cout << name[company] << "Cash: $" << cash[company] << netprofit[company] << " val $" <<
		valuation[company] << " shr " << shares[company] << " pres " <<
		orphans[company] << " orp " << president[company] << " TO " <<
		order[company] << " strt " << started[company] << "sold " << sold[company] << endl;
		return;
}



