/*
 * Store.cpp
 * TODO
 * PRIORITY_QUEUE WILL NOT BE ABLE TO REMOVE ELEMENTS THAT ARE NOT HEAD
 * MUST MAKE OWN PRIORITY QUEUE THAT IS ABLE TO DO THAT
 */

//include Store header file
#include "Store.hpp"

//====================================================================================================
void Store::handleEvent(EventNode<Customer,CheckoutLine> E)
{
	//Print The Current Time
	printf("========================= %lu =========================\n\n", Time);

	//Print the Status of the CheckoutLines and Customers
	printLines();
	printCusts();

	//Print the Current Event being Processed
	printf("PROCESSING EVENT\n");
	printEvent(E);

	//==================================================
	if(E.get_type() == CUSTOMER_ARRIVES)
	{
		//Create New Customer Object in Heap Memory
		Customer *aCustomer = new Customer(Time);
		//Add the New Customer to the Store's Vector of all Customers
		Shopping.push_back(*aCustomer);

		//Calculate how Long the Customer will Shop based on Number of Items
		int shopTime = calcShoppingTime(aCustomer->getNumItems());
		//Add Checkout_Ready Event for New Customer
		EventQ.make_event(Time+shopTime, aCustomer, NULL, CUSTOMER_CHECKOUT_READY);

		//Create a Checkout_Ready Event and Print It
		printf("CREATED EVENT\n");
		EventNode<Customer, CheckoutLine> Print1(Time+shopTime, aCustomer, NULL, CUSTOMER_CHECKOUT_READY);
		printEvent(Print1);

		//Calculate when Next Customer Arrives
		int nextArriveTime = Time + genRandExp(arrivalSeed);
		//Add Customer_Arrives Event
		EventQ.make_event(nextArriveTime, NULL, NULL, CUSTOMER_ARRIVES);

		//Create a Customer_Arrives Event and Print It
		printf("CREATED EVENT\n");
		EventNode<Customer, CheckoutLine> Print2(nextArriveTime, NULL, NULL, CUSTOMER_ARRIVES);
		printEvent(Print2);
	}
	//==================================================
	else if(E.get_type() == CUSTOMER_CHECKOUT_READY)
	{
		//Pull Customer Pointer from Event
		Customer *C = E.get_obj1();
		//Decide which CheckoutLine the Customer should Join
		CheckoutLine *L = chooseLine();
		//Update CheckoutLine Variables
		L->incNumCustomers(*C);
		L->updateNumItems(C->getNumItems());

		//Determine Time that Customer will Abandon Store, This Value Will Not Change
		C->setAbandonTime(Time);

		//Customer Has 3 Options: Stay In Line, Change Lines, Abandon Store
		int chTime = L->getWaitTime(); //Time Customer would Start Checkout
		int swTime = C->getOppFactor() + Time; //Time Customer would Switch Lines
		int abTime = C->getAbandonTime(); //Time Customer would Abandon Store

	  //Create an Event that Corresponds to Lowest of the 3 Times
		if(chTime<=swTime & chTime<=abTime) //Customer will Finish Checkout in Current Line
		{
			//Update WaitTime of CheckoutLine
			L->updateWaitTime(calcCashierTime(C->getNumItems()));

			//Time that Customer Finishes Checkout Equals...
			//Time Waiting in Line + Time Scanning Items + Current Time
			int FinishTime = chTime + calcCashierTime(C->getNumItems()) + Time;
			//Add Checkout_Finish Event
			EventQ.make_event(FinishTime, C, L, CUSTOMER_CHECKOUT_FINISH);

			//Create a Checkout_Finish Event and Print It
			printf("CREATED EVENT\n");
			EventNode<Customer, CheckoutLine> Print3(FinishTime, C, L, CUSTOMER_CHECKOUT_FINISH);
			printEvent(Print3);
		}
		if(swTime<chTime & swTime<=abTime) //Customer will Switch Checkout Lines
		{
			//Add Changes_Line Event
			EventQ.make_event(swTime, C, L, CUSTOMER_CHANGES_LINE);

			//Create a Changes_Line Event and Print It
			printf("CREATED EVENT\n");
			EventNode<Customer, CheckoutLine> Print4(swTime, C, L, CUSTOMER_CHANGES_LINE);
			printEvent(Print4);
		}
		if(abTime<swTime & abTime<chTime) //Customer will Abandon Store
		{
			//Create Abandons_Line Event
			EventQ.make_event(abTime, C, L, CUSTOMER_ABANDONS_LINE);

			//Create a Abandons_Line Event and Print It
			EventNode<Customer, CheckoutLine> Print5(abTime, C, L, CUSTOMER_ABANDONS_LINE);
			printf("CREATED EVENT\n");
			printEvent(Print5);
		}
	}
	//==================================================
	else if(E.get_type() == CUSTOMER_CHECKOUT_FINISH)
	{
		// TODO Calculate Statistics about Customer

		//Pull Customer Pointer from Event
		Customer *C = E.get_obj1();
		//Pull CheckoutLine Pointer from Event
		CheckoutLine *L = E.get_obj2();

		//Update CheckoutLine Variables
		L->decNumCustomers(*C);
		L->updateWaitTime(-1 * calcCashierTime(C->getNumItems()));
		L->updateNumItems(-1 * C->getNumItems());

		//Remove Customer from Global Shopping Vector
		removeCustomer(C->getId());

		//Free Memory Allocated to Customer ?
	}
	//==================================================
	else if(E.get_type() == CUSTOMER_CHANGES_LINE)
	{
		//Pull Customer Pointer from Event
		Customer *C = E.get_obj1();
		//Pull CheckoutLine Pointer from Event
		CheckoutLine *oldL = E.get_obj2();
		//Decide which CheckoutLine the Customer should Change To
		CheckoutLine *newL = chooseLine();

		//Update CheckoutLine Variables for Line that Customer is Leaving
		oldL->decNumCustomers(*C);
		oldL->updateNumItems(-1 * C->getNumItems());
		//Update CheckoutLine Variables for Line that Customer is Joining
		newL->incNumCustomers(*C);
		newL->updateNumItems(C->getNumItems());

		//Customer Has 3 Options: Stay In Line, Change Lines, Abandon Store
		int chTime = newL->getWaitTime(); //Time Customer would Start Checkout
		int swTime = C->getOppFactor() + Time; //Time Customer would Switch Lines
		int abTime = C->getAbandonTime(); //Time Customer would Abandon Store

	  //Create an Event that Corresponds to Lowest of the 3 Times
		if(chTime<=swTime & chTime<=abTime) //Customer will Finish Checkout in Current Line
		{
			//Update WaitTime of CheckoutLine
			newL->updateWaitTime(calcCashierTime(C->getNumItems()));

			//Time that Customer Finishes Checkout Equals...
			//Time Waiting in Line + Time Scanning Items + Current Time
			int FinishTime = chTime + calcCashierTime(C->getNumItems()) + Time;
			//Add Checkout_Finish Event
			EventQ.make_event(FinishTime, C, newL, CUSTOMER_CHECKOUT_FINISH);

			//Create a Checkout_Finish Event and Print It
			printf("CREATED EVENT\n");
			EventNode<Customer, CheckoutLine> Print6(FinishTime, C, newL, CUSTOMER_CHECKOUT_FINISH);
			printEvent(Print6);
		}
		if(swTime<chTime & swTime<=abTime) //Customer will Switch Checkout Lines
		{
			//Add Changes_Line Event
			EventQ.make_event(swTime, C, newL, CUSTOMER_CHANGES_LINE);

			//Create a Changes_Line Event and Print It
			printf("CREATED EVENT\n");
			EventNode<Customer, CheckoutLine> Print7(swTime, C, newL, CUSTOMER_CHANGES_LINE);
			printEvent(Print7);
		}
		if(abTime<swTime & abTime<chTime) //Customer will Abandon Store
		{
			//Create Abandons_Line Event
			EventQ.make_event(abTime, C, newL, CUSTOMER_ABANDONS_LINE);

			//Create a Abandons_Line Event and Print It
			EventNode<Customer, CheckoutLine> Print8(abTime, C, newL, CUSTOMER_ABANDONS_LINE);
			printf("CREATED EVENT\n");
			printEvent(Print8);
		}
	}
	//==================================================
	else if(E.get_type() == CUSTOMER_ABANDONS_LINE)
	{
		//Pull Customer Pointer from Event
		Customer *C = E.get_obj1();
		//Pull CheckoutLine Pointer from Event
		CheckoutLine *L = E.get_obj2();

		//Update CheckoutLine Variables for Line that Customer is Leaving
		L->decNumCustomers(*C);
		L->updateNumItems(-1 * C->getNumItems());

		//Remove Customer from Global Shopping Vector
		removeCustomer(C->getId());

		//Free Memory Allocated to Customer ?
	};
	//==================================================
}
//====================================================================================================

