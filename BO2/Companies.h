#pragma once


class Companies
{
public:
	
	Companies(int cashVal[maxCompanies], int netprofitVal[maxCompanies], int valuationVal[maxCompanies], int sharesVal[maxCompanies], int orphansVal[maxCompanies], int presidentVal[maxCompanies], int turnorderVal[maxCompanies], bool startedVal[maxCompanies], bool soldVal[maxCompanies], bool recievershipVal[maxCompanies]);


	int getCash(int company);
	int getPresident(int company);
	int getValuation(int company);
	int getNetprofit(int company);
	int getShares(int company);
	int getOrphans(int company);
    bool getStarted(int company);
	bool getSold(int company);
	bool getAvailable(int company, int techLevel);
	bool getRecievership(int company);
	int getTurn(int company);
	bool getCity(int company, int city);

    int getNext(int order);
    void getInfo(int company);

    int setCash(int company, int cash);
    int setNetprofit(int company, int netprofit);
    int setPresident(int company, int player);
	int setCity(int company, int city);
    int setStarted(int company);
    int setSold(int company);
	int setRecievership(int company);
    int clearSold();
	int clearSold(int company);
	int clearStarted(int company);
	int clearRecievership(int company);
	int clearCity(int company, int city);


    int getorderCompany(int oldTurnorder[]);
    //Precondition: The current turnorders of each companies are stored in turnorder.
    //Postcondition: This values are stored in oldTurnorder with the first company index
    // in 0, the second in 1, ...

    int setInitialValuation(int company, int value);
    int setTurnorder(int company, int direction);
	int setTurn(int company, int turn);



    int increaseValuation(int company);
	int decreaseValuation(int company);
    int changeShares(int company, int sharesVal);
    int changeOrphans(int company, int sharesVal);
	int changeCash(int company, int value);

	

	const char name[maxCompanies][35] = { "Baltimore & Ohio", "Boston & Maine", "Chesapeake & Ohio", "Illinois Central", "Erie", "New York Central","Nickel Plate", "New York New Haven & Hartford", "Pennsylvania", "Wabash" };
	const int available[maxCompanies] = { 1,1,1,3,3,1,3,1,1,3 };



private:

	int cash[maxCompanies];
	int netprofit[maxCompanies];
	int valuation[maxCompanies];
	int shares[maxCompanies];
	int orphans[maxCompanies];
	int president[maxCompanies];
	bool started[maxCompanies];
	bool sold[maxCompanies];
	int turnorder[maxCompanies];
	bool recievership[maxCompanies];
	bool cities[maxCompanies][maxCities];


};

