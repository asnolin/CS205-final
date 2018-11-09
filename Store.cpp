/*
 * Store.cpp
 * TODO
 * PRIORITY_QUEUE WILL NOT BE ABLE TO REMOVE ELEMENTS THAT ARE NOT HEAD
 * MUST MAKE OWN PRIORITY QUEUE THAT IS ABLE TO DO THAT
 */

//include Store header file
#include"Store.hpp"

//no-arg Store constructor
Store::Store(){
	time = 0;

}//end store default constructor

//Store destructor
//TODO
Store::~Store(){

}//end store default destructor

//TODO
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

