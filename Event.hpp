/*
 * Event.hpp
 * 
 * EventNode<T> and EventQueue<T> are class templates
 *
 * for a class T, an EventNode<T> contains a pointer to an object of that class
 * and EventQueue<T> produces EventNode<T> object for its pop() function
 * 
 * No need for an Event.cpp because both are class templates
 *
 * TODO
 * implement exceptions?
 * field for line pointer in EventNode
 */

#include<memory>
#include<queue>
#include<vector>
using namespace std;

//TODO
//would be nice to be able to overwrite this definition from another file
//#ifdef and #ifndef?
//
//eventType stores the enumeration of all possible event types the EventNode can be
enum eventType {CUSTOMER_ARRIVES, CUSTOMER_CHECKOUT_READY, CUSTOMER_CHECKOUT_FINISH, 
		CUSTOMER_CHANGES_LINE, CUSOMER_ABANDONS_LINE, VOID_EVENT};

	
		//nested struct EventNode
template<class U, class V>	
class EventNode{
	private:
	unsigned long int time; //time that event will occur at
	U *obj1; //pointer to first object involved in event
	V *obj2; //pointer to second object involved in event
	eventType type; //type of event

	public:
	//no-arg constructor
	EventNode();
	
	//constructor
	EventNode(unsigned long int inTime, U *inObj1, V *inObj2, eventType inType);

	//overloaded < operator for priority_queue
	bool operator<(EventNode<U, V> rhs) const;

	//overloaded > operator for vector
	bool operator>(EventNode<U, V> rhs) const;

	//getters
	unsigned long int get_time();
	U *get_obj1();
	V *get_obj2();
	eventType get_type();

};//end EventNode



template<class T, class S>
class EventQueue{
	private:
	//priority queue that contains EventNodes
	priority_queue<EventNode<T, S>, std::vector<EventNode<T, S> >, std::greater<EventNode<T, S> > > eventQ;	

	//minimum time an event can be and current time for the system
	unsigned long int currentTime;	

	public:		
	//no-arg construtctor
	EventQueue();
	
	//creates a new EventNode of class T and adds it to the pq
	//returns true when successful
	bool make_event(unsigned long int inT, T *inObj1, S *inObj2,  eventType inType);

	//removes head EventNode and returns a copy of it	
	EventNode<T, S> pop();

	//get time for event queue
	unsigned long int get_current_time() noexcept;


};//end EventQueue


//Event Node constructors
template<class U, class V>
EventNode<U, V>::EventNode(){
	time = 1;
	obj1 = nullptr;
	obj2 = nullptr;
	type = VOID_EVENT;
}//end no-arg constructor

template<class U, class V>
EventNode<U, V>::EventNode(unsigned long int inTime, U *inObj1, V *inObj2, eventType inType){
	time = inTime;
	obj1 = inObj1;
	obj2 = inObj2;
	type = inType;
}//end constructor


//EventNode overloaded operators
template<class U, class V>
bool EventNode<U, V>::operator<(EventNode<U, V> rhs) const{
	return time < rhs.time;
}//end overloaded < op

template<class U, class V>
bool EventNode<U ,V>::operator>(EventNode<U, V> rhs) const{
	return time > rhs.time;
}//end overloaded > op


//EventNode getters
template<class U, class V>
unsigned long int EventNode<U, V>::get_time(){
	return time;
}//end get_time

template<class U, class V>
U *EventNode<U, V>::get_obj1(){
	return obj1;
}//end get_obj1

template<class U, class V>
V *EventNode<U, V>::get_obj2(){
	return obj2;
}//end get_obj2

template<class U, class V>
eventType EventNode<U, V>::get_type(){
	return type;
}//end get_type





//EventQueue constructor
template<class T, class S>
EventQueue<T, S>::EventQueue(){
	//init currentTime
	currentTime = 0;
	//TODO
	//init the eventQ?
}//end no-arg constructor

//make_event method
template<class T, class S>
bool EventQueue<T, S>::make_event(unsigned long int inT, T *inObj1, S *inObj2, eventType inType){
	//TODO
	//CREATING A NEW EVENTNODE IS NOT WORKING
	//check if inT >= currentTime. return false if inT < currentTime
	if(inT < currentTime){
		return false;
	}else{
		//create new EventNode
		EventNode<T, S> node = EventNode<T, S>(inT, inObj1, inObj2, inType);
		//add EventNode to eventQ
		eventQ.push(node);
		//return true if successful
		return true;
	}
}//end make_event



//EventQueue get current time
template<class T, class S>
unsigned long int EventQueue<T, S>::get_current_time() noexcept{
	return currentTime;
}//end get_current_time



template<class T, class S>
EventNode<T, S> EventQueue<T, S>::pop() {
	//TODO
	//needs to free EventNode?
	//TOP RETURNS A CONST-REFERENCE 
	//
	if(eventQ.empty()){
		throw std::runtime_error("empty eventQ");
	}else{
		EventNode<T, S> head  = EventNode<T, S>(eventQ.top());
		eventQ.pop();
		//update currentTime to the popped event's time
		currentTime = head.get_time();
		return head;
	}
}//end pop()
