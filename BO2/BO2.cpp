
#include "stdafx.h"
#include "Trains.h"
#include "TechLevels.h"
#include "Companies.h"
#include "Players.h"
#include "Cities.h"
#include <string>
#include <fstream>

using namespace std;

void setupPlayers(int orderPlayers[]);
//Precondition: None
//Postcondition: After running all the players will be loaded into the class players
// with initial values and turn orders set

int setGame(int numberPlayers);
//Precondition: number of players has been set and passed in numberPlayers
//Postcondition: game conditions set and current tech level is passed.
//Game will resume at beginning of market round


int setPlayerTurnorder( int order[], int numberPlayers);
// Preconditions: Current player cash and turn order are in playerNetworth and playerTurnorder.
//				The number of players is passed in numberPlayers.
// Postcondition: playerTurnorder is reevaluated so that the lowest cash is first (order =0) and the highest is last (order = numberPlayers).
//				Returns 0 if successful.

int Sorter(int Values[], int Order[], int Size);
//Preconditions: An array with maginitudes stored in Values and the order is stored in Order (0 first, 1 second, ...)
//				The size of the arrays are stored in Size
//Postcondition: Order is modified so that the smallest value has order 0 the second smallest has order 1 ...

void setPlayerNetworth();
//Precondition: players object has current cash and shares. Companies has current valuations
//Postcondition: players networth is calculated.

int getPlayer(int order);
//Precondition: players is poulated. order is a value < numberPlayers
//Postcondition: the player number with that order is returned.

void setRandomTurnorder();
//Precondition: players object is initialized with cash and turnorder. NumberPlayers is set.
//Postcondition: cash is set to zero and players have random values in turnorder

bool attemptBuy(int player);
//Precondition: player < numberPlayers
//Postcondition: returns 1 if successfull and handles all the buying transactions

bool attemptSell(int player);
// This function will return a 1 when the player has sucessfully sold a stock for their turn.

bool attemptOrphan(int player);
// This function will return a 1 when a player has successfully had a company buy back orphaned stock.

int playerSharesOwned (int company);
//Preconditions: For the company - company the number of shares owned by players is 
// in playerShares.
//Postconditions: function returns the sum of shares currently owned by players


int setCompanyPresident(int president);
// Preconditions: currentCompany is a vaild company. The shares ownd by players is passed through playerShares and the current president it passed
// through companyPresident
// Postcondidtion: The number of shares owned by each player is compared and if a new player has more shares their number is returned through setCompanyPresident.
// If not the old president is passed.

void setCompanyValuation(int company, int netProfitChange, char companyDividenPlan);
//Preconditions: For the company given by CurrentCompany that had a net profit change given by netProfitChange (decrease = -1, increase = 1
// and same = 0) and the decision to withhold (w) or distribute (d) dividens given in companyDividenPlan. Function also uses companyValuations
//Postcondition: Valuation of company is decrease if it had a decrease in net profit. It increase if net profit increased and dividens were paied. 
//Otherwise valuation stays the same.

int reduceForOrphans();

int reduceForNoProfit(int company);
// Preconditions: 

void attemptScrapTrain(int company);
// Precondition: Company index - postitive intger
// Postcondition: Train is scrapped and money added to company or error given

void attemptBuyTrain(int company);
// Precondition: Company index - postitive intger
//Postcondition: Ifunds sufficient, company is designated owner of train and cost stutracted from cash.

void attemptBuildTrack(int company);
// Precondition: Company index - postitive intger


void setCompanyDividens(int currentCompany, char companyDividenPlan);
//Preconditions: For the current company given in currentCompany to pay dividens to shareholders and itself. Uses companyNetprofit, companySharesowned, and playerShares.
//Postcondition: Profits distributed to companyCash and playerCash

char readValue(ifstream& inputStream, char cArray[]);
//Precondtions: Open stream in in inputStrean and character array is returned in cArray
//Postcondition: Will return last character read.

char findEOL(ifstream& inputStream);
//Precondition: Stream to be read for end of line is in inputStream
//				It is expected that all relevant values have been read
//Postcondition: Stream cleared. Last character returned. Should be /n if successful

int getFileData(char pfileName[], int orderPlayer[]);

int getManualData(int orderPlayers[]);

int pushFileData(char pFilename[]);


void showPlayerInfo();


const int totalCash = 1500;




int trainOwner[30] = { -1,-1, -1, -1,-1, -1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1 };
int companyCash[maxCompanies] = { 0,0,0,0,0,0,0,0,0,0 };
int companyNetprofit[maxCompanies] = { 0,0,0,0,0,0,0,0,0,0 };
int companyValuation[maxCompanies] = { 1,1,1,1,1,1,1,1,1,1 };
int companyShares[maxCompanies] = { 10,10,10,10,10,10,10,10,10,10 };
int companyOrphans[maxCompanies] = { 0,0,0,0,0,0,0,0,0,0 };
int companyPresident[maxCompanies] = { 5,3,5,5,5,5,5,5,5,5 };
int companyTurnorder[maxCompanies] = { 0,1,2,3,4,5,6,7,8,9 };
bool companyStart[maxCompanies] = { 0,0,0,0,0,0,0,0,0,0 };
bool companySold[maxCompanies] = { 0,0,0,0,0,0,0,0,0,0 };
bool companyRecievership[maxCompanies] = { 0,0,0,0,0,0,0,0,0,0 };

Trains  trains (trainOwner);
TechLevels techLevels;
Cities cities;
Companies companies(companyCash, companyNetprofit, companyValuation, companyShares, companyOrphans, companyPresident, companyTurnorder,companyStart, companySold, companyRecievership);
//int continueConfirm;
//int traincost;
//int currentTrain;
//int cash = 100;



