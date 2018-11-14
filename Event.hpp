/*
 * Event.hpp
 * 
 * EventNode<T> and EventQueue<T> are class templates
 *
 * for a class T, an EventNode<T> contains a pointer to an object of that class
 * and EventQueue<T> produces EventNode<T> object for its pop() function
 * 
 * No need for an Event.cpp because both are class templates
 * TODO
 * implement exceptions?
 * field for line pointer in EventNode
 */

#include<memory>
#include<queue>
using namespace std;

//TODO
//would be nice to be able to overwrite this definition from another file
//#ifdef and #ifndef?
//
//eventType stores the enumeration of all possible event types the EventNode can be
enum eventType {CUSTOMER_ARRIVES, CUSTOMER_CHECKOUT_READY, CUSTOMER_CHECKOUT_FINISH, 
		CUSTOMER_CHANGES_LINE, CUSOMER_ABANDONS_LINE, VOID_EVENT};

	
		//nested struct EventNode
template<class T>	
class EventNode{
	private:
		unsigned long int time; //time that event will occur at
		T *obj; //pointer to object involved in event

		eventType type; //type of event
	public:
		//no-arg constructor
		EventNode();
		
		//constructor
		EventNode(unsigned long int inTime, T *inObj, eventType inType);

		//overloaded < operator for priority_queue
		bool operator<(EventNode rhs) const;		

		//getters
		unsigned long int get_time();

		T *get_obj();
		
		eventType get_type();

};//end EventNode



template<class T>
class EventQueue{
	private:
		priority_queue<EventNode<T>> eventQ;	//priority queue that contains EventNodes
		unsigned long int currentTime;	//minimum time an event can be and current time for the system
	public:
		//no-arg construtctor
		EventQueue();
		
		//creates a new EventNode of class T and adds it to the pq
		//returns true when successful
		bool make_event(unsigned long int inT, T *inObj, eventType inType);

		//pops head from event queue and returns it		
		EventNode<T> pop();

		//get time for event queue
		unsigned long int get_current_time() noexcept;


};//end EventQueue


//Event Node constructors
template<class T>
EventNode<T>::EventNode(){
	time = 1;
	obj = nullptr;
	type = VOID_EVENT;
}//end no-arg constructor

template<class T>
EventNode<T>::EventNode(unsigned long int inTime, T *inObj, eventType inType){
	time = inTime;
	obj = inObj;
	type = inType;
}//end constructor



//EventNode overloaded <
template<class T>
bool EventNode<T>::operator<(EventNode rhs) const{
	return time < rhs.time;
}//end overloaded < op


//EventNode getters
template<class T>
unsigned long int EventNode<T>::get_time(){
	return time;
}//end get_time

template<class T>
T *EventNode<T>::get_obj(){
	return obj;
}//end get_obj

template<class T>
eventType EventNode<T>::get_type(){
	return type;
}//end get_type


//EventQueue constructor
template<class T>
EventQueue<T>::EventQueue(){
	//init currentTime
	currentTime = 0;
	//TODO
	//init the eventQ?
}//end no-arg constructor

template<class T>
bool EventQueue<T>::make_event(unsigned long int inT, T*inObj, eventType inType){
	//TODO
	//check if inT >= currentTime. return false if inT < currentTime
	if(inT < currentTime){
		return false;
	}else{
		//create new EventNode
		EventNode<T> node = EventNode<T>::EventNode(inT, *inObj, inType);
		//add EventNode to eventQ
		eventQ.push(node);
		//return true if successful
		return true;
	}
}//end make_event



//EventQueue get current time
template<class T>
unsigned long int EventQueue<T>::get_current_time() noexcept{
	return currentTime;
}//end get_current_time



template<class T>
EventNode<T> EventQueue<T>::pop() {
	//TODO
	if(eventQ.empty()){
		throw std::runtime_error("empty eventQ");
	}else{
		EventNode<T> node = eventQ.top();
		//update currentTime to the popped event's time
		currentTime = node.get_time();
		return node;
	}
}//end pop()
