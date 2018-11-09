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

    printf("%d\n",Cust1.getId());
    printf("%d\n",Cust2.getId());
    printf("%d\n",Cust3.getId());
    printf("%d\n",Cust4.getId());
    printf("%d\n",Cust5.getId());
    printf("\n");
    printf("%d\n",Cust1.getNumItems());
    printf("%d\n",Cust2.getNumItems());
    printf("%d\n",Cust3.getNumItems());
    printf("%d\n",Cust4.getNumItems());
    printf("%d\n",Cust5.getNumItems());
    printf("\n");
}
