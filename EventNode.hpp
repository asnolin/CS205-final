/*
 * EventNode.hpp
 *
 */

#include<"Customer.hpp"
using namespace std;
enum eventType {CUSTOMER_ARRIVES, CUSTOMER_CHECKOUT_READY, CUSTOMER_CHECKOUT_FINISH, 
		CUSTOMER_CHANGES_LINE, CUSOMER_ABANDONS_LINE};


class EventNode{
	private:
		unsigned long int time; //time that event will occur at
		Customer *cust; //customer involved in event
		eventType type; //type of event
	public:
		//no-arg constructor
		EventNode();
		
		//destructor
		~EventNode();
		
		//constructor
		EventNode(unsigned long int inTime, Customer &inCust, eventType inType);

		//overloaded < operator for priority_queue
		bool operator<(EventNode rhs) const;

		//get time of event	
		unsigned long int get_time();

		//get customer pointer
		Customer *get_cust();

		//get event type
		eventType get_type();
		
		
};//end EventNode