//int scrapTrain;
//int buildAmount;
int numberPlayers;
int techLevel = 1;
char testArray[30];

//int levelValuation;
Players players[maxPlayers];

int main()
{
	// BO Banker with Object
	char option;
	int test;
	int company;
	int player;
	int profit;
	char confirm;

	int orderCompany[maxCompanies];
	int orderPlayers[maxPlayers];
	char wfileName[30];


	cout << "BO Banker Program \n \n";

	// Set up options

	cout << "Name of game data file:";
	cin >> wfileName;
	strcat_s(wfileName, ".csv");
	cout << "Enter the option of how you want to start the game:\n";
		cout << "What would you like to do? \n";
		cout << "   'n' = Start new game\n";
		cout << "   'm' = Manually enter game state \n";
		cout << "   'f' = Read game state from file\n";
		cout << "Option: ";
		cin >> option;
		cout << endl;

		switch (option)
		{
		case 'm':
			techLevel = getManualData(orderPlayers);
			break;
		case 'f':
			techLevel = getFileData(wfileName, orderPlayers);
		break;
		default:
			setupPlayers(orderPlayers);
		}
		//Sort players by cash
		test = setPlayerTurnorder(orderPlayers, numberPlayers);
		setPlayerNetworth();
		for (int i = 0; i < numberPlayers; i++)
			players[i].getInfo();
		for (int j = 0; j < maxCompanies; j++)
		{
			if (companies.getStarted(j) == 1)
				cout << j << ": " << companies.name[j] << " has $" << companies.getCash(j) << " and " << companies.getShares(j) << " regular shares and " << companies.getOrphans(j) << " orphaned shares valued at $" << valuations[companies.getValuation(j)] << " per share \n";
		}
		cout << endl;

		pushFileData(wfileName);


	do
	{
		// Market Phase

		int numberPasses = 0;

		cout << "\nMARKET PHASE \n";
		while (numberPasses < numberPlayers)
		{
			numberPasses = 0;
			for (int i = 0; i < numberPlayers; i++)
			{
				player =orderPlayers[i];
				int playerSuccess = 0;
				do
				{
					cout << "\nCURRENT PLAYER:" << players[player].name << " has $" << players[player].cash << "cash.\n";
					cout << "What would you like to do? \n";
					cout << "   'p' = pass \n";
					cout << "   'o' = orphan share buyback \n";
					cout << "   's' = sell shares\n";
					cout << "   'b' = buy shares\n";
					cout << "   'f' = finished with turn after selling \n ";
					cout << "Option: ";
					cin >> option;
					cout << endl;

					switch (option)
					{
					case 'p':
						numberPasses++;
						cout << players[player].name << " passes. Pass " << numberPasses << " of " << numberPlayers << endl;
						playerSuccess = 1;
					break;
					case 'o':
						if (attemptOrphan(player))
							playerSuccess = 1;
						else
							playerSuccess = 0;
					break;
					case 's':
						attemptSell(player);
					break;
					case 'b':
						if (attemptBuy(player))
							playerSuccess = 1;
						else
							playerSuccess = 0;
					break;
					case 'f':
						playerSuccess = 1;
					break;
					default:
						cout << "Invalid option. Try agian. \n";
					}
				}
				while (playerSuccess != 1);
			} 
			// Clear sold array
			for (int i = 0; i < numberPlayers; i++)
			{
				for (int j = 0; j < maxCompanies; j++)
				{
					players[i].sold[j] = 0;
				}
			}
			cout << "\nEnd of Market Turn \n";		
			setPlayerNetworth();
			for (int i = 0; i < numberPlayers; i++)
				players[i].getInfo();
			for (int j = 0; j < maxCompanies; j++)
			{
				if (companies.getStarted(j) == 1)
					cout << j << ": " << companies.name[j] << " has $" << companies.getCash(j) << " and " << companies.getShares(j) << " regular shares and " << companies.getOrphans(j) << " orphaned shares valued at $" << valuations[companies.getValuation(j)] << " per share \n";
			}
			cout << endl;

		}
		cout << "All players have passed \n";
		cout << "\nEnd of Market Round \n";
		test = reduceForOrphans();
		// Build Phase

		for (int l = 0; l < 2; l++)
		{
			cout << "Begin Build Round " << l + 1 << endl;
			int j = 0;
			test = companies.getorderCompany(orderCompany);
			for (int j = 0; j < maxCompanies; j++)
			{
				company = orderCompany[j];
				if (companies.getStarted(company))
				{
					cout << endl << companies.name[company] << "building phase. \n\n";
					cout << companies.name[company] << " has $ " << companies.getCash(company) << " Would you like to scrap a train ? (y/n): ";
					cin >> confirm;
					while ((confirm != 'n') && (confirm != 'N'))
					{
						attemptScrapTrain(company);
						cout << companies.name[company] << " has $ " << companies.getCash(company) << " Would you like to scrap a train ? (y/n): ";
						cin >> confirm;
					}
					cout << companies.name[company] << " has $ " << companies.getCash(company) << " Would you like to buy the next train ? (y/n): ";
					cin >> confirm;
					while ((confirm != 'n') && (confirm != 'N'))
					{
						if ((confirm == 'y') || (confirm == 'Y'))
						{
							attemptBuyTrain(company);
						}
						cout << companies.name[company] << " has $ " << companies.getCash(company) << " Would you like to buy the next train ? (y/n): ";
						cin >> confirm;
					}
					cout << companies.name[company] << " has $ " << companies.getCash(company) << " Would you like to buy track ? (y/n): ";
					cin >> confirm;
					while ((confirm != 'n') && (confirm != 'N'))
					{
						if ((confirm == 'y') || (confirm == 'Y'))
						{
							attemptBuildTrack(company);
						}
						cout << companies.name[company] << " has $ " << companies.getCash(company) << " Would you like to buy track ? (y/n): ";
						cin >> confirm;
					}
				
						// Run Company
					cout << companies.name[company] << " finished building. \n";
					int netprofitChange;
					do
					{
						cout << "Enter new net profit $";
						cin >> profit;

						if ((profit >= 0) && (profit < 1000))
						{
							cout << "New net profit for " << companies.name[company] << " is $" << profit << ". Is this correct? (y/n): ";
							cin >> confirm;
						}
						else
						{
							cout << "Invalid entry. Please try again. \n";
							cin.clear();
							cin.ignore(10, '\n');
							confirm = 'n';
						}
					} while (confirm != 'y');
					if (profit == 0)
					{
						netprofitChange = -2;
						cout << "Net profit for " << companies.name[company] << " is 0. Company is unprofitable \n";
					}
					else if (profit > companies.getNetprofit(company))
					{
						netprofitChange = 1;
						cout << "Net profit for " << companies.name[company] << " has increased. \n";
					}
					else if (profit < companies.getNetprofit(company))
					{
						netprofitChange = -1;
						cout << "Net profit for " << companies.name[company] << " has decreased. \n";
					}
					else
					{
						netprofitChange = 0;
						cout << "Net profit for " << companies.name[company] << " has remained the same. \n";
					}
					companies.setNetprofit(company, profit);
					do
					{
						cout << "Does " << companies.name[company] << " want to distribute=d or withold=w dividens? ";
						cin >> option;
						if (option == 'd')
						{
							cout << companies.name[company] << " would like to distribute dividens, Is this correct? (y/n): ";
							cin >> confirm;
						}
						else if (option == 'w')
						{
							cout << companies.name[company] << " would like to withhold dividens, Is this correct? (y/n): ";
							cin >> confirm;
						}
						else
						{
							cout << "Invalid entry. Please try again \n";
							confirm = 'n';
						}
					} while (confirm != 'y');
					setCompanyDividens(company, option);
					setCompanyValuation(company, netprofitChange, option);
				}
			}
			setPlayerNetworth();
			setPlayerTurnorder(orderPlayers, numberPlayers);
			for (int i = 0; i < numberPlayers; i++)
				players[i].getInfo();
			for (int j = 0; j < maxCompanies; j++)
			{
				if (companies.getStarted(j) == 1)
					cout << j << ": " << companies.name[j] << " has $" << companies.getCash(j) << " and " << companies.getShares(j) << " regular shares and " << companies.getOrphans(j) << " orphaned shares valued at $" << valuations[companies.getValuation(j)] << " per share \n";
			}
		}
		pushFileData(wfileName);
		cout << "\nEnd of Business Rounds " << endl;;
	} while (techLevel < 6);
	return 0;
}


