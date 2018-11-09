/*
 * EventQueue.cpp
 *
 */

EventNode::EventNode(){
	time = 1;
	cust = NULL;
	type = NULL;
}//end no-arg constructor

EventNode::EventNode(unsigned long int inTime, void &inCust, eventType inType){
	time = inTime;
	cust = inCust;
	type = inType;
}//end constructor

EventNode::~EventNode(){
	delete time;
	delete cust;
	delete type;
}//end destructor

EventNode::bool operator<(EventNode rhs) const{
	return time < rhs.time;
}//end overloaded < op

EventNode::unsigned long int get_time(){
	return time;
}//end get_time

EventNode::Customer *get_cust(){
	return cust;
}//end get_cust()

EventNode::eventType get_type(){
	return type;
}//end get_type
