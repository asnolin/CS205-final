#include "Store.hpp"
#include <iostream>

//====================================================================================================
//Mean Arrival Interval for Customers
int Store::arrivalSeed = 1;

unsigned long int Store::Time = 0;

Store::Store()
{
	Time = 0;
	Strat = RANDOM;
	NumCheckouts = 0;
}

Store::~Store()
{
}

//====================================================================================================

void Store::handleEvent(EventNode<Customer,CheckoutLine> E)
{
	//Print The Current Time
	printf("========================= %lu =========================\n\n", Time);
	//cout << EventQ.to_str() << endl;

	//Print the Status of the CheckoutLines and Customers
	printLines();
	printCusts();

	//Print the Current Event being Processed
	printf("PROCESSING EVENT\n");
	printEvent(E.get_time(), E.get_obj1(), E.get_obj2(), E.get_type());

	//==================================================
	if(E.get_type() == CUSTOMER_ARRIVES)
	{
		//Create New Customer Object in Heap Memory
		Customer *aCustomer = new Customer(Time);
		//Add the New Customer to the Store's Vector of all Customers
		Shopping.push_back(*aCustomer);

		//Calculate how Long the Customer will Shop based on Number of Items
		int shopTime = genShopTime(aCustomer->getNumItems());
		aCustomer->setCheckoutLength(genCashTime(aCustomer->getNumItems()));

		//Add Checkout_Ready Event for New Customer
		EventQ.make_event(Time+shopTime, aCustomer, aCustomer->getID(), NULL, 0, CUSTOMER_CHECKOUT_READY);

		//Create a Checkout_Ready Event and Print It
		printf("CREATED EVENT\n");
		printEvent(Time+shopTime, aCustomer, NULL, CUSTOMER_CHECKOUT_READY);

		//Calculate when Next Customer Arrives
		int nextArriveTime = Time + genRandExp(arrivalSeed) + 1;
		//Add Customer_Arrives Event
		EventQ.make_event(nextArriveTime, NULL, 0, NULL, 0, CUSTOMER_ARRIVES);

		//Create a Customer_Arrives Event and Print It
		printf("CREATED EVENT\n");
		printEvent(nextArriveTime, NULL, NULL, CUSTOMER_ARRIVES);
	}
	//==================================================
	else if(E.get_type() == CUSTOMER_CHECKOUT_READY)
	{
		//Pull Customer Pointer from Event
		Customer *C = E.get_obj1();
		//Determine Time that Customer will Abandon Store, This Value Will Not Change
		C->setAbandonTime(Time);
		//Track When Customer Starts Waiting to be Checked Out
		C->setInLineTime(Time);

		//Decide which CheckoutLine the Customer should Join
		CheckoutLine *L = chooseLine(C->getNumItems());
		//Update CheckoutLine Variables
		L->incNumCustomers(*C);
		L->updateNumItems(C->getNumItems());

		makeDecision(C, L);
	}
	//==================================================
	else if(E.get_type() == CUSTOMER_CHECKOUT_FINISH)
	{
		// TODO Calculate Statistics about Customer

		//Pull Customer Pointer from Event
		Customer *C = E.get_obj1();
		//Pull CheckoutLine Pointer from Event
		CheckoutLine *L = E.get_obj2();

		//Update CheckoutLine Variables
		L->decNumCustomers(*C);
		L->updateWaitTime(-1 * C->getCheckoutLength());
		L->updateNumItems(-1 * C->getNumItems());

		WaitTimes.push_back(Time - C->getInLineTime() - C->getCheckoutLength());

		NumCheckouts = NumCheckouts + 1;

		//Remove Customer from Global Shopping Vector
		removeCustomer(C->getID());
		delete(C);

		//Free Memory Allocated to Customer ?
	}
	//==================================================
	else if(E.get_type() == CUSTOMER_CHANGES_LINE)
	{
		//Pull Customer Pointer from Event
		Customer *C = E.get_obj1();
		//Pull CheckoutLine Pointer from Event
		CheckoutLine *oldL = E.get_obj2();
		//Decide which CheckoutLine the Customer should Change To
		CheckoutLine *newL = chooseLine(C->getNumItems());

		//Update CheckoutLine Variables for Line that Customer is Leaving
		oldL->decNumCustomers(*C);
		oldL->updateNumItems(-1 * C->getNumItems());
		//Update CheckoutLine Variables for Line that Customer is Joining
		newL->incNumCustomers(*C);
		newL->updateNumItems(C->getNumItems());

		makeDecision(C, newL);
	}
	//==================================================
	else if(E.get_type() == CUSTOMER_ABANDONS_LINE)
	{
		//Pull Customer Pointer from Event
		Customer *C = E.get_obj1();
		//Pull CheckoutLine Pointer from Event
		CheckoutLine *L = E.get_obj2();

		//Update CheckoutLine Variables for Line that Customer is Leaving
		L->decNumCustomers(*C);
		L->updateNumItems(-1 * C->getNumItems());

		WaitTimes.push_back(Time - C->getInLineTime());

		//Remove Customer from Global Shopping Vector
		removeCustomer(C->getID());
		delete(C);

		//Free Memory Allocated to Customer ?
	};
	//==================================================
}