void setupPlayers( int orderPlayers[])
{
	// Set up players names
	char name[20];
	long int currentTime = static_cast<long int>(time(0)); //Generate random seed
	srand(currentTime);



//*****************************************
	cout << "Number of players: ";
	cin >> numberPlayers;
	cout << "There are " << numberPlayers << " of " << maxPlayers << " players. \n";
	cout << "Enter player names in any order. \n";
	for (int i = 0; i < numberPlayers; i++)
	{
		cout << "Player " << i + 1 << ": ";
		cin >> name;
		cout << "\n";
		strcpy_s(players[i].name, name);
		players[i].cash = rand() % 10000; // assign random number
		players[i].turnorder = i;
		orderPlayers[i] = i;
	}
	//Sort players by cash
	int test = setPlayerTurnorder(orderPlayers, numberPlayers);


	for (int i = 0; i < numberPlayers; i++)
	{
		players[i].cash = totalCash / numberPlayers;
		players[i].networth = 0;
		for (int j = 0; j < maxCompanies; j++)
		{
			players[i].shares[j] = 0;
			players[i].sold[j] = 0;
		}
		players[i].getInfo();
	}


}



void setPlayerNetworth()
{
	for (int i = 0; i < numberPlayers; i++)
	{
		int sum = players[i].cash;
		for (int j = 0; j<maxCompanies; j++)
		{
			sum += players[i].shares[j] * valuations[companies.getValuation(j)];
		}
		players[i].networth = sum;
	}
	return;
}


int getPlayer(int order)
{
	for (int i = 0; i < numberPlayers; i++)
	{
		if (players[i].turnorder == order)
			return (i);
	}
	return (-1);
}

