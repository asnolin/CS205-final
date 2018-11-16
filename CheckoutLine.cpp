//
// Created by Ylee on 11/9/2018.
//

#include "CheckoutLine.h"
#include <stdlib.h>

int CheckoutLine::idSeed = 1;
CheckoutLine::CheckoutLine(){
    ID = idSeed;
    idSeed++;
    WaitTime = 0;
    NumCustomers = 0;
    NumItems = 0;
};

int CheckoutLine::getID() const{
    return ID;
}
int CheckoutLine::getNumCustomers() const{
    return NumCustomers;
};
int CheckoutLine::getNumItems() const{
    return NumItems;
};
int CheckoutLine::getWaitTime() const{
    return WaitTime;
};

void CheckoutLine::incNumCustomers(){
    NumCustomers++;
};
void CheckoutLine::decNumCustomers(){
    NumCustomers--;
};
void CheckoutLine::updateNumItems(int n){
    NumItems = n + NumItems;
};
void CheckoutLine::updateWaitTime(int n){
    WaitTime = n + WaitTime;
};
