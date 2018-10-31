/*
 * Store.hpp
 * The Store class contains:
 * 	event queue
 * 	event queue node struct
 *	customer struct
 *	checkout lines that hold customers
 *	a vector to hold customers while they are shopping
 * 	cashiers
 *
 * The Store class should communicate with GUI contorller 
 * 
 * TODO
 * cashiers
 * GUI
 * n items or fewer lines
 * customer movement
 * add new cashiers
 */

//lib includes
#include<list>
#include<queue>
#include<vector>
//class includes
//defs

using namespace std;

class Store{
	private:
		//fields
		unsigned long int time;
		//eventType is an enum for all types of events
		enum eventType {CUSTOMER_ARRIVES, CUSTOMER_CHECKOUT_READY, CUSTOMER_CHECKOUT_FINISH, 
				CUSTOMER_CHANGES_LINE, CUSTOMER_ABANDONS_LINE};


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
		}Customer;
		

		//event struct holds data needed for an event  
		typedef struct{
			unsigned long int exe_time;
			eventType type;
			Customer *cust;
		}Event;


		//lines is a vector of lists to hold customers
		vector<list<Customer>>lines;
		
		//eventQ is the priority queue for Event structs sorted by time
		priority_queue<Event> eventQ;

		//shopping is the vector where customers will go when they enter the store but are not in line yet
		vector<Customer> shopping;		
		
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
		//custIn creates a customer that arrives at time t
		void customerIn(unsigned long int t);
};//end store class
