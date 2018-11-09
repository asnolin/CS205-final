#include "Customer.hpp"
#include <iostream>

int main()
{
    Customer Cust1(1);
    wait((int *)10000);
    Customer Cust2(2);
    Customer Cust3(3);
    Customer Cust4(4);
    Customer Cust5(5);

    std::cout << "\n";
    std::cout << Cust1.getId();
    std::cout << "\n";
    std::cout << Cust2.getId();
    std::cout << "\n";
    std::cout << Cust3.getId();
    std::cout << "\n";
    std::cout << Cust4.getId();
    std::cout << "\n";
    std::cout << Cust5.getId();
    std::cout << "\n";

    std::cout << "\n";
    std::cout << Cust1.getNumItems();
    std::cout << "\n";
    std::cout << Cust2.getNumItems();
    std::cout << "\n";
    std::cout << Cust3.getNumItems();
    std::cout << "\n";
    std::cout << Cust4.getNumItems();
    std::cout << "\n";
    std::cout << Cust5.getNumItems();
    std::cout << "\n";

    std::cout << "\n";
}
