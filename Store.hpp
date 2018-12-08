//
// Written by Andrew Nolin and William Slocum
//

#include<list>
#include<queue>
#include<vector>
#include<cmath>
#include<unordered_map>
#include<cmath>

#include "Customer.hpp"
#include "CheckoutLine.h"
#include "Event.hpp"

using namespace std;

class Store
{
	private:

		static unsigned long int Time;

		static int arrivalSeed;

	public:

		Store();
		~Store();

		enum QueueStrategy {RANDOM, NUM_CUSTOMERS, NUM_ITEMS, WAIT_TIME};

		//Event Queue
		EventQueue<Customer, CheckoutLine> EventQ;

		//Vector of Customers
		vector<Customer> Shopping;

		//Vector of CheckoutLines
		vector<CheckoutLine*> Lines;

		//Queueing Strategy for Store
		QueueStrategy Strat;

		//Fields for Store Statistics
		vector<int> WaitTimes;
		double AvgWaitTime;
		int NumCheckouts;
		double CheckoutRate;

		//==================================================

		//Event Processing Functions
		void handleEvent(EventNode<Customer,CheckoutLine> E);
		void makeDecision(Customer *C, CheckoutLine *L);

		//Time Functions
		int getTime();
		void incTime();
		void setTime(int t);
		void setStrategy(QueueStrategy S);

		//Customer Functions
		int genCashTime(int numItems);
		int genShopTime(int numItems);
		void removeCustomer(int ID);

		//CheckoutLine Functions
		void addCheckoutLine(CheckoutLine *L);
		CheckoutLine* chooseLine(int Items);

		//Store Statistic Functions
		double getAvgWaitTime();
		double getCheckoutRate();

		//Printing Functions
		void printCusts();
		void printLines();
		void printEvent(unsigned long Time, Customer *C, CheckoutLine *L, eventType eT);

		//Random Number Generation
		double genRandExp(double beta) const;
		double genRandUni(int low, int high) const;

};