//Decide Whether a Customer Will Checkout, Change Lines, or Abandon Line
void Store::makeDecision(Customer *C, CheckoutLine *L)
{
	//Customer Has 3 Options: Stay In Line, Change Lines, Abandon Store
	int StTime = L->getWaitTime()  + Time; //Time Customer would Start Checkout (Scanning Items)
	int ChTime = C->getOppFactor() + Time; //Time Customer would Switch Lines
	int AbTime = C->getAbandonTime();      //Time Customer would Abandon Store

	//Create an Event that Corresponds to Soonest of the 3 Times
	//======================================================================
	if(StTime <= ChTime && StTime <= AbTime) //Customer will Finish Checkout in Current Line
	{
		//Update WaitTime of CheckoutLine
		L->updateWaitTime(C->getCheckoutLength());

		//Time that Customer Finishes Checkout Equals...
		//Time Waiting in Line + Time Scanning Items + Current Time
		int FinishTime = StTime + C->getCheckoutLength();
		//Add Checkout_Finish Event
		EventQ.make_event(FinishTime, C, C->getID(), L, L->getID(), CUSTOMER_CHECKOUT_FINISH);

		//Print Event
		printf("CREATED EVENT\n");
		printEvent(FinishTime, C, L, CUSTOMER_CHECKOUT_FINISH);
	}
	//======================================================================
	if(ChTime < StTime && ChTime <= AbTime) //Customer will Switch Checkout Lines
	{
		//Add Changes_Line Event
		EventQ.make_event(ChTime, C, C->getID(), L, L->getID(), CUSTOMER_CHANGES_LINE);

		//Print Event
		printf("CREATED EVENT\n");
		printEvent(ChTime, C, L, CUSTOMER_CHANGES_LINE);
	}
	//======================================================================
	if(AbTime < StTime && AbTime < ChTime) //Customer will Abandon Store
	{
		//Create Abandons_Line Event
		EventQ.make_event(AbTime, C, C->getID(), L, L->getID(), CUSTOMER_ABANDONS_LINE);

		//Print Event
		printf("CREATED EVENT\n");
		printEvent(AbTime, C, L, CUSTOMER_ABANDONS_LINE);
	}
	//======================================================================
}

//====================================================================================================

int Store::getTime()
{
	return Time;
}

void Store::incTime()
{
	Time = Time+1;
}

void Store::setTime(int t)
{
	Time = t;
}

void Store::setStrategy(QueueStrategy S)
{
	Strat = S;
}

//====================================================================================================

int Store::genCashTime(int numItems)
{
	int r = floor((0.20*numItems) + 1);
	return(r);
}

int Store::genShopTime(int numItems)
{
	int r = floor((0.80*numItems) + 2);
	return(r);
}

void Store::removeCustomer(int ID)
{
	int i;
	for(i = 0; i < Shopping.size(); i++)
	{
		if(Shopping[i].getID() == ID)
		{
			Shopping.erase(Shopping.begin()+i);
			break;
		}
	}
}

//====================================================================================================

void Store::addCheckoutLine(CheckoutLine *L)
{
	Lines.push_back(L);
}

