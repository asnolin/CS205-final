/*
 * Store.hpp
 * The Store class contains:
 * 	event queue
 * 	event queue node struct
 *	customer struct
 *	checkout lines that hold customers
 *	a vector to hold customers while they are shopping
 * 	cashiers
 * 	cashiers could be a mapping of a cashier id values to a list addr or idex of a vector<list<Customer>>
 *	maybe map or unordered map. 
 *
 * The Store class should communicate with GUI contorller 
 * 
 * TODO
 * cashiers
 * GUI
 * n items or fewer lines
 * customer movement
 * add/remove cashiers
 */

//lib includes
#include<list>
#include<queue>
#include<vector>
#include<unordered_map>
//class includes
//defs

using namespace std;

class Store{
	private:
		//fields
		unsigned long int time;

		//seeds customer ids
		int idSeed;

		//eventType is an enum for all types of events
		enum eventType {CUSTOMER_ARRIVES, CUSTOMER_CHECKOUT_READY, CUSTOMER_CHECKOUT_FINISH, 
				CUSTOMER_CHANGES_LINE, CUSTOMER_ABANDONS_LINE};

		
		//TODO
		//change fidget to a number of ticks the customer would wait before switching a line. 
		//requires the cashiers to hold the number of customers ahaead of them 
		//simple imp might be to hold number of items, that way customers would never switch because they
		//would always be in the fastest line
		//
		//customer struct holds data  associated with a customer
		typedef struct{
			//items is the number of items the customer has
			//influences checkout time and shopping time
			int items;

			//timeIn is the time the customer first entered the store
			unsigned long int timeIn;

			//fidget is a probability 0-1
			//determines how likley it is for a customer to switch lines or leave the store
			double fidget;

			//customer id is set by idSeed which is a global within Store
			int id;

			//list of all events involving this customer
			list<void *> custEvents;
		}Customer;
		

		//event struct holds data needed for an event  
		typedef struct{
			unsigned long int exe_time;
			eventType type;
			Customer *cust;
		}Event;
		
		//eventQ is the priority queue for Event structs sorted by time
		priority_queue<Event> eventQ;

		//shopping is the vector where customers will go when they enter the store but are not in line yet
		vector<Customer> shopping;		
		
		//cashiers are a mapping of 		
		//private functions

		//makeEvent makes an event struct with the args passed in
		// inserts event in sorted order in eventQ
		bool makeEvent(unsigned long int inTime, eventType inType, Customer &inCust);
	
	public:
		//constructor
		Store();
		//destructor
		~Store();

		//public functions
		
		
};//end store class