void Store::addCheckoutLine(CheckoutLine *L){
	Lines.push_back(L);
}

CheckoutLine* Store::chooseLine(){
	CheckoutLine *currentLine = Lines.front();

	int i;
	for(i = 0; i < Lines.size(); i++)
	{
		if(Lines[i]->getNumItems() < currentLine->getNumItems())
		{
			currentLine = Lines[i];
		}
	}

	return(currentLine);
}

void Store::printLines()
{
	int i;
	for(i = 0; i < Lines.size(); i++)
	{
		printf("(Line %2d)     Wait: %3d     Cust: %3d     Item: %3d\n",
		Lines[i]->getID(),Lines[i]->getWaitTime(),Lines[i]->getNumCustomers(),Lines[i]->getNumItems());
	}
}

void Store::printCusts()
{
	int i;
	for(i = 0; i < Shopping.size(); i++)
	{
		printf("(Cust %2d)     Item: %3d     OppF: %3d     ImpF: %3d\n",
		Shopping[i].getId(),Shopping[i].getNumItems(),Shopping[i].getOppFactor(),Shopping[i].getImpFactor());
	}
}

void Store::removeCustomer(int ID)
{
	int i;
	for(i = 0; i < Shopping.size(); i++)
	{
		if(Shopping[i].getId() == ID)
		{
			Shopping.erase(Shopping.begin()+i);
			break;
		}
	}
}

