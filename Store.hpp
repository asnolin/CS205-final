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

		//eventQ is the priority queue for Event structs sorted by time
		priority_queue<Event> eventQ;

		//shopping is the vector where customers will go when they enter the store but are not in line yet
		vector<Customer> shopping;

		//cashiers are a mapping of
		//private functions


	public:
		//constructor
		Store();
		//destructor
		~Store();

		//public functions


};//end store class
