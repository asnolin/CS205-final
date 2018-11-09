//
// Created by Ylee on 11/9/2018.
//

#include "CheckoutLine.h"
#include <stdlib.h>
CheckoutLine::CheckoutLine(int ID);

int CheckoutLine::idSeed = 1;
int CheckoutLine::CheckoutLine(){
    ID = idSeed;
    idSeed++;
    WaitTime = 0;
};

int CheckoutLine::getID() const{
    return ID;
}
int CheckoutLine::getNumCustomers() const{
    return NumCustomers;
};
int CheckoutLine::getNumItems() const{
    return NumItems
};
int CheckoutLine::getWaitTime() const{
    return WaitTime;
};
void CheckoutLine::setID(int inputID){
    ID = inputID;
};
void CheckoutLine::incNumCustomers(){
    NumCustomers += 1;
};
void CheckoutLine::decNumCustomers(){
    NumCustomers -= 1;
};
void CheckoutLine::updateNumItems(int n){
    NumItems = n;
};
void CheckoutLine::updateWaitTime(int n){
    WaitTime = n;
};
