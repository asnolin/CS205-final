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
	//Get Event Type
	EventType T = E.get_type();

	printf("========================= %lu =========================\n", Time);
	printLines();
	printCusts();
	printf("\nPROCESSING EVENT\n");
	printEvent(E);
	printf("\n");
	//==================================================
	if(T == CUSTOMER_ARRIVES)
	{
		//Create New Customer Object
		Customer *aCustomer = new Customer(Time);

		Shopping.push_back(*aCustomer);

		//Calculate How Long the Customer Will Shop
		int shopTime = calcCashierTime(aCustomer->getNumItems());

		EventNode<Customer, CheckoutLine> Print1(Time+shopTime, aCustomer, NULL, CUSTOMER_CHECKOUT_READY);
		printf("CREATED EVENT\n");
		printEvent(Print1);
		printf("\n");
		//Add CHECKOUT_READY Event For New Customer
		EventQ.make_event(Time+shopTime, aCustomer, NULL, CUSTOMER_CHECKOUT_READY);

		//Calculate When Next Customer Arrives
		int nextArriveTime = Time + genRandExp(arrivalSeed);


		EventNode<Customer, CheckoutLine> Print2(nextArriveTime, NULL, NULL, CUSTOMER_ARRIVES);
		printf("CREATED EVENT\n");
		printEvent(Print2);
		printf("\n");
		//Add CUSTOMER_ARRIVES Event to Event Queue
		EventQ.make_event(nextArriveTime, NULL, NULL, CUSTOMER_ARRIVES);
		//Event newEvent2(nextArriveTime, CUSTOMER_ARRIVES, NULL, NULL);
		//EventQ.push(newEvent2);
	}
	//==================================================
	else if(T == CUSTOMER_CHECKOUT_READY)
	{
		Customer *C = E.get_obj1();
		CheckoutLine *L = chooseLine();

		//Determine Absolute Time that Customer will Abandon Store
		C->setAbandonTime(Time);

		//Calculate the Times for the Customer's 3 Options
		int chTime = L->getWaitTime();
		int swTime = C->getOppFactor() + Time;
		int abTime = C->getAbandonTime();

	  //Create Event Based on Shortest of the Times
		if(chTime<=swTime & chTime<=abTime)
		{
			int csTime = calcCashierTime(C->getNumItems());

			//Update Line Variables
			L->incNumCustomers(*C);
			L->updateNumItems(C->getNumItems());
			L->updateWaitTime(csTime);

			int FinishTime = chTime + csTime + Time;
			EventNode<Customer, CheckoutLine> Print3(FinishTime, C, L, CUSTOMER_CHECKOUT_FINISH);
			printf("CREATED EVENT\n");
			printEvent(Print3);
			printf("\n");

			EventQ.make_event(FinishTime, C, L, CUSTOMER_CHECKOUT_FINISH);
		}

		if(swTime<chTime & swTime<=abTime)
		{
			L->incNumCustomers(*C);
			L->updateNumItems(C->getNumItems());

			EventNode<Customer, CheckoutLine> Print4(swTime, C, L, CUSTOMER_CHANGES_LINE);
			printf("CREATED EVENT\n");
			printEvent(Print4);
			printf("\n");

			EventQ.make_event(swTime, C, L, CUSTOMER_CHANGES_LINE);
		}

		if(abTime<swTime & abTime<chTime)
		{
			L->incNumCustomers(*C);
			L->updateNumItems(C->getNumItems());

			EventNode<Customer, CheckoutLine> Print5(abTime, C, L, CUSTOMER_ABANDONS_LINE);
			printf("CREATED EVENT\n");
			printEvent(Print5);
			printf("\n");

			EventQ.make_event(abTime, C, L, CUSTOMER_ABANDONS_LINE);
		}
	}
	//==================================================
	else if(T == CUSTOMER_CHECKOUT_FINISH)
	{
		// TODO Calculate Statistics about Customer
		Customer *C = E.get_obj1();
		CheckoutLine *L = E.get_obj2();

		L->decNumCustomers(*C);
		L->updateWaitTime(-1 * calcCashierTime(C->getNumItems()));
		L->updateNumItems(-1 * C->getNumItems());

		removeCustomer(C->getId());
		//Free Memory Allocated to Customer ?
	}
	//==================================================
	else if(T == CUSTOMER_CHANGES_LINE)
	{
		Customer *C = E.get_obj1();
		CheckoutLine *oldL = E.get_obj2();
		CheckoutLine *newL = chooseLine();

		oldL->decNumCustomers(*C);
		oldL->updateNumItems(-1 * C->getNumItems());

		int chTime = newL->getWaitTime();
		int swTime = C->getOppFactor() + Time;
		int abTime = C->getAbandonTime();

		//Create Event Based on Shortest of the Times
		if(chTime<=swTime & chTime<=abTime)
		{
			int csTime = calcCashierTime(C->getNumItems());

			//Update Line Variables
			newL->incNumCustomers(*C);
			newL->updateNumItems(C->getNumItems());
			newL->updateWaitTime(csTime);

			int FinishTime = chTime + csTime;

			EventNode<Customer, CheckoutLine> Print6(FinishTime, C, newL, CUSTOMER_CHECKOUT_FINISH);
			printf("CREATED EVENT\n");
			printEvent(Print6);
			printf("\n");

			EventQ.make_event(FinishTime, C, newL, CUSTOMER_CHECKOUT_FINISH);
		}
		if(swTime<chTime & swTime<=abTime)
		{
			newL->incNumCustomers(*C);
			newL->updateNumItems(C->getNumItems());

			EventNode<Customer, CheckoutLine> Print7(swTime, C, newL, CUSTOMER_CHANGES_LINE);
			printf("CREATED EVENT\n");
			printEvent(Print7);
			printf("\n");

			EventQ.make_event(swTime, C, newL, CUSTOMER_CHANGES_LINE);
		}
		if(abTime<swTime & abTime<chTime)
		{
			newL->incNumCustomers(*C);
			newL->updateNumItems(C->getNumItems());

			EventNode<Customer, CheckoutLine> Print8(abTime, C, newL, CUSTOMER_ABANDONS_LINE);
			printf("CREATED EVENT\n");
			printEvent(Print8);
			printf("\n");

			EventQ.make_event(abTime, C, newL, CUSTOMER_ABANDONS_LINE);
		}

	}
	//==================================================
	else if(T == CUSTOMER_ABANDONS_LINE)
	{
		Customer *C = E.get_obj1();
		CheckoutLine *L = E.get_obj2();

		L->decNumCustomers(*C);
		L->updateNumItems(-1 * C->getNumItems());

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
	printf("< %lu  ", E.get_time());
	//===================================
	if(E.get_obj1()==NULL){
		printf("NULL ");
	}
	else{
		printf("%d  ",E.get_obj1()->getId());
	}
	//===================================
	if(E.get_obj2()==NULL){
		printf("NULL ");
	}
	else{
		printf("%d  ",E.get_obj2()->getID());
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
	printf("\n");
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
