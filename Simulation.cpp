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

  theStore.EventQ.make_event(0, NULL, 0, NULL, 0, CUSTOMER_ARRIVES);

  EventNode<Customer,CheckoutLine> E;
  E = theStore.EventQ.pop();

  while(theStore.getTime() < 100)
  {
    theStore.setTime(E.get_time());
    theStore.handleEvent(E);
    E = theStore.EventQ.pop();
  }
  
  printf("====================================\n");
  printf("\n");
  printf("\n");
}
