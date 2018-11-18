#include "Customer.hpp"
#include <iostream>
#include <time.h>

int main()
{
    srand48((long) time(NULL));

    Customer Cust1(1);
    Customer Cust2(2);
    Customer Cust3(3);
    Customer Cust4(4);
    Customer Cust5(5);

    printf("Cust1 should have an ID of 1 - Customer ID is: %d\n",Cust1.getId());
    printf("Cust2 should have an ID of 2 - Customer ID is: %d\n",Cust2.getId());
    printf("Cust3 should have an ID of 3 - Customer ID is: %d\n",Cust3.getId());
    printf("Cust4 should have an ID of 4 - Customer ID is: %d\n",Cust4.getId());
    printf("Cust5 should have an ID of 5 - Customer ID is: %d\n",Cust5.getId());
    printf("\n");
    printf("Cust1 should have an inStoreTime of 1 - Customer inStoreTime is: %d\n",Cust1.getInStoreTime());
    printf("Cust2 should have an inStoreTime of 1 - Customer inStoreTime is: %d\n",Cust2.getInStoreTime());
    printf("Cust3 should have an inStoreTime of 1 - Customer inStoreTime is: %d\n",Cust3.getInStoreTime());
    printf("Cust4 should have an inStoreTime of 1 - Customer inStoreTime is: %d\n",Cust4.getInStoreTime());
    printf("Cust5 should have an inStoreTime of 1 - Customer inStoreTime is: %d\n",Cust5.getInStoreTime());
    printf("\n");
    printf("%s\n","The following are the number of items in customer's carts - based on the (static) meanNumItems, calculated with genRandExp:" );
    printf("Cust1 items - %d\n",Cust1.getNumItems());
    printf("Cust2 items - %d\n",Cust2.getNumItems());
    printf("Cust3 items - %d\n",Cust3.getNumItems());
    printf("Cust4 items - %d\n",Cust4.getNumItems());
    printf("Cust5 items - %d\n",Cust5.getNumItems());
    printf("\n");
    printf("%s\n","The following are the impatience factors of the customers - based on the (static) meanImpFactor, calculated with genRandExp:" );
    printf("Cust1 impFactor - %d\n",Cust1.getImpFactor());
    printf("Cust2 impFactor - %d\n",Cust2.getImpFactor());
    printf("Cust3 impFactor - %d\n",Cust3.getImpFactor());
    printf("Cust4 impFactor - %d\n",Cust4.getImpFactor());
    printf("Cust5 impFactor - %d\n",Cust5.getImpFactor());
    printf("\n");
    printf("%s\n","The following are the oppurtunism factors of the customers - based on the (static) meanOppFactor, calculated with genRandExp:" );
    printf("Cust1 oppFactor - %d\n",Cust1.getOppFactor());
    printf("Cust2 oppFactor - %d\n",Cust2.getOppFactor());
    printf("Cust3 oppFactor - %d\n",Cust3.getOppFactor());
    printf("Cust4 oppFactor - %d\n",Cust4.getOppFactor());
    printf("Cust5 oppFactor - %d\n",Cust5.getOppFactor());
    printf("\n");
}
