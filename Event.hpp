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
 */

#include<memory>
#include<queue>
#include<vector>
#include<string>
#include<sstream>
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





template<class T, class S>
class EventQueue{
	private:
	//priority queue that contains EventNodes
	//priority_queue<EventNode<T, S>, std::deque<EventNode<T, S> >, std::greater<EventNode<T, S> > > eventQ;	

	//minimum time an event can be and current time for the system
	unsigned long int currentTime;	
	
	/* nested class is derived from a priority_queue, but has a method to return a pointer to the container
	 * Found the container variable, c,  in the bits/stl_queue.h file which defines the priority_queue
	 * this allows for printing of the event queue
	 */
	
	class MyPQ : public std::priority_queue<EventNode<T, S>, 
	std::deque<EventNode<T, S> >, std::greater<EventNode<T, S> > >{

		public:
		deque<EventNode<T, S> > get_container() const{
			deque<EventNode<T, S> > copy = deque<EventNode<T, S> >(priority_queue<EventNode<T, S>, std::deque<EventNode<T, S> >, std::greater<EventNode<T, S> > >::c);
			return copy;
		}//end get_container
				

	};//end MyPQ class

	//instance of the MyPQ class
	MyPQ eventQ;

	public:
	//no-arg construtctor
	EventQueue();
	
	//creates a new EventNode of class T and adds it to the pq
	//returns true when successful
	bool make_event(unsigned long int inT, T *inObj1, S *inObj2,  eventType inType);

	//removes head EventNode and returns a copy of it	
	EventNode<T, S> pop();

	//advance head
	void advance_head();

	//get time for event queue
	unsigned long int get_current_time();

	//get event type of head
	eventType get_current_type();

	//get pointer to obj1 of head
	T* get_ptr1();

	//get pointer to obj2 of head
	S* get_ptr2();
	
	//print the event queue
	string to_str();

};//end EventQueue



//EventQueue constructor
template<class T, class S>
EventQueue<T, S>::EventQueue(){
	//init currentTime
	currentTime = 0;
}//end no-arg constructor


//priority_queue manipulators
template<class T, class S>
bool EventQueue<T, S>::make_event(unsigned long int inT, T *inObj1, S *inObj2, eventType inType){
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

template<class T, class S>
EventNode<T, S> EventQueue<T, S>::pop() {
	if(eventQ.empty()){
		throw std::runtime_error("empty eventQ");
	}else{
		//save head and pop head from priority_queue
		EventNode<T, S> head  = eventQ.top();
		eventQ.pop();
		//update currentTime to the popped event's time
		currentTime = head.get_time();
		return head;
	}
}//end pop()


//TODO
//does this need to delete the EventNode?
template<class T, class S>
void EventQueue<T, S>::advance_head(){
	if(!eventQ.empty()){
		//delete the eventNode here?
		//pop head element and update currentTime
		eventQ.pop();
		EventNode<T, S> node = eventQ.top();
		currentTime = node.get_time();
	}
}//end advance_head


//EventQueue getters
//TODO
//ask lisa why I can't do something like:
//eventType type = eventQ.top().get_type();
//becuase I get a "passing const value_type as 'this' argument discared qualifiers
//eventQ.top() is a const reference to an eventNode
//I can do EventNode<T, S> node = eventQ.top();
//If this is possible, would it result in a speedup 
//
//
template<class T, class S>
unsigned long int EventQueue<T, S>::get_current_time(){
	EventNode<T, S> node = eventQ.top();
	currentTime = node.get_time();
	return currentTime;
}//end get_current_time

template<class T, class S>
eventType EventQueue<T, S>::get_current_type(){
	if(eventQ.empty()){
		return VOID_EVENT;
	}else{
		EventNode<T, S> node = eventQ.top();
		return node.get_type();
	}
}//end get_type

template<class T, class S>
T* EventQueue<T, S>::get_ptr1(){
	if(eventQ.empty()){
		return nullptr;
	}else{
		EventNode<T, S> node  = eventQ.top();
		return node.get_obj1();
	}
}//end get_obj1

template<class T, class S>
S* EventQueue<T, S>::get_ptr2(){
	if(eventQ.empty()){
		return nullptr;
	}else{
		EventNode<T, S> node = eventQ.top();
		return node.get_obj2();
	}
}//end get_obj2


//TODO
//can I copy the eventQ to cpyQueue?
//if not, I need to pop from eventQ and then emplace nodes back in 
////print_queue
template<class T, class S>
string EventQueue<T, S>::to_str(){
	const deque<EventNode<T, S> > myDeque = eventQ.get_container();
	string str;
	str =  "the number of items in the event queue is: ";
	int i = 0;
	for(auto itr = myDeque.cbegin(); itr != myDeque.cend(); ++itr){
		++i;
	}
	ostringstream number;
	number << i;
	str += number.str();
	return str;

}//end print_queue

