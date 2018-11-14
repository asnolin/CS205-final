/*
 * EventNode.hpp
 * 
 * EventNode<T> is a template class
 * for a class T, an EventNode<T> contains a pointer to an object of that class
 * 
 * TODO
 * finish eventQueue
 * rename file
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
		
		evetnType get_type();

};//end EventNode



template<class T>
class EventQueue{
	private:
		priority_queue<EventNode<T>> eventQ;	//priority queue that contains EventNodes
		unsigned long int currentTime;	//minimum time an event can be
	public:
		//no-arg construtctor
		EventQueue();
		
		//creates a new EventNode of class T and adds it to the pq
		//returns true when successful
		bool make_event(unsigned long int inT, T *inObj, eventType inType);

		//pops head from event queue and returns it		
		EventNode pop();

		//get time for event queue
		unsigned long int get_current_time();


}//end EventQueue