bool attemptBuy(int player)
{
	// Player requests to buy

	int numberShares;
	int requestValuation;
	int test;
	int option;
	int company;

	cout << "Select company to buy from\n";
	//List regular shares for sale
	for (int j = 0; j < maxCompanies; j++)
	{
		if (companies.getAvailable(j, techLevel))
		{
			if (players[player].sold[j] != 1)
			{
				if (companies.getStarted(j) == 0)
				{
					cout << j << ": " << companies.name[j] << " is available to be started at $" << valuations[techLevels.lowVal[techLevel - 1]] << ", $" << valuations[techLevels.medVal[techLevel - 1]] << " or $" << valuations[techLevels.highVal[techLevel - 1]] << " per share\n";
				}
				else
				{
					cout << j << ": " << companies.name[j] << " has $" << companies.getCash(j) << " and " << companies.getShares(j) << " regular shares and " << companies.getOrphans(j) << " orphaned shares valued at $" << valuations[companies.getValuation(j)] << " per share \n";
				}
			}
		}
	}
	cout << "Selection:";
	cin >> company;
	// Three options: not avialable, buy regular shares, buy orphaned shares.

	if ((company < 0) || (company > maxCompanies + maxCompanies - 1)) // Company not avialable
	{
		cout << "Company  nubmer" << company << " is not valid. Please try again. \n";
		cin.clear();
		return 0;
	}
	else if (players[player].sold[company] != 0)
	{
		cout << "Can not buy shares of company sold during this round. Please try again. \n";
		cin.clear();
		return 0;
	}
	else if (company < maxCompanies) // Regular Shares
	{
		if (!companies.getAvailable(company, techLevel))
		{
			cout << "Company " << companies.name[company] << " is not available. \n";
			return 0;
		}
		// Check to see if company has not been started and needs intial value set
		if (!companies.getStarted(company))
		{
			cout << "\t 1: $" << valuations[techLevels.lowVal[techLevel - 1]] << endl;
			cout << "\t 2: $" << valuations[techLevels.medVal[techLevel - 1]] << endl;
			cout << "\t 3: $" << valuations[techLevels.highVal[techLevel - 1]] << endl;
			cout << "Select inital company valuation for " << companies.name[company] << " :";
			cin >> option;
			if (option == 1)
				requestValuation = techLevels.lowVal[techLevel - 1];
			else if (option == 2)
				requestValuation = techLevels.medVal[techLevel - 1];
			else if (option == 3)
				requestValuation = techLevels.highVal[techLevel - 1];
			else
			{
				cout << "Request not valid. Please try again.";
				return 0;
			}
			cout << companies.name[company] << " has requested an intial valuations of $" << valuations[requestValuation] << " per share \n";
		}
		else
		{
			requestValuation = companies.getValuation(company);
		}
		cout << "How many shares regular shares of " << companies.name[company] << " do you want to buy: ";
		cin >> numberShares;
		// check validity of request
		if (numberShares < 0)
		{
			cout << "Request not valid. Please try again. \n";
			cin.clear();
			return 0;
		}
		if (numberShares > companies.getShares(company))
		{
			cout << "Only " << companies.getShares(company) << " shares available.\n";
			cin.clear();
			return 0;
		}
		else if (numberShares*valuations[requestValuation] > players[player].cash)
		{
			cout << "Need " << numberShares * valuations[requestValuation] << " for purchase\n";
			return 0;
		}
		else // Proceed with sale
		{
			test = companies.setStarted(company);
			test = companies.setInitialValuation(company, requestValuation);
			test = companies.changeShares(company, -numberShares);
			test = companies.changeCash(company, (numberShares * valuations[requestValuation]));
			players[player].shares[company] += numberShares;
			players[player].cash -= (numberShares * valuations[requestValuation]);
			cout << companies.name[company] << " now has $" << companies.getCash(company) << " and " << companies.getShares(company) << " regular shares and " << companies.getOrphans(company) << " orphaned shares valued at $" << valuations[companies.getValuation(company)] << " per share \n";
			cout << players[player].name << " now owns " << players[player].shares[company] << " shares of " << companies.name[company] << " and $" << players[player].cash << endl;
			test = setCompanyPresident(company);
			test = companies.setTurnorder(company, 1);
			if (companies.getOrphans(company) != 0) // Offer Orphans if any
			{
				cout << "How many ORPHAN shares of " << companies.name[company] << " do you want to buy: ";
				cin >> numberShares;
				// check validity of request
				if (numberShares < 0)
				{
					cout << "Request not valid. Please try again. \n";
					cin.clear();
					return false;
				}
				if (numberShares > companies.getOrphans(company))
				{
					cout << "Only " << companies.getOrphans(company) << " shares available.\n";
					cin.clear();
					return false;
				}
				else if (numberShares*valuations[requestValuation] > players[player].cash)
				{
					cout << "Need " << numberShares * valuations[requestValuation] << " for purchase\n";
					return false;
				}
				else // Proceed with sale
				{
					test = companies.changeOrphans(company, -numberShares);
					players[player].shares[company] += numberShares;
					players[player].cash -= (numberShares * valuations[requestValuation]);
					cout << companies.name[company] << " now has $" << companies.getCash(company) << " and " << companies.getShares(company) << " regular shares and " << companies.getOrphans(company) << " orphaned shares valued at $" << valuations[companies.getValuation(company)] << " per share \n";
					cout << players[player].name << " now owns " << players[player].shares[company] << " shares of " << companies.name[company] << " and $" << players[player].cash << endl;
					test = setCompanyPresident(company);
				}
			}
		}
		return true;
	}
	return false;
}


