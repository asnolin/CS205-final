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
    cout<<"Should be 1 and we get " <<c1.getId() <<endl;
    cout<<"Should be 2 and we get " <<c2.getId() <<endl;
    cout<<"Should be 3 and we get " <<c3.getId() <<endl;
    cout <<"Should be 1 and we get " << Line1.getID() << endl;
    cout <<"Should be 2 and we get " << Line2.getID() << endl;
    cout << "Should be 3 and we get " <<Line3.getID() << endl;
    cout << "Should be 4 and we get " <<Line4.getID() << endl;
    Line1.incNumCustomers(c1);
    Line2.incNumCustomers(c2);
    Line2.incNumCustomers(c3);
    Line2.decNumCustomers(c2);
    Line3.updateNumItems(3);
    Line4.updateWaitTime(20);

    //should be 1
    cout <<"Should be 1 and we get " <<Line1.getNumCustomers()<<endl;
    //should be 1
    cout << "Should be 1 and we get " <<Line2.getNumCustomers()<<endl;
    //should be 3
    cout <<"Should be 3 and we get " << Line3.getNumItems()<<endl;
    //should be 20
    cout <<"Should be 20 and we get " << Line4.getWaitTime()<<endl;
    //
    Line1.update();
    cout<<Line1.getNumItems()<<endl;
    cout<<Line1.getWaitTime()<<endl;

};