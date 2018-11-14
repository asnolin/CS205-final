/*
 * Store.cpp
 * TODO
 * PRIORITY_QUEUE WILL NOT BE ABLE TO REMOVE ELEMENTS THAT ARE NOT HEAD
 * MUST MAKE OWN PRIORITY QUEUE THAT IS ABLE TO DO THAT
 */

//include Store header file
#include "Store.hpp"

void Store::handleEvent(Event E)
{
	//Get Event Type
	eventType t = E.get_type()

	if(t == CUSTOMER_ARRIVES)
	{
		//Create New Customer Object
		Customer aCustomer(Time);

		int shopTime = calcCheckoutTime(aCustomer.getNumItems());

		Event newEvent1(Time+shopTime, CUSTOMER_CHECKOUT_READY, E.getCustomer());
		eventQ.push(newEvent1);

		int arrivalInterval = genRandExp(arrivalSeed);

		Event newEvent2(Time+arrivalInterval, CUSTOMER_ARRIVES, NULL, NULL);
		eventQ.push(newEvent2);
	}

	else if(t == CUSTOMER_CHECKOUT_READY)
	{
		Customer *C = E.get_obj();
		CheckoutLine *L = chooseLine();


		//Given a Pointer to a Checkout Line (L)...
		//Calculate 3 Times
			// Finishes Checkout
			// Changes Line
			// Abandons Line

		C->setAbandonTime(Time);

		int CheckoutTime = L->getWaitTime();
		int SwitchTime = C->getOppFactor + Time;
		int AbandonTime = C->getAbandonTime;

		//Update Checkout Line Variables

	  //Create Event Based on Shortest of the Times
		if(CheckoutTime<=SwitchTime & CheckoutTime<=AbandonTime)
		{
			FinishTime = CheckoutTime + calcCheckoutTime(C->numItems);
			eventQ.make_event(FinishTime, CUSTOMER_CHECKOUT_FINISH, C, L);
		}
		if(SwitchTime<CheckoutTime & SwitchTime<=AbandonTime)
		{
			eventQ.make_event(SwitchTime, CUSTOMER_CHANGES_LINE, C, L);
		}
		if(AbandonTime<SwitchTime & AbandonTime<CheckoutTime)
		{
			eventQ.make_event(AbandonTime, CUSTOMER_ABANDONS_LINE, C, L);
		}
	};
	/*
	else if(t == CUSTOMER_CHECKOUT_FINISH)
	{
		// TODO Calculate Statistics about Customer

	}

	else if(t == CUSTOMER_CHANGES_LINE)
	{
		//TODO Choose New Line
		//TODO Update Checkout Line Variables
	}

	else if(t == CUSTOMER_ABANDONS_LINE)
	{
		//TODO Update Line Statistics
		//Free Customer Memory
	}
	*/
}

void Store::addCheckoutLine(CheckoutLine Line){
	//TODO
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

void Store::incTime(){
	Time = Time+1;
}

int Store::calcShoppingTime(int numItems){
	//TODO
	return(numItems);
}

int Store::calcCheckoutTime(int numItems){
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

//TODO

int main(){
	printf("Hello World");
}
