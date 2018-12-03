#include "Store.hpp"

int main()
{
  srand48((long) time(NULL));

  Store theStore;
  theStore.setTime(0);

  int i;
  for(i = 0; i < 3; i++)
  {
    CheckoutLine *L = new CheckoutLine();
    theStore.addCheckoutLine(L);
  }

  EventNode<Customer,CheckoutLine> E;

  theStore.EventQ.make_event(0, NULL, 0, NULL, 0, CUSTOMER_ARRIVES);

  theStore.setTime(E.get_time());
  E = theStore.EventQ.pop();
  while(theStore.getTime() < 100)
  {
    theStore.setTime(E.get_time());
    theStore.handleEvent(E);
    E = theStore.EventQ.pop();
  }
  printf("====================================\n");
  printf("\n");

  /*
  //==============================================
  //TESTING CUSTOMER FINISHES CHECKOUT
  //==============================================
  printf("\nTESTING: Customer Finishes Checkout\n");
  printf("----------------------------------------\n");
  Customer C1(0);

  printf("Customer %d | Items %d | Opp %d | Imp %d\n", C1.getId(), C1.getNumItems(), C1.getOppFactor(), C1.getImpFactor());
  printf("\n");
  printf("Line 1 Customers %d | Line 1 Items %d | Line 1 Wait Time: %d\n", L1.getNumCustomers(), L1.getNumItems(),L1.getWaitTime());
  printf("\n");

  theStore.EventQ.make_event(0, &C1, &L1, CUSTOMER_CHECKOUT_FINISH);

  printf("*Customer Abandons Line 1*\n\n");
  theStore.handleEvent(theStore.EventQ.pop());

  printf("Line 1 Customers %d | Line 1 Items %d | Line 1 Wait Time: %d\n", L1.getNumCustomers(), L1.getNumItems(),L1.getWaitTime());
  printf("\n");
  theStore.printQ();
  */

  /*
  //==============================================
  //TESTING CUSTOMER ABANDONS LINE
  //==============================================
  printf("\nTESTING: Customer Abadons Line\n");
  printf("----------------------------------------\n");
  Customer C1(0);

  printf("Customer %d | Items %d | Opp %d | Imp %d\n", C1.getId(), C1.getNumItems(), C1.getOppFactor(), C1.getImpFactor());
  printf("\n");
  printf("Line 1 Customers %d | Line 1 Items %d | Line 1 Wait Time: %d\n", L1.getNumCustomers(), L1.getNumItems(),L1.getWaitTime());
  printf("\n");

  theStore.EventQ.make_event(0, &C1, &L1, CUSTOMER_ABANDONS_LINE);

  printf("*Customer Abandons Line 1*\n\n");
  theStore.handleEvent(theStore.EventQ.pop());

  printf("Line 1 Customers %d | Line 1 Items %d | Line 1 Wait Time: %d\n", L1.getNumCustomers(), L1.getNumItems(),L1.getWaitTime());
  printf("\n");
  theStore.printQ();
  */

  /*
  //==============================================
  //TESTING CUSTOMER CHANGES Line
  //==============================================
  printf("\nTESTING: Customer Changes Line\n");
  printf("----------------------------------------\n");
  Customer C1(0);
  C1.setAbandonTime(0);

  printf("Customer %d | Items %d | Opp %d | Imp %d\n", C1.getId(), C1.getNumItems(), C1.getOppFactor(), C1.getImpFactor());
  printf("\n");
  printf("Line 1 Customers %d | Line 1 Items %d | Line 1 Wait Time: %d\n", L1.getNumCustomers(), L1.getNumItems(),L1.getWaitTime());
  printf("Line 2 Customers %d | Line 2 Items %d | Line 2 Wait Time: %d\n", L2.getNumCustomers(), L2.getNumItems(),L2.getWaitTime());
  printf("\n");

  theStore.EventQ.make_event(0, &C1, &L1, CUSTOMER_CHANGES_LINE);

  printf("*Customer Changes From Line 1 to Line 2*\n\n");
  theStore.handleEvent(theStore.EventQ.pop());

  printf("Line 1 Customers %d | Line 1 Items %d | Line 1 Wait Time: %d\n", L1.getNumCustomers(), L1.getNumItems(),L1.getWaitTime());
  printf("Line 2 Customers %d | Line 2 Items %d | Line 2 Wait Time: %d\n", L2.getNumCustomers(), L2.getNumItems(),L2.getWaitTime());
  printf("\n");
  theStore.printQ();
  */

  /*
  //==============================================
  // TESTING CUSTOMER READY FOR CHECKOUT
  //==============================================
  Customer C1(0);
  Customer C2(0);
  printf("\nTESTING: Customers Ready For Checkout\n");
  printf("----------------------------------------\n");
  printf("Customer %d | Items %d | Opp %d | Imp %d\n", C1.getId(), C1.getNumItems(), C1.getOppFactor(), C1.getImpFactor());
  printf("Customer %d | Items %d | Opp %d | Imp %d\n", C2.getId(), C2.getNumItems(), C2.getOppFactor(), C2.getImpFactor());
  printf("\n");
  theStore.setTime(0);

  theStore.EventQ.make_event(0, &C1, NULL, CUSTOMER_CHECKOUT_READY);
  theStore.EventQ.make_event(0, &C2, NULL, CUSTOMER_CHECKOUT_READY);

  printf("Line 1 Wait Time: %d\n", L1.getWaitTime());
  theStore.handleEvent(theStore.EventQ.pop());
  printf("*Customer 1 Joins Line 1 at Time 0*\n");
  printf("Line 1 Wait Time: %d\n", L1.getWaitTime());
  theStore.handleEvent(theStore.EventQ.pop());
  printf("*Customer 2 Joins Line 1 at Time 0*\n");
  printf("\n");

  printf("Resulting Event Queue\n");
  theStore.printQ();
  */

  /*
  //==============================================
  // TESTING CUSTOMER ARRIVES
  //==============================================
  printf("\n");
  printf("TESTING: Manually Adding Events to Event Queue\n");
  printf("----------------------------------------------\n");

  printf("//theStore.EventQ.make_event(5, NULL, NULL, CUSTOMER_ARRIVES);\n");
  theStore.EventQ.make_event(5, NULL, NULL, CUSTOMER_ARRIVES);

  printf("//theStore.EventQ.make_event(10, NULL, NULL, CUSTOMER_ARRIVES);\n");
  theStore.EventQ.make_event(10, NULL, NULL, CUSTOMER_ARRIVES);

  theStore.setTime(5);

  printf("//theStore.handleEvent(theStore.EventQ.pop());\n");
  theStore.handleEvent(theStore.EventQ.pop());

  printf("//theStore.printQ();\n\n");
  theStore.printQ();
  */

  /*
  //==============================================
  // TESTING CHOOSE LINE
  //==============================================
  printf("\nTesting getTime and incTime\n");
  printf("--------------------------------------------------\n");
  int i;
  i = theStore.getTime();
  printf("Should Print 0: %d\n",i);

  theStore.incTime();
  i = theStore.getTime();
  printf("Should Print 1: %d\n",i);

  theStore.incTime();
  i = theStore.getTime();
  printf("Should Print 2: %d\n",i);

  theStore.incTime();
  i = theStore.getTime();
  printf("Should Print 3: %d\n",i);

  printf("\nTesting addCheckoutLine and chooseLine\n");
  printf("--------------------------------------------------\n");
  CheckoutLine L1;
  CheckoutLine L2;
  CheckoutLine L3;
  CheckoutLine L4;

  theStore.addCheckoutLine(&L1);
  theStore.addCheckoutLine(&L2);
  theStore.addCheckoutLine(&L3);
  theStore.addCheckoutLine(&L4);

  L1.updateNumItems(20);
  L2.updateNumItems(10);
  L3.updateNumItems(5);
  L4.updateNumItems(15);

  printf("Line 1 Should Have 20 Items: %d = %d\n",theStore.Lines[0]->getID(),theStore.Lines[0]->getNumItems());
  printf("Line 2 Should Have 10 Items: %d = %d\n",theStore.Lines[1]->getID(),theStore.Lines[1]->getNumItems());
  printf("Line 3 Should Have  5 Items: %d =  %d\n",theStore.Lines[2]->getID(),theStore.Lines[2]->getNumItems());
  printf("Line 4 Should Have 15 Items: %d = %d\n",theStore.Lines[3]->getID(),theStore.Lines[3]->getNumItems());

  CheckoutLine *Shortest;
  Shortest = theStore.chooseLine();
  printf("Shortest Line Should Be Line 3: %d\n", Shortest->getID());
  */

  printf("\n");
}
