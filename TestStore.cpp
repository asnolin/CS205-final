#include "Store.hpp"

int main()
{
  srand48((long) time(NULL));

  Store theStore;

  CheckoutLine L1;
  CheckoutLine L2;
  CheckoutLine L3;
  theStore.addCheckoutLine(&L1);
  theStore.addCheckoutLine(&L2);
  theStore.addCheckoutLine(&L3);

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

  printf("\n");
  /*
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

  printf("\n");
  */
}
