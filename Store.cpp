/*
 * Store.cpp
 * TODO
 * PRIORITY_QUEUE WILL NOT BE ABLE TO REMOVE ELEMENTS THAT ARE NOT HEAD
 * MUST MAKE OWN PRIORITY QUEUE THAT IS ABLE TO DO THAT
 */

//include Store header file
#include "Store.hpp"

//====================================================================================================
void Store::handleEvent(EventNode<Customer,CheckoutLine> E)
{
	//Get Event Type
	EventType T = E.get_type();
	//==================================================
	if(T == CUSTOMER_ARRIVES)
	{
		//Create New Customer Object
		Customer aCustomer(Time);

		Shopping.push_back(aCustomer);

		//Calculate How Long the Customer Will Shop
		int shopTime = calcCashierTime(aCustomer.getNumItems());

		//Add CHECKOUT_READY Event For New Customer
		EventQ.make_event(Time+shopTime, &(Shopping.back()), NULL, CUSTOMER_CHECKOUT_READY);

		//Calculate When Next Customer Arrives
		int nextArriveTime = Time + genRandExp(arrivalSeed);

		//Add CUSTOMER_ARRIVES Event to Event Queue
		EventQ.make_event(15, NULL, NULL, CUSTOMER_ARRIVES);
		//Event newEvent2(nextArriveTime, CUSTOMER_ARRIVES, NULL, NULL);
		//EventQ.push(newEvent2);
	}
	//==================================================
	else if(T == CUSTOMER_CHECKOUT_READY)
	{
		Customer *C = E.get_obj1();
		CheckoutLine *L = chooseLine();

		//Determine Absolute Time that Customer will Abandon Store
		C->setAbandonTime(Time);

		//Calculate the Times for the Customer's 3 Options
		int chTime = L->getWaitTime();
		int swTime = C->getOppFactor() + Time;
		int abTime = C->getAbandonTime();

	  //Create Event Based on Shortest of the Times
		if(chTime<=swTime & chTime<=abTime)
		{
			int csTime = calcCashierTime(C->getNumItems());

			//Update Line Variables
			L->incNumCustomers();
			L->updateNumItems(C->getNumItems());
			L->updateWaitTime(csTime);

			int FinishTime = chTime + csTime;
			EventQ.make_event(FinishTime, C, L, CUSTOMER_CHECKOUT_FINISH);
		}

		if(swTime<chTime & swTime<=abTime)
		{
			L->incNumCustomers();
			L->updateNumItems(C->getNumItems());

			EventQ.make_event(swTime, C, L, CUSTOMER_CHANGES_LINE);
		}

		if(abTime<swTime & abTime<chTime)
		{
			L->incNumCustomers();
			L->updateNumItems(C->getNumItems());

			EventQ.make_event(abTime, C, L, CUSTOMER_ABANDONS_LINE);
		}
	}
	//==================================================
	else if(T == CUSTOMER_CHECKOUT_FINISH)
	{
		// TODO Calculate Statistics about Customer
		Customer *C = E.get_obj1();
		CheckoutLine *L = E.get_obj2();

		L->decNumCustomers();
		L->updateWaitTime(-1 * calcCashierTime(C->getNumItems()));
		L->updateNumItems(-1 * C->getNumItems());

		//Free Memory Allocated to Customer ?
	}
	//==================================================
	else if(T == CUSTOMER_CHANGES_LINE)
	{
		Customer *C = E.get_obj1();
		CheckoutLine *oldL = E.get_obj2();
		CheckoutLine *newL = chooseLine();

		oldL->decNumCustomers();
		oldL->updateNumItems(-1 * C->getNumItems());

		int chTime = newL->getWaitTime();
		int swTime = C->getOppFactor() + Time;
		int abTime = C->getAbandonTime();

		//Create Event Based on Shortest of the Times
		if(chTime<=swTime & chTime<=abTime)
		{
			int csTime = calcCashierTime(C->getNumItems());

			//Update Line Variables
			newL->incNumCustomers();
			newL->updateNumItems(C->getNumItems());
			newL->updateWaitTime(csTime);

			int FinishTime = chTime + csTime;
			EventQ.make_event(FinishTime, C, newL, CUSTOMER_CHECKOUT_FINISH);
		}
		if(swTime<chTime & swTime<=abTime)
		{
			newL->incNumCustomers();
			newL->updateNumItems(C->getNumItems());

			EventQ.make_event(swTime, C, newL, CUSTOMER_CHANGES_LINE);
		}
		if(abTime<swTime & abTime<chTime)
		{
			newL->incNumCustomers();
			newL->updateNumItems(C->getNumItems());

			EventQ.make_event(abTime, C, newL, CUSTOMER_ABANDONS_LINE);
		}

	}
	//==================================================
	else if(T == CUSTOMER_ABANDONS_LINE)
	{
		Customer *C = E.get_obj1();
		CheckoutLine *L = E.get_obj2();

		L->decNumCustomers();
		L->updateNumItems(-1 * C->getNumItems());

		//Free Memory Allocated to Customer ?
	};
	//==================================================
}
//====================================================================================================

void Store::addCheckoutLine(CheckoutLine *L){
	Lines.push_back(L);
}

CheckoutLine* Store::chooseLine(){
	CheckoutLine *currentLine = Lines.front();

	int i;
	for(i = 0; i < Lines.size(); i++)
	{
		if(Lines[i]->getNumItems() < currentLine->getNumItems())
		{
			currentLine = Lines[i];
		}
	}

	return(currentLine);
}

int Store::getTime() const{
	return Time;
}

void Store::incTime(){
	Time = Time+1;
}

void Store::setTime(int t){
	Time = t;
}

int Store::calcShoppingTime(int numItems){
	//TODO
	return(numItems);
}

int Store::calcCashierTime(int numItems){
	//TODO
	return(numItems);
}

double Store::genRandExp(double beta) const{
  double u, x;
  u = drand48();
  x = -beta * log(1.0 - u); // this is the natural log
  return(x);
}

void Store::printQ()
{
	EventNode<Customer, CheckoutLine> E;
	while(!EventQ.is_empty())
	{
		//===================================
		E = EventQ.pop();
		//===================================
		printf("< %d  ", E.get_time());
		//===================================
		if(E.get_obj1()==NULL){
			printf("NULL ");
		}
		else{
			printf("%d  ",E.get_obj1()->getId());
		}
 		//===================================
		if(E.get_obj2()==NULL){
			printf("NULL ");
		}
		else{
			printf("%d  ",E.get_obj2()->getID());
		}
		//===================================
		switch(E.get_type())
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
		printf("\n");
	}
}

int Store::arrivalSeed = 10;
unsigned long int Store::Time = 0;

//no-arg Store constructor
Store::Store(){
	Time = 0;

}//end store default constructor

//Store destructor
//TODO
Store::~Store(){

}//end store default destructor
