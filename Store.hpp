/*
 * Store.hpp
 */

//lib includes
#include<list>
#include<queue>
//class includes
#include"Customer.hpp"
//defs

using namespace std;


/*
 * The Store Class
 * contains:
 * event queue
 * 	the event queue should contain a time, pointer to customer, and a enum of event type
 * customers
 * lines for customers
 * cashiers
 */
class Store{
	private:
		//fields
		unsigned long int time;
		enum eventType {CUSTOMER_ARRIVES, CUSTOMER_CHECKOUT_READY, CUSTOMER_CHECKOUT_FINISH, CUSTOMER_CHANGES_LINE, CUSTOMER_ABANDONS_LINE};
		//structs 
		typedef struct{
			unsigned long int exe_time;
			eventType type;
			Customer *cust;
		}event;
		//lines is an array of lists to hold customers
		list<Customer> *lines;
		priority_queue<event> eventQ;
		//private functions
		bool makeEvent(unsigned long int inTime, eventType inType, Customer &inCust);
	public:
		//constructor
		Store();
		//destructor
		~Store();
		//public functions
		
};//end store class
