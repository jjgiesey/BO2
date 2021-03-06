
#include "stdafx.h"

#include "Trains.h"
#include "TechLevels.h"
#include "Companies.h"
#include "Players.h"
#include "Cities.h"


using namespace std;

// Game functions

int setGame(int numberPlayers);
//Precondition: number of players has been set and passed in numberPlayers
//Postcondition: game conditions set and current tech level is passed.
//Game will resume at beginning of market round

int startGame();


void setupPlayers();
//Precondition: None
//Postcondition: After running all the players will be loaded into the class players
// with initial values and turn orders set

int endGame();

// Market

int marketRound();
//Precondition: Turn holds the turn order index to start with.
//Postcondition:

int marketTurn(int player);
//Precondition: Given player index in player
//Postcondition: Will  run player's turn until done and then
//   return a 0. If player passes returns a 1.

bool attemptBuy(int player);
//Precondition: player < numberPlayers
//Postcondition: returns 1 if successfull and handles all the buying transactions

bool attemptSell(int player);
// This function will return a 1 when the player has sucessfully sold a stock for their turn.

bool attemptOrphan(int player);
// This function will return a 1 when a player has successfully had a company buy back orphaned stock.

int reduceForOrphans();
//Preconditions:To be run at end of market round
//Postconditions: Valuation of companies that have orphan shares
//				is reduced by one level.

//Building
int businessRound();
//Precondition: To be run after market round in loop of two attempts. Turn holds the turn order index to start with.
//Postcondition: All companies get a turn.

int businessTurn(int company);
//Precondition: Comapny whose turn it is sent
//Postcondition: Business functions run.

int attemptScrapTrain(int company);
// Precondition: Company index - postitive intger
// Postcondition: Train is scrapped and money added to company or error given

int attemptBuyTrain(int company);
// Precondition: Company index - postitive intger
//Postcondition: Ifunds sufficient, company is designated owner of train and cost stutracted from cash.

void attemptBuildTrack(int company);
// Precondition: Company index - postitive intger

void BuildTrack(int company, int amount);

void setCompanyDividens(int currentCompany, char companyDividenPlan);
//Preconditions: For the current company given in currentCompany to pay dividens to shareholders and itself. Uses companyNetprofit, companySharesowned, and playerShares.
//Postcondition: Profits distributed to companyCash and playerCash

void setCompanyValuation(int company, int netProfitChange, char companyDividenPlan);
//Preconditions: For the company given by CurrentCompany that had a net profit change given by netProfitChange (decrease = -1, increase = 1
// and same = 0) and the decision to withhold (w) or distribute (d) dividens given in companyDividenPlan. Function also uses companyValuations
//Postcondition: Valuation of company is decrease if it had a decrease in net profit. It increase if net profit increased and dividens were paied. 
//Otherwise valuation stays the same.

// Utilities

void setPlayerNetworth();
//Precondition: players object has current cash and shares. Companies has current valuations
//Postcondition: players networth is calculated.

int setCompanyPresident(int company);
// Preconditions: company is a vaild company. The shares ownd by players is passed through playerShares and the current president it passed
// through companyPresident
// Postcondidtion: The number of shares owned by each player is compared and if a new player has more shares their number is returned through setCompanyPresident.
// If not the old president is passed.

char readValue(ifstream& inputStream, char cArray[]);
//Precondtions: Open stream in in inputStrean and character array is returned in cArray
//Postcondition: Will return last character read.

char findEOL(ifstream& inputStream);
//Precondition: Stream to be read for end of line is in inputStream
//				It is expected that all relevant values have been read
//Postcondition: Stream cleared. Last character returned. Should be /n if successful

int getCashInfo();


// Data processing 

int fetchFileData(char pfileName[]);

int getManualData();

int pushFileData(char pfileName[]);

const int totalCash = 1500;
int trainOwner[30] = { -1,-1, -1, -1,-1, -1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1, -1, -1,-1 };

Players players(totalCash);
Trains trains(0);
TechLevels techLevels;
Cities cities;
Companies companies(0);
int numberPlayers;

char testArray[30];
char wfileName[30];
int turn = 0;
int gameRound = 0;
int techLevel = 1;

