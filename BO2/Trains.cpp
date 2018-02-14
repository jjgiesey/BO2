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
	return (cost[indexVal]);
}

int Trains::priceTrainForSale()
{
	int k = 0;
	while (owner[k] != -1)
	{
		k++;
	}
	cout << "Train " << k << " is for sale for $" << cost[k] << endl;
	return (cost[k]);
}

int Trains::buyTrainForSale(int companyVal)
{
	int k = 0;
	while (owner[k] != -1)
	{
		k++;
	}
	cout << "Company bought train " << k << " for $" << cost[k] << endl;
	owner[k] = companyVal;
	return (cost[k]);
}

int Trains::scrapTrainOfCompany(int indexVal, int companyVal)
{
	if (owner[indexVal - 1] == companyVal)
	{
		owner[indexVal - 1] = -10;
		cout << "Train " << indexVal << " has been scrapped for for $" << scrap[indexVal - 1] << endl;
		return (scrap[indexVal - 1]);
	}
	else
	{
		cout << "The company does not own the train to scrap \n";
		return (0);
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

int Trains::getTechLevel(int currentTechLevel)
{
	int k = 0;
	while (owner[k] != -1)
	{
		k++;
	}
	if (level[k-1] != currentTechLevel)
		cout << "NEW TECH LEVEL IS " << level[k-1] << endl;
	return level[k - 1];
}



