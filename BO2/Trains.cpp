#include "stdafx.h"
#include "Trains.h"
#include <iostream>

using namespace std;


Trains::Trains( int ownerVal[30])
{
	for (int k = 0; k < 30; k++)
	{
		owner[k] = ownerVal[k];
	}
}


int Trains::getCost(int indexVal)
{
	return (cost[indexVal-1]);
}

int Trains::priceTrainForSale()
{
	int k = 0;
	while ((owner[k] != -1) && (k < maxTrains))
	{
		k++;
	}
	if (k < maxTrains)
	{
		cout << "Train " << k << " is for sale for $" << cost[k] << endl;
	}
	return (cost[k]);
}

int Trains::buyTrainForSale(int companyVal)
{
	int k = 0;
	while ((owner[k] != -1) && (k < maxTrains))
	{
		k++;
	}
	if (k >= 30)
	{
		cout << "There are no more trains for sale.";
		return (0);
	}
	else
	{
		cout << "Company bought train " << k << " for $" << cost[k] << endl;
		owner[k] = companyVal;
		return (cost[k]);
	}
}

int Trains::scrapTrainOfCompany(int indexVal, int companyVal)
{
	if ( (indexVal<1) || (indexVal>30))
	{
		cout << "The company does not own the train to scrap \n";
		cin.clear();
		cin.ignore(10, '\n');
		return (0);
	}
	else if ((owner[indexVal - 1] != companyVal))
	{
		cout << "The company does not own the train to scrap \n";
		return (0);
	}
	else
	{
		owner[indexVal - 1] = -10;
		cout << "Train " << indexVal << " has been scrapped for for $" << scrap[indexVal - 1] << endl;
		return (scrap[indexVal - 1]);
	}
}

int Trains::getServiceCapacity(int companyVal)
{
	int capacity = 0;
	for (int k = 0; k < 30; k++)
	{
		if (owner[k] == companyVal)
		{
			capacity = capacity + level[k];
		}
	}
	return(capacity);
}


int Trains::getCompanyTrains(int companyVal)
{
	int numberTrains = 0;
	for (int k = 0; k < 30; k++)
	{
		if (owner[k] == companyVal)
		{
			cout << index[k] << ": Train " << index[k] << " with scrap value $" << scrap[k] << endl;
			numberTrains++;
		}
	}
	return (numberTrains);
}

int Trains::scrapCompanyTrains(int companyVal)
{
	int numberTrains = 0;
	for (int k = 0; k < 30; k++)
	{
		if (owner[k] == companyVal)
		{
			owner[k] = -10;
			cout << "Train " << index[k] << " has been scrapped for for $" << scrap[k] << endl;
			return (scrap[k]);
		}
	}
	return (numberTrains);
}


int Trains::getTechLevel(int currentTechLevel)
{
	int k = 0;
	while ((owner[k] != -1) && (k < maxTrains))
	{
		k++;
	}
	if (level[k-1] != currentTechLevel)
		cout << "NEW TECH LEVEL IS " << level[k-1] << endl;
	return level[k - 1];
}

int Trains::getTrainOwner(int indexVal)
{
	return(owner[indexVal-1]);

}

int Trains::setTrainOwner(int indexVal, int player)
{
	owner[indexVal-1] = player;
	return(owner[indexVal-1]);

}