int Store::getTime() const{
	return Time;
}

void Store::incTime(){
	Time = Time+1;
}

void Store::setTime(int t){
	Time = t;
}

int Store::calcShoppingTime(int numItems){
	//TODO
	return(numItems);
}

int Store::calcCashierTime(int numItems){
	//TODO
	return(numItems);
}

double Store::genRandExp(double beta) const{
  double u, x;
  u = drand48();
  x = -beta * log(1.0 - u); // this is the natural log
  return(x);
}

void Store::printQ()
{
	EventNode<Customer, CheckoutLine> E;
	while(!EventQ.is_empty())
	{
		//===================================
		E = EventQ.pop();
		printEvent(E);
	}
}

void Store::printEvent(EventNode<Customer, CheckoutLine> E)
{
	//===================================
	printf("< %3lu  ", E.get_time());
	//===================================
	if(E.get_obj1()==NULL){
		printf("NULL  ");
	}
	else{
		printf("C%-3d  ",E.get_obj1()->getId());
	}
	//===================================
	if(E.get_obj2()==NULL){
		printf("NULL  ");
	}
	else{
		printf("L%-3d  ",E.get_obj2()->getID());
	}
	//===================================
	switch(E.get_type())
	{
		case 0: printf("CUSTOMER_ARRIVES >");
			break;

		case 1: printf("CUSTOMER_CHECKOUT_READY >");
			break;

		case 2: printf("CUSTOMER_CHECKOUT_FINISH >");
			break;

		case 3: printf("CUSTOMER_CHANGES_LINE >");
			break;

		case 4: printf("CUSTOMER_ABANDONS_LINE >");
			break;

		case 5: printf("VOID_EVENT >");
			break;
	}
	//===================================
	printf("\n\n");
}

int Store::arrivalSeed = 10;
unsigned long int Store::Time = 0;

//no-arg Store constructor
Store::Store(){
	Time = 0;

}//end store default constructor

//Store destructor
//TODO
Store::~Store(){

}//end store default destructor
