#pragma once
class Trains
{
public:	
	Trains( int ownerVal[30]);

	void output(int indexVal);
	//Precondition: index value of the train - number bewteen 1 and 30
	//Postcodition: Prints information about train.
	int getCost(int indexVal);
	int priceTrainForSale();
	//Precondition: None
	//Postcondition: Returns the cost of the train that is currently for sale
	int buyTrainForSale(int companyVal);
	//Precondition: index of company purchasing the train - postive integer
	//Postconditio: Returns the cost of the train that is currently for sale. Also assign
	// train to company and makes next train current train for sale.
	int scrapTrainOfCompany(int indexVal, int companyVal);
	//Precondition: Index of train that company owns and wants to scrap - number between 1 and 30.
	//Postcondition: Returns the scrap value of the train if no error. Returns
	//0 if there is and error. Also removes train from company's ownership.
	int getCompanyTrains(int companyVal);
	// Precondition: index of company purchasing the train - postive integer
	// Postcondition: Prints list of trains a company owns
	int getServiceCapacity(int companyVal);
	// Precondition: index of company purchasing the train - postive integer
	// Postcondition:  Returns the number of cities that the company can service.
	int getTechLevel(int currentTechLevel);
	//Precondition: None
	//Postcondition: Returns the current tech level based on trains purchased




private:	
	const int cost[30] = { 100, 95,90,85,80,140,130,120,110,100,200,185,170,155,135,280,260,240,220,200,380,355,330,305,280,500,470,440,410,380 };
	const int level[30] = { 1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6 };
	const int scrap[30] = { 20,20,20,20,40,40,40,40,40,60,60,60,60,60,80,80,80,80,80,100,100,100,100,100,120,120,120,120,120 };
	const int index[30] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };
	int owner[30];

};