bool attemptSell(int player)
	// This function will return a 1 when the player has sucessfully sold a stock for their turn.
{
	int numberShares;
	int test;
	int company;

	cout << players[player].name << " wants to sell stock. \n";
	for (int j = 0; j < maxCompanies; j++)
	{
		if ((players[player].shares[j] != 0) && (players[player].sold[j] != 1))
		{
			cout << j << " " << companies.name[j] << ": " << players[player].shares[j] << " at $" << valuations[companies.getValuation(j)] << " per share \n";
		}
	}
	cout << "Select company to sell from:";
	cin >> company;
	if ((company < 0) || (company > maxCompanies - 1))
	{
		
		//*************************************************************************
		cout << "Company  nubmer" << company << " is not valid. Please try again. \n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	if (players[player].sold[company] == 1)
	{
		cout << "Company  nubmer" << company << " has been sold by you this turn. You must wait until a later turn to sell more. \n"; 
		cin.clear();
		cin.ignore(10, '\n');
		return false; 
	}
	cout << "How many shares of " << companies.name[company] << " do you want to sell: ";
	cin >> numberShares;
	// check validity of request
	if (numberShares< 0)
	{
		cout << "Request not valid. Please try again. \n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	if (numberShares > players[player].shares[company])
	{
		cout << "Only " << players[player].shares[company] << " shares owned. Reduce request.\n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	else if (playerSharesOwned(company) <= numberShares)
	{
		cout << "Can not sell all shares of company " << companies.name[company] << ". Reduce request. \n";
		return false;
	}
	else  // Proceed with sale
	{
        test = companies.changeOrphans(company,numberShares);
        players[player].shares[company] -= numberShares;
        players[player].cash += (numberShares * valuations[companies.getValuation(company)]);
 		// reduce evaluation if first sale of round
		if (!companies.getSold(company))
		{
			test = companies.decreaseValuation(company);
			cout << companies.name[company] << " has been sold this turn its valuation has been reduced to $" << valuations[companies.getValuation(company)] << " per share. \n";
		}
		cout << companies.name[company] << " now has $" << companies.getCash(company) << " and " << companies.getShares(company) << " regular shares and " << companies.getOrphans(company) << " orphaned shares valued at $" << valuations[companies.getValuation(company)] << " per share \n";
		cout << players[player].name << " now owns " << players[player].shares[company] << " shares of " << companies.name[company] << " and $" << players[player].cash << endl;
		test = setCompanyPresident(company);
		players[player].sold[company] = 1;
		return true;
	}
	return false;
}

int playerSharesOwned(int company)
{
    int shareSum = 0;
    for (int i = 0; i < numberPlayers; i++)
    {
        shareSum += players[i].shares[company];
    }
    return shareSum;
}


bool attemptOrphan(int player)
{
	int numberShares;
	int numberOrphanCompaniesControlled = 0;
	int company;
	int test;

	cout << players[player].name << " wants a company to buy orphaned stock \n";
	cout << "Select company to buy its orphaned stock:\n";
	//List orphaned shares for sale
	for (int j = 0; j < maxCompanies; j++)
	{
		if (companies.getOrphans(j) != 0 && player == companies.getPresident(j))
		{
			cout << j << ": " << companies.name[j] << " has " << companies.getOrphans(j)<< " orphaned shares available at $" << valuations[companies.getValuation(j)] << " per share. \n";
			numberOrphanCompaniesControlled++;
		}
	}
	if (numberOrphanCompaniesControlled == 0)
	{
		cout << players[player].name << " owns no companies with orphan stocks \n";
		return 0;
	}
	cin >> company;
	if ((company < 0) || (company > maxCompanies - 1))
	{
		cout << "Company  nubmer" << company << " is not valid. Please try again. \n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	if (player != companies.getPresident(company))
	{
		cout << "Only " << companies.name[company] << " president, " << players[companies.getPresident(company)].name << " can buy orphan shares on behalf of company \n";
		return false;
	}
	cout << "How many orphaned shares of " << companies.name[company] << " do you want to buy back: ";
	cout << companies.name[company] << " has $" << companies.getCash(company)<< endl;
	cin >> numberShares;
	// check validity of request
	if (numberShares< 0)
	{
		cout << "Request not valid. Please try again. \n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	if (numberShares > companies.getOrphans(company))
	{
		cout << "Only " << companies.getOrphans(company) << " shares available.\n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	else if (numberShares*valuations[companies.getValuation(company)] > companies.getCash(company))
	{
		cout << "Need " << numberShares*valuations[companies.getValuation(company)] << " for purchase\n";
		return false;
	}
	else
	{

        test = companies.changeOrphans(company,-numberShares);
        test = companies.changeShares(company,numberShares);
        test = companies.changeCash(company, -numberShares*valuations[companies.getValuation(company)]);
        cout << companies.name[company] << " now has $" << companies.getCash(company) << " and " << companies.getShares(company) << " regular shares and " << companies.getOrphans(company) << " orphaned shares \n";
  		return true;
	}
}

int setCompanyPresident(int company)
{
	int president = companies.getPresident(company);
	for (int i = 0; i < numberPlayers; i++)
	{
		if (players[i].shares[company] > players[president].shares[company])
		{
			companies.setPresident(company,i);
			president = i;
		}
	}
	cout << "The president for " << companies.name[company] << " is " << players[president].name << endl;
	return(president);
}

void attemptScrapTrain(int company)

	{
		int train;

		if (trains.getCompanyTrains(company) <= 0)
		{
			cout << " Company has no trains to scrap \n";
		}
		else
		{
			cout << "Select train to scrap: ";
			cin >> train;
			companies.changeCash(company, +trains.scrapTrainOfCompany(train, company));
			cout << companies.name[company] << " now has $" << companies.getCash(company) << endl;
		}
		return;
	}

	void attemptBuyTrain(int company)
	{
		if (companies.getCash(company) >= trains.priceTrainForSale())
		{
			companies.changeCash(company, -trains.buyTrainForSale(company));
			cout << companies.name[company] << " now has $" << companies.getCash(company) << endl;
			techLevel = trains.getTechLevel(techLevel);
		}
		else
		{
			cout << "Company does not have enough cash to buy train. \n";
		}
		return;
	}

	void attemptBuildTrack(int company)
	{
		int amount;
		cout << "What is the total track build abount: ";
		cin >> amount;
		if ((amount < 0) || (amount > 500))
		{ 
			cout << "$" << amount << " is not a valid amount. \n";
			cin.clear();
			cin.ignore(10, '\n');
		}
		else if (companies.getCash(company) >= amount)
		{
			companies.changeCash(company,-amount);
			cout << companies.name[company] << " now has $" << companies.getCash(company) << endl;
		}
		else
		{
			cout << "Company does not have enough cash to build this amount of track \n";
		}
		return;
	}

    void setCompanyValuation(int company, int netProfitChange, char companyDividenPlan)
{
	if (netProfitChange < 0)
	{
		if (companies.getNetprofit(company) != 0)
		{
			companies.decreaseValuation(company);
			cout << companies.name[company] << " valuation decreases to $" << valuations[companies.getValuation(company)] << " per share. \n";
		}
		else
		{
			// Unprofitable Company
			int badPresident = companies.getPresident(company);
			companies.decreaseValuation(company);
			companies.decreaseValuation(company);
			cout << companies.name[company] << " valuation decreases to $" << valuations[companies.getValuation(company)] << " per share. \n";
			companies.changeShares(company,1);
			players[setCompanyPresident(company)].shares[company] -= 1;
			cout << players[badPresident].name << " shares in " << companies.name[company] << " has been reduced to " << players[badPresident].shares[company] << " shares. \n";
			if (players[setCompanyPresident(company)].shares[company] == 0)
			{
				// Company goes into recievership
				cout << companies.name[company] << " goes into recievership. \n";
				companies.setRecievership(company); // Place into revievership
				companies.clearStarted(company); // Clear started flag
				companies.setInitialValuation(company, 4); //Set valuation to $50
				trains.scrapCompanyTrains(company); //Scrap all trains
				companies.setCash(company, 0); //Clear out treasurey
				companies.changeOrphans(company, -companies.getOrphans(company)); //Clear out orphans
				companies.changeShares(company, 10 - companies.getShares(company)); // Put all shares regular
				cout << companies.name[company] << " now has $" << companies.getCash(company) << " and " << companies.getShares(company) << " regular shares and " << companies.getOrphans(company) << " orphaned shares \n";
			}
		}
}
    else if ((netProfitChange > 0) && (companyDividenPlan == 'd'))
    {
        companies.increaseValuation(company);
		cout << companies.name[company] << " valuation increases to $" << valuations[companies.getValuation(company)] << " per share. \n";

    }
    else
    {
        cout << companies.name[company] << " valuation remains the same at $" << valuations[companies.getValuation(company)] << " per share. \n";
    }
    return;
}

	void setCompanyDividens(int company, char option)
	{
		companies.setCash(company, companies.getCash(company) + companies.getShares(company) * companies.getNetprofit(company) / 10);
		if (option == 'd')
		{
			for (int i = 0; i < numberPlayers; i++)
			{
				if (players[i].shares[company] != 0)
				{
					int pDividend = players[i].shares[company]*companies.getNetprofit(company) / 10;
					players[i].cash += pDividend;
					cout << players[i].name << " recieved $" << pDividend << " from " << players[i].shares[company] << " shares of " << companies.name[company] << " and now has $" << players[i].cash << endl;
				}
			}

			return;
		}
		else
		{
			for (int i = 0; i < numberPlayers; i++)
			{
				companies.changeCash(company, +players[i].shares[company] * companies.getNetprofit(company) / 10);
			}
				cout << companies.name[company] << " now has $" << companies.getCash(company) << " and " << companies.getShares(company) << " regular shares and " << companies.getOrphans(company) << " orphaned shares \n";

			return;

		}
	}


	int reduceForOrphans()
	{
		for (int j = 0; j < maxCompanies; j++)
		{
			if (companies.getOrphans(j) != 0)
			{
				companies.decreaseValuation(j);
				cout << companies.name[j] << " valuation decreases to $" << valuations[companies.getValuation(j)] << " per share due to orphaned share. \n";
			}

		}
		return (0);
	}


	int setPlayerTurnorder(int playerTurnorder[], int numberPlayers)
	{
		// Determine  player turn order		
		// Sort players in order of cash
		int temp;
		for (int i = 0; i < numberPlayers - 1; i++)
		{
			for (int j = 0; j < numberPlayers - i - 1; j++)
			{
				if (players[playerTurnorder[j]].cash > players[playerTurnorder[j + 1]].cash)
				{
					temp = playerTurnorder[j];
					playerTurnorder[j] = playerTurnorder[j + 1];
					playerTurnorder[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < numberPlayers; i++)
			players[playerTurnorder[i]].turnorder = i;
		return(0);
	}


	int setGame(int numberPlayers)
	{
	// Rest TechLevey
		int techLevel;
		cout << "Enter current Tech Level: ";
		cin >> techLevel;
		int value;
		char confirm;
	// Reset Companies
		for (int j = 0; j < maxCompanies; j++)
		{
			if (companies.getAvailable(j, techLevel))
			{
				cout << "\n For company: " << companies.name[j] << " \n";
				cout << "Company started (y/n):";
				cin >> confirm;
				if ((confirm == 'y') || (confirm == 'Y'))
				{
					companies.setStarted(j);
					cout << "\nCompany in recievership (y/n):";
					cin >> confirm;
					if ((confirm == 'y') || (confirm == 'Y'))
					{
						companies.setRecievership(j);
						companies.clearStarted(j); // Clear started flag
						companies.setInitialValuation(j, 4); //Set valuation to $50
					}
					else
					{
						cout << "\nCash: ";
						cin >> value;
						companies.setCash(j, value);
						cout << "\nNet Profit: ";
						cin >> value;
						companies.setNetprofit(j, value);
						cout << "\nValuation: ";
						cin >> value;
						for (int n = 0; n < 26; n++)
						{
							if (valuations[n] == value)
								companies.setInitialValuation(j, n);
						}
						cout << "\nShares: ";
						cin >> value;
						companies.changeShares(j, value - 10);
						cout << "\nOrphans: ";
						cin >> value;
						companies.changeOrphans(j, value);
						cout << "\nTurn Order (0 is first): ";
						cin >> value;
						companies.setTurn(j, value);
						do
						{
							cout << "\nEnter train number of train(s) owned (0 to quit):";
							cin >> value;
							trains.setTrainOwner(value, j);
						} 
						while (value > 0);
						cout << endl;
					}
				}
			}
		}
// Reset Scrapped Trains
		do
		{
			cout << "\nEnter train number of train(s) scrapped (0 to quit):";
			cin >> value;
			trains.setTrainOwner(value, -10);
		} while (value > 0);

	// Reset Players

		for (int i = 0; i < numberPlayers; i++)
		{
			cout << "\n\nFor player: " << players[i].name << endl;
			cout << "\nCash: ";
			cin >> value;
			players[i].cash = value;
			for (int j = 0; j < maxCompanies; j++)
			{
				if (companies.getAvailable(j, techLevel))
				{
					if (companies.getStarted(j) == 1)
					{
						cout << "\nEnter number of shares of " << companies.name[j] <<  " owned: " ;
						cin >> value;
						players[i].shares[j] = value;
						cout << endl;
					}
				}
			}


		}
	return(techLevel);
	
	}

	char readValue(ifstream& inputStream, char cArray[])
	{
		char getChar;
		inputStream.get(getChar);
		int j = 0;
		while ((getChar != ',') && (getChar != '\n'))
		{
			cArray[j] = getChar;
			j++;
			inputStream.get(getChar);
		}
		cArray[j] = '\0';
		return(getChar);
	}

	char findEOL(ifstream& inputStream)
	{
		char getChar;
		do
		{
			inputStream.get(getChar);
		} while (getChar != '\n');
		return(getChar);
	}

	int getFileData(char pfileName[], int orderPlayers[])
	{
		char getChar;
		ifstream inDataStream;
		int rnumberPlayers = 0;
		inDataStream.open(pfileName);
		if (inDataStream.fail())
		{
			cout << "Input file stream open failed \n";
			return(1);
		}
		getChar = readValue(inDataStream, testArray);
		getChar = readValue(inDataStream, testArray);
		while(testArray[0] != '\0')
		{
			strcpy_s(players[rnumberPlayers].name, testArray);
			orderPlayers[rnumberPlayers] = rnumberPlayers;
			rnumberPlayers++;
			getChar = readValue(inDataStream, testArray);
		}
		numberPlayers = rnumberPlayers;
		getChar = readValue(inDataStream, testArray);
		for (int i = 0; i < numberPlayers; i++) // Read player cash
		{
			getChar = readValue(inDataStream, testArray);
			players[i].cash = atoi(testArray);
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int i = 0; i < numberPlayers; i++) // Read player cash
		{
			getChar = readValue(inDataStream, testArray);
			players[i].cash = atoi(testArray);
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) // Read player shares owned
		{
			for (int i = 0; i < numberPlayers; i++)
			{
				getChar = readValue(inDataStream, testArray);
				players[i].shares[j] = atoi(testArray);
			}
			findEOL(inDataStream);
			getChar = readValue(inDataStream, testArray);
		}
		for (int j = 0; j < maxCompanies; j++) //Read company name (and discard since fixed)
		{
			getChar = readValue(inDataStream, testArray);
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++)//Read company cash
		{
			getChar = readValue(inDataStream, testArray);
			companies.setCash(j, atoi(testArray));
			companyCash[j] = atoi(testArray);
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) //Read company net profit
		{
			getChar = readValue(inDataStream, testArray);
			companies.setNetprofit(j, atoi(testArray));
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) //Read company valuation
		{
			getChar = readValue(inDataStream, testArray);
			companies.setInitialValuation(j, atoi(testArray));
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) //Read company presidents
		{
			getChar = readValue(inDataStream, testArray);
			companies.setPresident(j, atoi(testArray));
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) //Read company shares
		{
			getChar = readValue(inDataStream, testArray);
			companies.changeShares(j, atoi(testArray) - companies.getShares(j));
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) //Read comapny orphans
		{
			getChar = readValue(inDataStream, testArray);
			companies.changeOrphans(j, atoi(testArray) - companies.getOrphans(j));
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) //Read company sold
		{
			getChar = readValue(inDataStream, testArray);
			if (atoi(testArray) == 1)
				companies.setStarted(j);
			else
				companies.clearSold(j);
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) //Read company recievership
		{
			getChar = readValue(inDataStream, testArray);
			if (atoi(testArray) == 1)
				companies.setRecievership(j);
			else
				companies.clearRecievership(j);
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++) //Read company turn order
		{
			getChar = readValue(inDataStream, testArray);
			companies.setTurn(j, atoi(testArray));
		}
		findEOL(inDataStream);
		for (int m = 0; m < maxCities; m++) // Read cities
		{
			getChar = readValue(inDataStream, testArray);
			for (int j = 0; j < maxCompanies; j++)
			{
				getChar = readValue(inDataStream, testArray);
				if (atoi(testArray) == 1)
					companies.setCity(j,m);
				else
					companies.clearCity(j,m);
			}
			findEOL(inDataStream);
		}
		getChar = readValue(inDataStream, testArray);
		for (int k = 0; k < 30; k++)
		{
			getChar = readValue(inDataStream, testArray);
		}
	//	findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
		for (int k = 0; k < 30; k++)
		{
			getChar = readValue(inDataStream, testArray);
			trains.setTrainOwner(k+1, atoi(testArray));
		}
		for (int k = 0; k < 30; k++)
		{
			if(trains.getTrainOwner(k+1)!= -1)
				techLevel = (k / 5)+1;
		}
		return(techLevel);
	}

	int getManualData(int orderPlayers[])
	{
		do
		{
			cout << "Enter number of players between 2 and 6: ";
			cin >> numberPlayers;
			cin.clear();
			cin.ignore(10, '\n');
		} while ((numberPlayers < 2) || (numberPlayers > 6));
		cout << "There are " << numberPlayers << " of " << maxPlayers << " players. \n";
		techLevel = setGame(numberPlayers);
		setPlayerNetworth();
		setPlayerTurnorder(orderPlayers, numberPlayers);
		for (int i = 0; i < numberPlayers; i++)
			players[i].getInfo();
		for (int j = 0; j < maxCompanies; j++)
		{
			if (companies.getStarted(j) == 1)
			{
				setCompanyPresident(j);
				cout << j << ": " << companies.name[j] << " has $" << companies.getCash(j) << " and " << companies.getShares(j) << " regular shares and " << companies.getOrphans(j) << " orphaned shares valued at $" << valuations[companies.getValuation(j)] << " per share \n";
			}
		}
		return(techLevel);
	}

int pushFileData(char pfileName[])
{

	ofstream outDataStream;
	outDataStream.open(pfileName);
	if (outDataStream.fail())
	{
		cout << "Output file stream open failed \n";
		return(1);
	}

	outDataStream << "Name, ";
	for (int i = 0; i < numberPlayers - 1; i++) // Save player name
	{
		outDataStream << players[i].name << ",";
	}
	outDataStream << players[numberPlayers - 1].name << "\n";
	outDataStream << "Cash, ";
	for (int i = 0; i < numberPlayers - 1; i++) // Save player cash
	{
		outDataStream << players[i].cash << ",";
	}
	outDataStream << players[numberPlayers - 1].cash << "\n";
	for (int j = 0; j < maxCompanies; j++) // Save player shares owned
	{
		outDataStream << companies.name[j] <<",";
		for (int i = 0; i < numberPlayers - 1; i++)
		{
			outDataStream << players[i].shares[j] << ",";
		}
		outDataStream << players[numberPlayers - 1].shares[j] << "\n";
	}
	outDataStream << "Names, ";
	for (int j = 0; j < maxCompanies - 1; j++) // Save company names
	{
		outDataStream << companies.name[j] << ",";
	}
	outDataStream << companies.name[maxCompanies - 1] << "\n";
	outDataStream << "Cash, ";
	for (int j = 0; j < maxCompanies - 1; j++) // Save company cash
	{
		outDataStream << companies.getCash(j) << ",";
	}
	outDataStream << companies.getCash(maxCompanies - 1) << "\n";
	outDataStream << "NetProfit, ";
	for (int j = 0; j < maxCompanies - 1; j++) // Save company netprofit
	{
		outDataStream << companies.getNetprofit(j) << ",";
	}
	outDataStream << companies.getNetprofit(maxCompanies - 1) << "\n";
	outDataStream << "Valuation, ";
	for (int j = 0; j < maxCompanies - 1; j++) //Save valuation
	{
		outDataStream << companies.getValuation(j) << ",";
	}
	outDataStream << companies.getValuation(maxCompanies - 1) << "\n";

	outDataStream << "Persident, ";
	for (int j = 0; j < maxCompanies - 1; j++) //Save valuation
	{
		outDataStream << companies.getPresident(j) << ",";
	}
	outDataStream << companies.getPresident(maxCompanies - 1) << "\n";
	outDataStream << "Shares, ";
	for (int j = 0; j < maxCompanies - 1; j++) // Save Company shares
	{
		outDataStream << companies.getShares(j) << ",";
	}
	outDataStream << companies.getShares(maxCompanies - 1) << "\n";
	outDataStream << "Orphans, ";
	for (int j = 0; j < maxCompanies - 1; j++) // Sace Company orphans
	{
		outDataStream << companies.getOrphans(j) << ",";
	}
	outDataStream << companies.getOrphans(maxCompanies - 1) << "\n";
	outDataStream << "Started, ";
	for (int j = 0; j < maxCompanies - 1; j++) // SAve company started
	{
		outDataStream << companies.getStarted(j) << ",";
	}
	outDataStream << companies.getStarted(maxCompanies - 1) << "\n";
	outDataStream << "Reship, ";
	for (int j = 0; j < maxCompanies - 1; j++)//Save company recievership
	{
		outDataStream << companies.getRecievership(j) << ",";
	}
	outDataStream << companies.getRecievership(maxCompanies - 1) << "\n";
	outDataStream << "TurnOrder, ";
	for (int j = 0; j < maxCompanies - 1; j++) // Save company turnorder
	{
		outDataStream << companies.getTurn(j) << ",";
	}
	outDataStream << companies.getTurn(maxCompanies - 1) << "\n";
	for (int m = 0; m < maxCities; m++)
	{
		outDataStream << cities.name[m] << ",";
		for (int j = 0; j < maxCompanies-1; j++)
		{
			outDataStream << companies.getCity(j,m) << ",";
		}
		outDataStream << companies.getCity(maxCompanies - 1,m) << "\n";
	}
	outDataStream << "Trains, ";
	for (int k = 0; k < 29; k++) // Save train owners
	{
		outDataStream << k+1 << ",";
	}
	outDataStream << 30 << "\n";
	outDataStream << "Owners, ";
	for (int k = 0; k < 29; k++) // Save train owners
	{
		outDataStream << trains.getTrainOwner(k + 1) << ",";
	}
	outDataStream << trains.getTrainOwner(30) << "\n";
	outDataStream.close();
	return(techLevel);
}


	void showPlayerInfo()
	{



	}

/*
void setRandomTurnOrder()
	{
		srand(unsigned int (time(0)));
		for (int i = 0; i < numberPlayers; i++)
		{
				players[i].cash = rand() % 10000;
		}
		//setPlayerTurnorder(playerNetworth, playerTurnorder);
		for (int i = 0; i < numberPlayers; i++)
		{
			players[i].cash = 0;
		}
	}*/