int main()
{
	// BO Banker with Object
	char confirm;

	cout << "BO Banker Program \n \n";
	startGame();
	do
	{
		if (gameRound == 0)
		{
			// Market Phase
			int numberPasses = 0;
			marketRound();
			gameRound =1;
			turn = 0;
		}
		if (gameRound == 1)
		{ 
			// Build Phase 1
			cout << "++Begin building round 1 "<< endl;
			businessRound();
			gameRound = 2;
			turn = 0;
		}
		if (gameRound == 2)
		{
			// Build Phase 2
			cout << "++Begin building round 2 " << endl;
			businessRound();
			gameRound =0;
			turn = 0;
			cout << "++End of Business Rounds " << endl << endl;
		}
	} while (techLevel < 6);
	endGame();
	cout << "Enter a key to end:";
	cin >> confirm;
	return 0;
}
int startGame()
{
	char option;

	// Set up options

	cout << "Name of game data file:";
	cin >> wfileName;
	strcat_s(wfileName, 30, ".csv");
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
		getManualData();
		break;
	case 'f':
		fetchFileData(wfileName);
		break;
	default:
		setupPlayers();
	}
	//Sort players by cash
	getCashInfo();
	pushFileData(wfileName);
	return(0);
}
void setupPlayers( )
{
	// Set up players names
	char name[20];
	int tempOrder[maxPlayers] = { 0,1,2,3,4,5 };
	long int currentTime = static_cast<long int>(time(0)); //Generate random seed
	srand(currentTime);

//*****************************************
	cout << "Number of players: ";
	cin >> numberPlayers;
	cout << "++There are " << numberPlayers << " of " << maxPlayers << " players. \n";
	cout << "Enter player names in any order. \n";
	for (int i = 0; i < numberPlayers; i++)
	{
		cout << "Player " << i + 1 << ": ";
		cin >> name;
		cout << "\n";
		strcpy_s(players.name[i], name);
		players.setCash(i,rand() % 10000); // assign random number
	}
	players.getTurnorders(tempOrder, numberPlayers);

	for (int i = 0; i < numberPlayers; i++)
	{
		int player = tempOrder[i];
		players.setCash(player,totalCash / numberPlayers);
		for (int j = 0; j < maxCompanies; j++)
		{
			players.setShares(player,j,0);
			players.clearSold(player,j);
		}
	}
}
int endGame()
{
	cout << "End of the game.";
	int winner = 0;
	for (int i = 0; i < numberPlayers; i++)
	{
		if (players.getNetworth(i) > players.getNetworth(winner))
		{
			winner = i;
		}
	}
	cout << " The winner is " << players.name[winner] << "! \n";
	return(0);
}

