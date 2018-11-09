/*
 * Store.cpp
 * TODO
 * PRIORITY_QUEUE WILL NOT BE ABLE TO REMOVE ELEMENTS THAT ARE NOT HEAD
 * MUST MAKE OWN PRIORITY QUEUE THAT IS ABLE TO DO THAT
 */

//include Store header file
#include"Store.hpp"

void Store::handleEvent(Event E)
{
	// eventType t = E.getEventType();

	if(t == CUSTOMER_ARRIVES)
	{
		Customer aCustomer(Time);

		int shopTime = calcCheckoutTime(aCustomer.getNumItems());

		Event newEvent1(Time+shopTime, CUSTOMER_CHECKOUT_READY, E.getCustomer());
		eventQ.push(newEvent1);

		int arrivalInterval = genRandExp(arrivalSeed);

		Event newEvent2(Time+arrivalInterval, CUSTOMER_ARRIVES, NULL);
		eventQ.push(newEvent2);
	}
	/*
	else if(t == CUSTOMER_CHECKOUT_READY)
	{
		//TODO Choose Line
		//Calculate 3 Times
			// Finishes Checkout
			// Changes Line
			// Abandons Line
		//Update Checkout Line Variables
	  //Create Event Based on Shortest of the Times
	}

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

void incTime(){
	Time = Time+1
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

}
