#include "Store.hpp"

int main()
{
  Store theStore;

  printf("\nTesting getTime and incTime\n");
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

  CheckoutLine L1;
  CheckoutLine L2;
  CheckoutLine L3;
  CheckoutLine L4;

  theStore.addCheckoutLine(&L1);
  theStore.addCheckoutLine(&L2);
  theStore.addCheckoutLine(&L3);
  theStore.addCheckoutLine(&L4);

  printf("Line 1: %d\n",theStore.Lines[0]->getID());
  printf("Line 2: %d\n",theStore.Lines[1]->getID());
  printf("Line 3: %d\n",theStore.Lines[2]->getID());
  printf("Line 4: %d\n",theStore.Lines[3]->getID());

  theStore.Lines[0]->updateNumItems(20);
  theStore.Lines[1]->updateNumItems(10);
  theStore.Lines[2]->updateNumItems(5);
  theStore.Lines[3]->updateNumItems(15);

  CheckoutLine *Shortest;
  Shortest = theStore.chooseLine();
  printf("Should Be Line 3: %d\n", Shortest->getID());
}
