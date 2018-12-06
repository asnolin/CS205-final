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



//TODO
//ask lisa why I can't do something like:
//eventType type = eventQ.top().get_type();
//return eventQ.top().get_type()
//becuase I get a "passing const value_type as 'this' argument discared qualifiers
//eventQ.top() is a const reference to an eventNode
//I can do EventNode<T, S> node = eventQ.top();
//If this is possible, would it result in a speedup
#include<memory>
#include<queue>
#include<vector>
#include<string>
#include<sstream>
#include<iostream>
#include<iomanip>
using namespace std;


//eventType stores the enumeration of all possible event types the EventNode can be
enum eventType {CUSTOMER_ARRIVES, CUSTOMER_CHECKOUT_READY, CUSTOMER_CHECKOUT_FINISH,
		CUSTOMER_CHANGES_LINE, CUSTOMER_ABANDONS_LINE, VOID_EVENT};


		//nested struct EventNode
template<class U, class V>
class EventNode{
	private:
	unsigned long int time; //time that event will occur at
	U *obj1; //pointer to first object involved in event
	int id1; //id of the first object
	V *obj2; //pointer to second object involved in event
	int id2; //id of the second object
	eventType type; //type of event

	public:
	//no-arg constructor
	EventNode()
		time = 1;
		obj1 = nullptr;
		id1 = 0;
		obj2 = nullptr;
		id2 = 0;
		type = VOID_EVENT;
	}//end no-arg consturctor

	//constructor
	EventNode(unsigned long int inTime, U *inObj1, int inId1, V *inObj2, int inId2, eventType inType){
		time = inTime;
		obj1 = inObj1;
		id1 = inId1;
		obj2 = inObj2;
		id2 = inId2;
		type = inType;
	}//end constructor


	//overloaded < operator for priority_queue
	bool operator<(EventNode<U, V> rhs) const{
		return time < rhs.time;
	}//end overloaded < op

	//overloaded > operator for vector
	bool operator>(EventNode<U, V> rhs) const{
		return time > rhs.time;
	}//end overloaded > op

	//getters
	unsigned long int get_time(){
		return time;
	}//end get_time

	U *get_obj1(){
		return obj1;
	}//end get_obj1

	int get_id1(){
		return id1;
	}//end get_id1

	V *get_obj2(){
		return obj2;
	}//end get_obj2

	int get_id2(){
		return id2;
	}//end get_id2

	eventType get_type(){
		return type;
	}//end get_type


	//to-string function
	string to_str(){
		stringstream stream;
		stream << left << setw(4) << time << "  C" << setw(3) << id1 << "  L" << setw(3) << id2 << "  ";
		switch(type){
			case CUSTOMER_ARRIVES:
				stream << "ARRIVES";
				break;
			case CUSTOMER_CHECKOUT_READY:
				stream << "CHECKOUT_READY";
				break;
			case CUSTOMER_CHECKOUT_FINISH:
				stream << "CHECKOUT_FINISH";
				break;
			case CUSTOMER_CHANGES_LINE:
				stream << "CHANGES_LINE";
				break;
			case CUSTOMER_ABANDONS_LINE:
				stream << "ABANDONS_LINE";
				break;
			case VOID_EVENT:
				stream << "VOID_EVENT";
				break;
		}
		stream << "\n";
		return stream.str();
	}//end to_str

};//end EventNode






template<class T, class S>
class EventQueue{
	private:
	unsigned long int currentTime;
	//instance of the priority queue
	priority_queue<EventNode<T, S>, std::vector<EventNode<T, S> >, std::greater<EventNode<T, S> > > eventQ;

	public:
	//no-arg construtctor
	EventQueue(){
		currentTime = 0;
	}//end no-arg constructor

	//creates a new EventNode of class T and adds it to the pq
	void make_event(unsigned long int inT, T *inObj1, int inId1, S *inObj2, int inId2,  eventType inType){
		//create new EventNode
		EventNode<T, S> node = EventNode<T, S>(inT, inObj1, inId1, inObj2, inId2, inType);
		//add EventNode to eventQ
		eventQ.push(node);
	}//end make_event


	//removes head EventNode and returns a copy of it
	EventNode<T, S> pop(){
		if(eventQ.empty()){
			throw std::runtime_error("empty eventQ");
		}else{
			//save head and pop head from priority_queue
			EventNode<T, S> head  = eventQ.top();
			eventQ.pop();
			return head;
		}
	}//end pop


/*
 * unused code
	//advance head
	void advance_head(){
		if(!eventQ.empty()){
			//pop head element and update currentTime
			eventQ.pop();
			EventNode<T, S> node = eventQ.top();
			currentTime = node.get_time();
		}
	}//end advance_head


	//getters
	//get time for event queue
	unsigned long int get_current_time(){
		EventNode<T, S> node = eventQ.top();
		currentTime = node.get_time();
		return currentTime;
	}//end get_current_time

	//get event type of head
	eventType get_current_type(){
		if(eventQ.empty()){
			return VOID_EVENT;
		}else{
			EventNode<T, S> node = eventQ.top();
			return node.get_type();
		}
	}//end get_current_type

	//get pointer to obj1 of head
	T* get_ptr1(){
		if(eventQ.empty()){
			return nullptr;
		}else{
			EventNode<T, S> node  = eventQ.top();
			return node.get_obj1();
		}
	}//end get_ptr1

	//get pointer to obj2 of head
	S* get_ptr2(){
		if(eventQ.empty()){
			return nullptr;
		}else{
			EventNode<T, S> node = eventQ.top();
			return node.get_obj2();
		}
	}//end get_ptr2


*/
	bool is_empty(){
		return eventQ.empty();
	}//end is_empty


	//print the event queue
	vector<string> to_str(){
		vector<string> vecEvents; //holds the strings
		//holds the event nodes after they are popped off
		priority_queue<EventNode<T, S>, std::vector<EventNode<T, S> >, std::greater<EventNode<T, S> > > tempPQ; 
		//holds the eventnode
		EventNode<T, S> node;
		if(!eventQ.empty()){
			while(!eventQ.empty()){
				cout << "eventQ has: " << eventQ.size() << endl;
				node = eventQ.top();
				eventQ.pop();
				vecEvents.push_back(node.to_str());
				tempPQ.push(node);
			}//end for itr
			swap(tempPQ, eventQ);
		}else{
			vecEvents.push_back("the event queue is empty\n");
		}
		return vecEvents;
	}//end to_str

};//end EventQueue
