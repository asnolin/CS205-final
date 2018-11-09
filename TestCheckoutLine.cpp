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

    cout << Line1.getID() << endl;
    cout << Line2.getID() << endl;
    cout << Line3.getID() << endl;
    cout << Line4.getID() << endl;
    Line1.incNumCustomers();
    Line2.incNumCustomers();
    Line2.incNumCustomers();
    Line2.decNumCustomers();
    Line3.updateNumItems(3);
    Line4.updateWaitTime(20);

    //should be 1
    cout <<Line1.getNumCustomers()<<endl;
    //should be 1
    cout << Line2.getNumCustomers()<<endl;
    //should be 3
    cout <<Line3.getNumItems()<<endl;
    //should be 20
    cout <<Line4.getWaitTime()<<endl;

};