int marketRound()
{
	int numberPasses = 0;
	int player;
	int orderPlayers[maxPlayers];
	int istart = turn;
	cout << "++Begin market round. \n";
	players.getTurnorders(orderPlayers, numberPlayers);
	while (numberPasses < numberPlayers)
	{
		numberPasses = 0;
		for (int i = 0; i < numberPlayers; i++)
		{
			istart = 0;
			player = orderPlayers[i];
			turn = i;
			numberPasses += marketTurn(player);
		}
	}

	// Clear sold array
	for (int i = 0; i < numberPlayers; i++)
	{
		for (int j = 0; j < maxCompanies; j++)
		{
			players.clearSold(i, j);
		}
	}
	reduceForOrphans();
	cout << "++End of market round.\n";
	numberPasses = 0;
	return(0);
}
int marketTurn(int player)
{
	int pass = 1;
	int playerSuccess = 0;
	char option;
	do
	{
		cout << endl << players.name[player] << " has $" << players.getCash(player) << "cash. What would you like to do? \n";
		cout << "   's' = sell shares\n";
		cout << "   'b' = buy shares\n";
		cout << "   'o' = orphan share buyback \n";
		cout << "   'd' = done \n";
		cout << "Option: ";
		cin >> option;
		switch (option)
		{
		case 'd':
			playerSuccess = 1;
			getCashInfo();
			break;
		case 'o':
			if (attemptOrphan(player))
			{
				playerSuccess = 1;
				pass = 0;
				getCashInfo();
			}
			else
				playerSuccess = 0;
			break;
		case 's':
			if (attemptSell(player))
			{
				pass = 0;
				getCashInfo();
			}
			playerSuccess = 0;
			break;
		case 'b':
			if (attemptBuy(player))
			{
				playerSuccess = 1;
				pass = 0;
				getCashInfo();
			}
			else
				playerSuccess = 0;
			break;
		default:
		cout << "****Invalid option. Try agian.**** \n\n";
		}
	} while (playerSuccess != 1);
	pushFileData(wfileName);
	return(pass);
}
bool attemptBuy(int player)
{
	// Player requests to buy

	int numberShares=0, numberOrphans=0;
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
			if (players.getSold(player,j) != 1)
			{
				if (companies.getStarted(j) == 0)
				{
					cout << "    " << j << ": " << companies.name[j] << endl;
				}
				else
				{
					cout << "    " << j << ": " << companies.name[j] << endl;
				}
			}
		}
	}
	cout << "Selection:";
	cin >> company;
	// Three options: not avialable, buy regular shares, buy orphaned shares.

	if ((company < 0) || (company > maxCompanies + maxCompanies - 1)) // Company not avialable
	{
		cout << "****Company  nubmer" << company << " is not valid. Please try again.**** \n";
		cin.clear();
		return 0;
	}
	else if (players.getSold(player,company) != 0)
	{
		cout << "****Can not buy shares of company sold during this round. Please try again.**** \n";
		cin.clear();
		return 0;
	}
	else if (company < maxCompanies) // Regular Shares
	{
		if (!companies.getAvailable(company, techLevel))
		{
			cout << "****Company " << companies.name[company] << " is not available.**** \n";
			return 0;
		}
		// Check to see if company has not been started and needs intial value set
		if (!companies.getStarted(company))
		{
			cout << "Select inital company valuation for " << companies.name[company] << ". \n";
			cout << "    1: $" << valuations[techLevels.lowVal[techLevel - 1]] << endl;
			cout << "    2: $" << valuations[techLevels.medVal[techLevel - 1]] << endl;
			cout << "    3: $" << valuations[techLevels.highVal[techLevel - 1]] << endl;
			cout << "Selection: ";
			cin >> option;
			if (option == 1)
				requestValuation = techLevels.lowVal[techLevel - 1];
			else if (option == 2)
				requestValuation = techLevels.medVal[techLevel - 1];
			else if (option == 3)
				requestValuation = techLevels.highVal[techLevel - 1];
			else
			{
				cout << "****Request not valid. Please try again.****\n";
				return 0;
			}
			cout << "++" << companies.name[company] << " has requested an intial valuations of $" << valuations[requestValuation] << " per share \n";
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
			cout << "****Request not valid. Please try again.**** \n";
			cin.clear();
			return 0;
		}
		if (numberShares > companies.getShares(company))
		{
			cout << "****Only " << companies.getShares(company) << " shares available.****\n";
			cin.clear();
			return 0;
		}
		if (companies.getOrphans(company) != 0) // Offer Orphans if any
		{
			cout << "How many ORPHAN shares of " << companies.name[company] << " do you want to buy: ";
			cin >> numberOrphans;
			// check validity of request
			if (numberOrphans < 0)
			{
				cout << "****Request not valid. Please try again.****\n";
				cin.clear();
				return false;
			}
			if (numberOrphans > companies.getOrphans(company))
			{
				cout << "****Only " << companies.getOrphans(company) << " orphan shares available.****\n";
				cin.clear();
				return false;
			}
		}
		if ((numberShares + numberOrphans)*valuations[requestValuation] > players.getCash(player))
		{
			cout << "****Need " << (numberShares + numberOrphans) * valuations[requestValuation] << " for purchase.****\n";
			return false;
		}
		else
		{ 
		// Proceed with sale
			test = companies.setStarted(company);
			test = companies.setValuation(company, requestValuation);
			test = companies.changeShares(company, -numberShares);
			test = companies.changeCash(company, (numberShares * valuations[requestValuation]));
			test = companies.changeOrphans(company, -numberOrphans);
			players.changeShares(player, company, (numberShares + numberOrphans));
			players.changeCash(player, -((numberShares + numberOrphans) * valuations[requestValuation]));
			cout << "++" << players.name[player] << " now has " << players.getShares(player, company) << " of " << companies.name[company] << ".\n";
			cout << "++" << players.name[player] << " now has $" << players.getCash(player) << ".\n";
			cout << "++" << companies.name[company] << " now has " << companies.getShares(company) << " regualr shares and " << companies.getOrphans(company) << " orphan shares. \n";
			cout << "++" << companies.name[company] << " now has $" << companies.getCash(company) << endl;
			test = setCompanyPresident(company);
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

	cout << "Select company to sell from.\n";
	for (int j = 0; j < maxCompanies; j++)
	{
		if ((players.getShares(player,j) != 0))
		{
			cout << "    " << j << " " << companies.name[j] << endl;
		}
	}
	cout << "Selection: ";
	cin >> company;
	if ((company < 0) || (company > maxCompanies - 1))
	{
		cout << "****Company  nubmer" << company << " is not valid. Please try again.**** \n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	if (players.getShares(player, company) == 0)
	{
		cout << "****No shares of " << company << " owned. Please try again.**** \n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}

	// Removed to allow multiple sales of same stock during turn and round
	/*if (players.getSold(player,company))
	{
		cout << "Company  nubmer" << company << " has been sold by you this turn. You must wait until a later turn to sell more. \n"; 
		cin.clear();
		cin.ignore(10, '\n');
		return false; 
	} */
	cout << "How many shares of " << companies.name[company] << " do you want to sell?: ";
	cin >> numberShares;
	// check validity of request
	if (numberShares< 0)
	{
		cout << "****Request not valid. Please try again.**** \n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	if (numberShares > players.getShares(player,company))
	{
		cout << "****Only " << players.getShares(player,company) << " shares owned. Reduce request.****\n";
		cin.clear();
		cin.ignore(10, '\n');
		return false;
	}
	else if (players.totalSharesOwned(company) <= numberShares)
	{
		cout << "****Can not sell all shares of company " << companies.name[company] << ". Reduce request.**** \n";
		return false;
	}
	else  // Proceed with sale
	{
        players.changeShares(player,company, -numberShares);
		cout << "++" << players.name[player] << " now has " << players.getShares(player,company)<< " of " << companies.name[company] << ".\n";
        players.changeCash(player,(numberShares * valuations[companies.getValuation(company)]));
		cout << "++" << players.name[player] << " now has $" << players.getCash(player) << ".\n";
        test = companies.changeOrphans(company,numberShares);
		cout << "++" << companies.name[company] << " now has " << companies.getShares(company) << " regualr shares and " << companies.getOrphans(company) << " orphan shares. \n";
		cout << "++" << companies.name[company] << " now has $" << companies.getCash(company) << endl;
 		// Reduce valuation if first sale of round by player. If second or greater sale there is no additional reduction.
		if (!players.getSold(player,company))
		{
			test = companies.decreaseValuation(company);
			cout << "++" << companies.name[company] << " has been sold this turn and its valuation has been reduced to $" << valuations[companies.getValuation(company)] << " per share. \n";
		}
		test = setCompanyPresident(company);
		players.setSold(player,company);
		return true;
	}
	return false;
}
bool attemptOrphan(int player)
{
	int numberShares;
	int numberOrphanCompaniesControlled = 0;
	int company;
	int test;

	cout << players.name[player] << " wants a company to buy orphaned stock \n";
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
		cout << players.name[player] << " owns no companies with orphan stocks \n";
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
		cout << "Only " << companies.name[company] << " president, " << players.name[companies.getPresident(company)] << " can buy orphan shares on behalf of company \n";
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
int reduceForOrphans()
	{
		for (int j = 0; j < maxCompanies; j++)
		{
			if (companies.getOrphans(j) != 0)
			{
				companies.decreaseValuation(j);
				cout << "++" <<companies.name[j] << " valuation decreases to $" << valuations[companies.getValuation(j)] << " per share due to orphaned share. \n";
			}

		}
		return (0);
	}

int businessRound()
{
	int company;
	int orderCompany[maxCompanies];
	int jstart = turn;

	companies.getTurnorders(orderCompany);
	for (int j = 0; j < maxCompanies; j++)
	{
		jstart = 0;
		company = orderCompany[j];
		businessTurn(company);
	}
	return(0);
}
int businessTurn(int company)
{
	int profit,track, netprofitChange;
	char confirm;
	char dividend;
	int scrapT[maxTrains], buyT[maxTrains];
	int netCash;

	if (companies.getStarted(company))
	{
		cout << companies.name[company] << " has $ " << companies.getCash(company) << endl;

		do
		{
			netCash = companies.getCash(company);
			for (int k = 0; k < maxTrains; k++)  //Scrap train request
			{
				scrapT[k] = false;
				if (companies.getTrains(company, k) == 1)
				{
					cout << "Would you like to scrap a train " << k + 1 << " for $" << trains.scrap[k] << "? (y/n): ";
					cin >> confirm;
					cin.clear();
					cin.ignore(10, '\n');
					if ((confirm == 'y') || (confirm == 'Y'))
					{
						scrapT[k] = true;
						netCash += trains.scrap[k];
						cout << "-Net cash would be $" << netCash << ".\n";
					}
				}
			}
			int kSale = companies.getTrainForSale();// Buy train request
			for (int k=0; k<kSale;k++)
				buyT[k] = false;
			do
			{
				if (kSale >= maxTrains)
				{
					cout << "There are no more trains for sale. \n";
					confirm = 'n';
				}
				else
				{
					cout << "Would you like to buy the next train " << kSale + 1 << " for $" << trains.cost[kSale] << "? (y/n): ";
					cin >> confirm;
					cin.clear();
					cin.ignore(10, '\n');
					if ((confirm == 'y') || (confirm == 'Y'))
					{
						buyT[kSale] = true;
						netCash -= trains.cost[kSale];
						cout << "-Net cash would be $" << netCash << ".\n";
						kSale++;
					}
				}
			}
			while ((confirm == 'y') || (confirm == 'Y'));
			for (int k = kSale; k < maxTrains; k++)
			{
				buyT[k] = false;
			}
			do // Buy track request
			{
				cout << "How much track do you want to purchase?: ";
				cin >> track;
				cin.clear();
				cin.ignore(10, '\n');
			} while ((track < 0) || (track > 1000));
			netCash -= track;
			cout << "-Net cash would be $" << netCash << ".\n";
			do // Set profit request
			{
				cout << "Enter new net profit $";
				cin >> profit;
				cin.clear();
				cin.ignore(10, '\n');
			} while ((profit < 0) || (profit > 1000));
			do // Withhold/Distribute request
			{
				cout << "Do you want to distribute=d or withold=w dividens? ";
				cin >> dividend;
				cin.clear();
				cin.ignore(10, '\n'); 
			}
			while ((dividend !='d') && (dividend != 'w'));
			if (netCash < 0)
			{
				cout << "****Company does not have enough cash to implement build. Please try again.****\n";
				confirm = 'n';
			}
			else
			{
				for (int k = 0; k < maxTrains; k++)  //List scrap train requests
				{
					if (scrapT[k])
					{
						cout << "-Scrap train " << k + 1 << " for $" << trains.cost[k] << ". \n";
					}
				}
				for (int k = 0; k < maxTrains; k++)  //List buy train requests
				{
					if (buyT[k])
					{
						cout << "-Buy train " << k + 1 << " for $" << trains.cost[k] << ". \n";
					}
				}
				cout << "-Buy $" << track << " of track. \n"; //List track request
				cout << "-Set net profit to  $" << profit << ". \n"; //List profit request
				if (dividend == 'd') //List dividen request
				{
					cout << "-Distribute dividens. \n";
				}
				else
				{
					cout << "-Withhold dividens. \n";
				}
				cout << "Is this correct? (y/n): ";
				cin >> confirm;
				cin.clear();
				cin.ignore(10, '\n');
			}
		} while ((confirm != 'y') && (confirm != 'Y')); 
		for (int k = 0; k < maxTrains; k++)  //Scrap trains
		{
			if (scrapT[k])
			{
				companies.changeCash(company, companies.scrapTrainOfCompany(k, company));
			}
		}
		for (int k = 0; k < maxTrains; k++)  //Buy trains
		{
			if (buyT[k])
			{
				companies.changeCash(company,-companies.buyTrainForSale(company,techLevel));
			}
		}
		BuildTrack(company,track); //Build track
		if (profit == 0)
		{
			netprofitChange = -2;
		}
		else if (profit > companies.getNetprofit(company))
		{
			netprofitChange = 1;
		}
		else if (profit < companies.getNetprofit(company))
		{
			netprofitChange = -1;
		}
		else
		{
			netprofitChange = 0;
		}
		companies.setNetprofit(company, profit);
		cout << "++" << companies.name[company] << " netprofit is now " << profit << ", \n";
		setCompanyDividens(company,dividend);
		setCompanyValuation(company, netprofitChange, dividend);
		cout << "++" << companies.name[company] << " has $ " << companies.getCash(company) << endl;
		getCashInfo();
	}
	pushFileData(wfileName);
	return(0);
}

int attemptScrapTrain(int company)
	{
		int trainNumber;

		if (companies.getCompanyTrains(company) <= 0)
		{
			cout << " Company has no trains to scrap \n";
			return(0);
		}
		else
		{
			cout << "Select train to scrap: ";
			cin >> trainNumber;
			if (companies.getTrains(company, trainNumber - 1) == 1)
			{
				companies.changeCash(company, +companies.scrapTrainOfCompany(trainNumber - 1, company));
				cout << companies.name[company] << " now has $" << companies.getCash(company) << endl;
			return(trainNumber);	
			}
			else
			{
				cout << " Company does not own train: " << trainNumber << endl;
				return(0);

			}
		}

	}
int attemptBuyTrain(int company)
{
	int train = companies.getTrainForSale();
	if (train >= 30)
	{
		cout << "There are no more trains for sale. \n";
		return (30);
	}
	if (companies.getCash(company) < trains.cost[train])
	{
		cout << "Company does not have enough cash to buy train. \n";
		return (-1);
	}
	companies.changeCash(company, -companies.buyTrainForSale(company,techLevel));
	techLevel = companies.getTechLevel(techLevel);
	return(train);
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

void BuildTrack(int company, int amount)
{
	companies.changeCash(company, -amount);
	cout << companies.name[company] << " now has $" << companies.getCash(company) << endl;
	return;
}

void setCompanyValuation(int company, int netProfitChange, char companyDividenPlan)
{
	if (netProfitChange < 0)
	{
		if (companies.getNetprofit(company) != 0)
		{
			companies.decreaseValuation(company);
			cout << "++" <<companies.name[company] << " valuation decreases to $" << valuations[companies.getValuation(company)] << " per share. \n";
		}
		else
		{
			// Unprofitable Company
			int badPresident = companies.getPresident(company);
			companies.decreaseValuation(company);
			companies.decreaseValuation(company);
			cout << "++" << companies.name[company] << " valuation decreases to $" << valuations[companies.getValuation(company)] << " per share. \n";
			companies.changeShares(company,1);
			players.changeShares(setCompanyPresident(company),company, -1);
			cout << "++" << players.name[badPresident] << " shares in " << companies.name[company] << " has been reduced to " << players.getShares(badPresident,company) << " shares. \n";
			if (players.getShares(setCompanyPresident(company),company) == 0)
			{
				// Company goes into recievership
				cout << "++" << companies.name[company] << " goes into recievership. \n";
				companies.setRecievership(company); // Place into revievership
				companies.clearStarted(company); // Clear started flag
				companies.setValuation(company, 4); //Set valuation to $50
				companies.scrapCompanyTrains(company); //Scrap all trains
				companies.setCash(company, 0); //Clear out treasurey
				companies.changeOrphans(company, -companies.getOrphans(company)); //Clear out orphans
				companies.changeShares(company, 10 - companies.getShares(company)); // Put all shares regular
				cout << "++" << companies.name[company] << " now has $" << companies.getCash(company) << " and " << companies.getShares(company) << " regular shares and " << companies.getOrphans(company) << " orphaned shares \n";
			}
		}
}
    else if ((netProfitChange > 0) && (companyDividenPlan == 'd'))
    {
        companies.increaseValuation(company);
		cout << "++" << companies.name[company] << " valuation increases to $" << valuations[companies.getValuation(company)] << " per share. \n";

    }
    else
    {
        cout << "++" << companies.name[company] << " valuation remains the same at $" << valuations[companies.getValuation(company)] << " per share. \n";
    }
    return;
}
void setCompanyDividens(int company, char option)
	{
		if (option == 'd')
		{
			int cDividend = (companies.getShares(company) * companies.getNetprofit(company)) / 10;
			companies.changeCash(company, cDividend);
			cout << "++" << companies.name[company] << " recieved $" << cDividend << " from " << companies.getShares(company) << " shares. \n";

			for (int i = 0; i < numberPlayers; i++)
			{
				if (players.getShares(i,company) != 0)
				{
					int pDividend = players.getShares(i,company)*companies.getNetprofit(company) / 10;
					players.changeCash(i,pDividend);
					cout << "++" << players.name[i] << " recieved $" << pDividend << " from " << players.getShares(i,company) << " shares of " << companies.name[company] << " and now has $" << players.getCash(i) << endl;
				}
			}
		}
		else
		{
			companies.changeCash(company, companies.getNetprofit(company));
			cout << "++" << companies.name[company] << " recieved net profit of  $" << companies.getNetprofit(company) << ". \n";

		}
		return;
	}

int setCompanyPresident(int company)
{
	int oldpresident = companies.getPresident(company);
	int president = oldpresident;
	for (int i = 0; i < numberPlayers; i++)
	{
		if (players.getShares(i,company) > players.getShares(president,company))
		{
			companies.setPresident(company,i);
			president = i;
		}
	}
	if (president != oldpresident)
	{
		cout << "++" <<  players.name[president] << " is the new president for " << companies.name[company] << endl;
	}
	return(president);
}


void setPlayerNetworth()
{
	for (int i = 0; i < numberPlayers; i++)
	{
		int sum = players.getCash(i);
		for (int j = 0; j<maxCompanies; j++)
		{
			sum += players.getShares(i, j) * valuations[companies.getValuation(j)];
		}
		players.setNetworth(i, sum);
	}
	return;
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

int getCashInfo()
{
	cout << "\n++++++++++++++++++++++++++++++++++++++++ \n";		setPlayerNetworth();
	for (int i = 0; i < numberPlayers; i++)
		players.getInfo(i);
	for (int j = 0; j < maxCompanies; j++)
	{
		if (companies.getStarted(j) == 1)
			cout << j << ": " << companies.name[j] << " has $" << companies.getCash(j) << endl;
	}
	cout << "++++++++++++++++++++++++++++++++++++++++ \n\n";
	return(0);
}

int fetchFileData(char pfileName[])
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
	while (strcmp(testArray,"Done#")!=0)	//Read player names
	{
		strcpy_s(players.name[rnumberPlayers], testArray);
		rnumberPlayers++;
		getChar = readValue(inDataStream, testArray);
	}
	numberPlayers = rnumberPlayers;
	findEOL(inDataStream);
	getChar = readValue(inDataStream, testArray);
	for (int i = 0; i < numberPlayers; i++) // Read player cash
	{
		getChar = readValue(inDataStream, testArray);
		players.setCash(i,atoi(testArray));
	}
	findEOL(inDataStream);
	getChar = readValue(inDataStream, testArray);
	for (int j = 0; j < maxCompanies; j++) // Read player shares owned
	{
		for (int i = 0; i < numberPlayers; i++)
		{
			getChar = readValue(inDataStream, testArray);
			players.setShares(i,j,atoi(testArray));
		}
		findEOL(inDataStream);
		getChar = readValue(inDataStream, testArray);
	}
	for (int j = 0; j < maxCompanies; j++) // Read player sold company
	{
		for (int i = 0; i < numberPlayers; i++)
		{
			getChar = readValue(inDataStream, testArray);
			if (atoi(testArray) == 1)
				players.setSold(i,j);
			else
				players.clearSold(i, j);
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
		companies.setValuation(j, atoi(testArray));
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
	for (int j = 0; j < maxCompanies; j++) //Read company started
	{
		getChar = readValue(inDataStream, testArray);
		if (atoi(testArray) == 1)
			companies.setStarted(j);
		else
			companies.clearStarted(j);
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
		companies.setOrder(j, atoi(testArray));
	}
	findEOL(inDataStream);
	for (int m = 0; m < maxCities; m++) // Read cities
	{
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++)
		{
			getChar = readValue(inDataStream, testArray);
			if (atoi(testArray) == 1)
				companies.setCity(j, m);
			else
				companies.clearCity(j, m);
		}
		findEOL(inDataStream);
	}
	for (int k = 0; k < maxTrains; k++) // Read trains
	{
		getChar = readValue(inDataStream, testArray);
		for (int j = 0; j < maxCompanies; j++)
		{
			getChar = readValue(inDataStream, testArray);
			companies.setTrains(j, k, atoi(testArray));
		}
		findEOL(inDataStream);
	}
	getChar = readValue(inDataStream, testArray);
	getChar = readValue(inDataStream, testArray);
	gameRound = atoi(testArray);
	findEOL(inDataStream);
	getChar = readValue(inDataStream, testArray);
	getChar = readValue(inDataStream, testArray);
	turn = atoi(testArray);
	techLevel = companies.getTechLevel(1);
	return(0);
}
int getManualData()
{
	do
	{
		cout << "Enter number of players between 2 and 6: ";
		cin >> numberPlayers;
		cin.clear();
		cin.ignore(10, '\n');
	} while ((numberPlayers < 2) || (numberPlayers > 6));
	cout << "There are " << numberPlayers << " of " << maxPlayers << " players. \n";
	setGame(numberPlayers);
	setPlayerNetworth();
	for (int i = 0; i < numberPlayers; i++)
		players.getInfo(i);
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
int setGame(int numberPlayers)
{
	// Restet TechLevel

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
			cin.clear();
			cin.ignore(10, '\n');
			if ((confirm == 'y') || (confirm == 'Y'))
			{
				companies.setStarted(j);
				cout << "\nCompany in recievership (y/n):";
				cin >> confirm;
				cin.clear();
				cin.ignore(10, '\n');
				if ((confirm == 'y') || (confirm == 'Y'))
				{
					companies.setRecievership(j);
					companies.clearStarted(j); // Clear started flag
					companies.setValuation(j, 4); //Set valuation to $50
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
							companies.setValuation(j, n);
					}
					cout << "\nShares: ";
					cin >> value;
					companies.changeShares(j, value - 10);
					cout << "\nOrphans: ";
					cin >> value;
					companies.changeOrphans(j, value);
					cout << "\nTurn Order (0 is first): ";
					cin >> value;
					companies.setOrder(j, value);
					cout << endl;
					do
					{
						cout << "\nEnter train number of train(s) owned (0 to quit):";
						cin >> value;
						companies.setTrains(j,value, 1);
					} while (value > 0);

				}
			}
		}
	}
	// Reset Scrapped Trains
	do
	{
		cout << "\nEnter train number of train(s) scrapped (0 to quit):";
		cin >> value;
		companies.setTrains(0,value, -1);
	} while (value > 0);

	// Reset Players

	for (int i = 0; i < numberPlayers; i++)
	{
		cout << "\n\nFor player: " << players.name[i] << endl;
		cout << "\nCash: ";
		cin >> value;
		players.setCash(i, value);
		for (int j = 0; j < maxCompanies; j++)
		{
			if (companies.getAvailable(j, techLevel))
			{
				if (companies.getStarted(j) == 1)
				{
					cout << "\nEnter number of shares of " << companies.name[j] << " owned: ";
					cin >> value;
					players.setShares(i, j, value);
					cout << endl;
				}
			}
		}


	}
	return(0);

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

	outDataStream << "Name,";
	for (int i = 0; i < numberPlayers; i++) // Save player name
	{
		outDataStream << players.name[i] << ",";
	}
	outDataStream <<  "Done#," <<"\n";
	outDataStream << "Cash,";
	for (int i = 0; i < numberPlayers; i++) // Save player cash
	{
		outDataStream << players.getCash(i) << ",";
	}
	outDataStream << "\n";
	for (int j = 0; j < maxCompanies; j++) // Save player shares owned
	{
		outDataStream << companies.name[j] << ",";
		for (int i = 0; i < numberPlayers; i++)
		{
			outDataStream << players.getShares(i,j) << ",";
		}
		outDataStream << "\n";
	}
	for (int j = 0; j < maxCompanies; j++) // Save player sold company
	{
		outDataStream << companies.name[j] << ",";
		for (int i = 0; i < numberPlayers; i++)
		{
			outDataStream << players.getSold(i, j) << ",";
		}
		outDataStream << "\n";
	}	outDataStream << "Names,";
	for (int j = 0; j < maxCompanies; j++) // Save company names
	{
		outDataStream << companies.name[j] << ",";
	}
	outDataStream << "\n";
	outDataStream << "Cash, ";
	for (int j = 0; j < maxCompanies; j++) // Save company cash
	{
		outDataStream << companies.getCash(j) << ",";
	}
	outDataStream << "\n";
	outDataStream << "NetProfit,";
	for (int j = 0; j < maxCompanies; j++) // Save company netprofit
	{
		outDataStream << companies.getNetprofit(j) << ",";
	}
	outDataStream << "\n";
	outDataStream << "Valuation, ";
	for (int j = 0; j < maxCompanies; j++) //Save valuation
	{
		outDataStream << companies.getValuation(j) << ",";
	}
	outDataStream << "\n";

	outDataStream << "President, ";
	for (int j = 0; j < maxCompanies; j++) //Save president
	{
		outDataStream << companies.getPresident(j) << ",";
	}
	outDataStream << "\n";
	outDataStream << "Shares, ";
	for (int j = 0; j < maxCompanies; j++) // Save Company shares
	{
		outDataStream << companies.getShares(j) << ",";
	}
	outDataStream << "\n";
	outDataStream << "Orphans, ";
	for (int j = 0; j < maxCompanies; j++) // Sace Company orphans
	{
		outDataStream << companies.getOrphans(j) << ",";
	}
	outDataStream << "\n";
	outDataStream << "Started, ";
	for (int j = 0; j < maxCompanies; j++) // SAve company started
	{
		outDataStream << companies.getStarted(j) << ",";
	}
	outDataStream << "\n";
	outDataStream << "Reship, ";
	for (int j = 0; j < maxCompanies; j++)//Save company recievership
	{
		outDataStream << companies.getRecievership(j) << ",";
	}
	outDataStream << "\n";
	outDataStream << "TurnOrder, ";
	for (int j = 0; j < maxCompanies; j++) // Save company turnorder
	{
		outDataStream << companies.getOrder(j) << ",";
	}
	outDataStream << "\n";
	for (int m = 0; m < maxCities; m++) // Save cities
	{
		outDataStream << cities.name[m] << ",";
		for (int j = 0; j < maxCompanies; j++)
		{
			outDataStream << companies.getCity(j, m) << ",";
		}
		outDataStream << "\n";
	}
	for (int k = 0; k < maxTrains; k++) // Save trains
	{
		outDataStream << k+1 << ",";
		for (int j = 0; j < maxCompanies; j++)
		{
			outDataStream << companies.getTrains(j, k) << ",";
		}
		outDataStream << "\n";
	}
	outDataStream << ("Round,");
	outDataStream << (gameRound) << ", \n";
	outDataStream << ("Turn,");
	outDataStream << (turn) << ", \n";
	for (int k = 0; k < maxTrains+1; k++) // make sure rows are long enough
	{
		outDataStream << k << ",";
	}
	outDataStream << "\n";
	outDataStream.close();
	companies.getTechLevel(techLevel);
	return(0);
}



