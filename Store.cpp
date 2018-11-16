/*
 * Store.cpp
 * TODO
 * PRIORITY_QUEUE WILL NOT BE ABLE TO REMOVE ELEMENTS THAT ARE NOT HEAD
 * MUST MAKE OWN PRIORITY QUEUE THAT IS ABLE TO DO THAT
 */

//include Store header file
#include "Store.hpp"

/*
//====================================================================================================
void Store::handleEvent(Event E)
{
	//Get Event Type
	EventType T = E.get_type()
	//==================================================
	if(T == CUSTOMER_ARRIVES)
	{
		//Create New Customer Object
		Customer aCustomer(Time);

		//Calculate How Long the Customer Will Shop
		int shopTime = calcCheckoutTime(aCustomer.getNumItems());

		//Add CHECKOUT_READY Event For New Customer
		Event newEvent1(Time+shopTime, CUSTOMER_CHECKOUT_READY, aCustomer, NULL);
		EventQ.push(newEvent1);

		//Calculate When Next Customer Arrives
		int nextArriveTime = Time + genRandExp(arrivalSeed);

		//Add CUSTOMER_ARRIVES Event to Event Queue
		Event newEvent2(nextArriveTime, CUSTOMER_ARRIVES, NULL, NULL);
		EventQ.push(newEvent2);
	}
	//==================================================
	else if(T == CUSTOMER_CHECKOUT_READY)
	{
		Customer *C = E.get_obj();
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
			csTime = calcCashierTime(C->getNumItems());

			//Update Line Variables
			L->incNumCustomers();
			L->updateNumItems(C->getNumItems());
			L->updateWaitTime(csTime);

			FinishTime = chTime + csTime;
			EventQ.make_event(FinishTime, CUSTOMER_CHECKOUT_FINISH, C, L);
		}

		if(swTime<chTime & swTime<=abTime)
		{
			L->incNumCustomers();
			L->updateNumItems(C->getNumItems());

			EventQ.make_event(swTime, CUSTOMER_CHANGES_LINE, C, L);
		}

		if(abTime<swTime & abTime<chTime)
		{
			L->incNumCustomers();
			L->updateNumItems(C->getNumItems());

			EventQ.make_event(abTime, CUSTOMER_ABANDONS_LINE, C, L);
		}
	}
	//==================================================
	else if(T == CUSTOMER_CHECKOUT_FINISH)
	{
		// TODO Calculate Statistics about Customer
		Customer *C = E.getCust();
		CheckoutLone *L = E.getLine();

		L->decNumCustomers();
		L->updateNumItems(-1 * C->getNumItems());

		//Free Memory Allocated to Customer ?
	}
	//==================================================
	else if(T == CUSTOMER_CHANGES_LINE)
	{
		Customer *C = E.getCust();
		CheckoutLone *oldL = E.getLine();
		CheckoutLine *newL = chooseLine();

		oldL->decNumCustomers();
		oldL->updateNumItems(-1 * C->getNumItems());

		int chTime = newL->getWaitTime();
		int swTime = C->getOppFactor() + Time;
		int abTime = C->getAbandonTime();

		//Create Event Based on Shortest of the Times
		if(chTime<=swTime & chTime<=abTime)
		{
			csTime = calcCashierTime(C->getNumItems());

			//Update Line Variables
			newL->incNumCustomers();
			newL->updateNumItems(C->getNumItems());
			newL->updateWaitTime(csTime);

			FinishTime = chTime + csTime;
			EventQ.make_event(FinishTime, CUSTOMER_CHECKOUT_FINISH, C, newL);
		}
		if(swTime<chTime & swTime<=abTime)
		{
			newL->incNumCustomers();
			newL->updateNumItems(C->getNumItems());

			EventQ.make_event(swTime, CUSTOMER_CHANGES_LINE, C, newL);
		}
		if(abTime<swTime & abTime<chTime)
		{
			newL->incNumCustomers();
			newL->updateNumItems(C->getNumItems());

			EventQ.make_event(abTime, CUSTOMER_ABANDONS_LINE, C, newL);
		}

	}
	//==================================================
	else if(T == CUSTOMER_ABANDONS_LINE)
	{
		L->decNumCustomers();
		L->updateNumItems(-1 * C->getNumItems());

		//Free Memory Allocated to Customer ?
	};
	//==================================================
}
//====================================================================================================
*/

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

//no-arg Store constructor
Store::Store(){
	Time = 0;

}//end store default constructor

//Store destructor
//TODO
Store::~Store(){

}//end store default destructor
