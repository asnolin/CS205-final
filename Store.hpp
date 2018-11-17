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

#include "Customer.hpp"
#include "CheckoutLine.h"
#include "Event.hpp"

using namespace std;

class Store{
	private:
		//fields
		unsigned long int Time;

		//seeds customer ids
		int idSeed;
		int arrivalSeed;

		//TODO
		//change fidget to a number of ticks the customer would wait before switching a line.
		//requires the cashiers to hold the number of customers ahaead of them
		//simple imp might be to hold number of items, that way customers would never switch because they
		//would always be in the fastest line
		//

		//eventQ is the priority queue for Event structs sorted by time
		// priority_queue<Event> EventQ;

		//shopping is the vector where customers will go when they enter the store but are not in line yet


	public:
		//constructor
		Store();
		//destructor
		~Store();

		vector<Customer> Shopping;

		vector<CheckoutLine*> Lines;

		EventQueue<Customer, CheckoutLine> EventQ;

		void addCheckoutLine(CheckoutLine *L);

		void handleEvent(EventNode<Customer,CheckoutLine> E);

		int calcCashierTime(int numItems);
		int calcShoppingTime(int numItems);

		double genRandExp(double beta) const;

		CheckoutLine* chooseLine();

		int getTime() const;
		void incTime();

};//end store class