//Based on Queueing Strategy, Choose the Best Line for the Customer to Join
CheckoutLine* Store::chooseLine(int Items)
{
	CheckoutLine *L = Lines.front();
	int i;

	switch(Strat)
	{
	//======================================================================
		case NUM_ITEMS :
			for(i = 0; i < Lines.size(); i++)
			{
				if(Lines[i]->getNumItems()<L->getNumItems() && Items<=Lines[i]->getItemLimit() && Lines[i]->getStatus())
				{
					L = Lines[i];
				}
			}
			break;
	//======================================================================
		case NUM_CUSTOMERS :
			for(i = 0; i < Lines.size(); i++)
			{
				if(Lines[i]->getNumCustomers()<L->getNumCustomers() && Items<=Lines[i]->getItemLimit() && Lines[i]->getStatus())
				{
					L = Lines[i];
				}
			}
			break;
	//======================================================================
		case WAIT_TIME :
			for(i = 0; i < Lines.size(); i++)
			{
				if(Lines[i]->getWaitTime()<L->getWaitTime() && Items<=Lines[i]->getItemLimit() && Lines[i]->getStatus())
				{
					L = Lines[i];
				}
			}
			break;
	//======================================================================
		case RANDOM :
			L = Lines[genRandUni(0, Lines.size()-1)];
			while(Items>L->getItemLimit() || L->getStatus()==false)
			{
				L = Lines[genRandUni(0, Lines.size()-1)];
			}
	//======================================================================
	}
	return(L);
}

//====================================================================================================

double Store::getAvgWaitTime()
{
	if(WaitTimes.size()==0)
	{
		return 0;
	}
	else
	{
		int t = 0;
		for(int i = 0; i < WaitTimes.size(); i++)
		{
			t += WaitTimes[i];
		}
		AvgWaitTime = (double)t / (double)WaitTimes.size();
		return AvgWaitTime;
	}
}

double Store::getCheckoutRate()
{
	if(Time != 0)
	{
		CheckoutRate = (double) NumCheckouts / (double)((double)Time/60);
		return CheckoutRate;
	}
	else
	{
		return 0;
	}
}

//====================================================================================================
void Store::printCusts()
{
	int i;
	for(i = 0; i < Shopping.size(); i++)
	{
		printf("(Cust %2d)     Item: %3d     OppF: %3d     ImpF: %3d\n",
		Shopping[i].getID(),Shopping[i].getNumItems(),Shopping[i].getOppFactor(),Shopping[i].getImpFactor());
	}
}

void Store::printLines()
{
	int i;
	for(i = 0; i < Lines.size(); i++)
	{
		printf("(Line %2d)     Wait: %3d     Cust: %3d     Item: %3d\n",
		Lines[i]->getID(),Lines[i]->getWaitTime(),Lines[i]->getNumCustomers(),Lines[i]->getNumItems());
	}
}

void Store::printEvent(unsigned long Time, Customer *C, CheckoutLine *L, eventType eT)
{
	//===================================
	printf("< %3lu  ", Time);
	//===================================
	if(C==NULL){
		printf("NULL  ");
	}
	else{
		printf("C%-3d  ",C->getID());
	}
	//===================================
	if(L==NULL){
		printf("NULL  ");
	}
	else{
		printf("L%-3d  ",L->getID());
	}
	//===================================
	switch(eT)
	{
		case 0: printf("CUSTOMER_ARRIVES >");
			break;
		case 1: printf("CUSTOMER_CHECKOUT_READY >");
			break;
		case 2: printf("CUSTOMER_CHECKOUT_FINISH >");
			break;
		case 3: printf("CUSTOMER_CHANGES_LINE >");
			break;
		case 4: printf("CUSTOMER_ABANDONS_LINE >");
			break;
		case 5: printf("VOID_EVENT >");
			break;
	}
	//===================================
	printf("\n\n");
}

//====================================================================================================
//Generate Number from Exponential Distrubtion with Mean = Beta
double Store::genRandExp(double beta) const
{
  double u, x;
  u = drand48();
  x = -beta * log(1.0 - u);
  return(x);
}

//Generate Number from Uniform Distribution Between Low and High
double Store::genRandUni(int low, int high) const
{
	double r1, r2;
  int rtnval;
  r1 = drand48();
	r2 = (1 + high - low) * r1;
	rtnval = low + floor(r2);
	return(rtnval);
}

//====================================================================================================
