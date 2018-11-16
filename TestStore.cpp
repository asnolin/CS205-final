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

  
}
