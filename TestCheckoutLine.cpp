//
// Created by Ylee on 11/9/2018.
//
#include "CheckoutLine.h"
#include<iostream>
using namespace std;
int main() {
    CheckoutLine Line1;
    CheckoutLine Line2;
    CheckoutLine Line3;
    CheckoutLine Line4;
    Customer c1(1);
    Customer c2(2);
    Customer c3(2);
    Customer c4(4);
    cout << "Testing getID()" << endl;
    cout << "---------------" << endl;
    cout << "CheckoutLine Id Should Be 1: " << Line1.getID() << endl;
    cout << "CheckoutLine Id Should Be 2: " << Line2.getID() << endl;
    cout << "CheckoutLine Id Should Be 3: " << Line3.getID() << endl;
    cout << "CheckoutLine Id Should Be 4: " << Line4.getID() << endl << endl;

    cout << "Testing incNumCustomers() and decNumCustomers()" << endl;
    cout << "---------------" << endl;
    cout << "//Line1.incNumCustomers(c1)" << endl;
    cout << "//Line1.incNumCustomers(c2)" << endl;
    cout << "//Line2.incNumCustomers(c3)" << endl;
    cout << "//Line3.incNumCustomers(c4)" << endl;
    cout << "//Line3.decNumCustomers(c4)" << endl;

    Line1.incNumCustomers(c1);
    Line1.incNumCustomers(c2);
    Line2.incNumCustomers(c3);
    Line3.incNumCustomers(c4);
    Line3.decNumCustomers(c4);

    cout <<"CheckoutLine 1 Number Customers Should be 2: " << Line1.getNumCustomers() << endl;
    cout <<"CheckoutLine 2 Number Customers Should be 1: " << Line2.getNumCustomers() << endl;
    cout <<"CheckoutLine 3 Number Customers Should be 0: " << Line3.getNumCustomers() << endl << endl;


    cout << "Testing incNumCustomers() and decNumCustomers()" << endl;
    cout << "---------------" << endl;
    cout << "//Line1.updateNumItems(20)" << endl;
    cout << "//Line2.updateWaitTime(15)" << endl;
    Line1.updateNumItems(20);
    Line2.updateWaitTime(15);
    cout << "CheckoutLine 1 NumItems Should be 20: " << Line1.getNumItems() << endl;
    cout << "CheckoutLine 2 WaitTime Should be 15: " << Line2.getWaitTime() << endl << endl;
};
