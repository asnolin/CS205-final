/*
 * Store.cpp
 * TODO
 * PRIORITY_QUEUE WILL NOT BE ABLE TO REMOVE ELEMENTS THAT ARE NOT HEAD
 * MUST MAKE OWN PRIORITY QUEUE THAT IS ABLE TO DO THAT
 */

//include Store header file
#include"Store.hpp"

void Store::handleEvent(Event E){
	// eventType t = E.getEventType();

	if(t == CUSTOMER_ARRIVES){
		Customer aCustomer(Time);
		//TODO readyCheckoutTime = calculate checkout time using aCustomer.getNumItems()
		//makeEvent(time+readyCheckoutTime, CUSTOMER_CHECKOUT_READY, E.getCustomer);

		//TODO arrivalInterval = find next arrival interval
		//makeEvent(time+arrivalInterval, CUSTOMER_ARRIVES, NULL)
	}
	else if(t == CUSTOMER_CHECKOUT_READY){
		//choose line
		//calculate three times
			// finishes checkout
			// changes line
			// abandons line
		//update checkout line variables
		//makeEvent based on shortest of the times
	}
	else if(t == CUSTOMER_CHECKOUT_FINISH){
		//int waitTime = E.getCustomer -> getInStoreTime();

	}
	else if(t == CUSTOMER_CHANGES_LINE){
		//choose new line
		//update checkout line variables
	}
	else if(t == CUSTOMER_ABANDONS_LINE){
		//update line statistics
		//free customer memory
	}
}

bool Store::makeEvent(unsigned long int inTime, eventType inType, Customer &inCust){
	bool isMade = false;
	//TODO must catch bad_alloc
	Event *newEvent = new Event;
	newEvent->exe_time = inTime;
	newEvent->type = inType;
	newEvent->cust = &inCust;
	//TODO add newEvent to eventQ and update isMade when it all works

	return isMade;
}//end makeEvent

void incTime(){
	Time = Time+1
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
