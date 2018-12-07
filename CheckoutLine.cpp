//
// Created by Ylee on 11/9/2018.
//

#include "CheckoutLine.h"
#include <stdlib.h>
#include<limits>

int CheckoutLine::idSeed = 1;
CheckoutLine::CheckoutLine(){
    ID = idSeed;
    idSeed++;
    WaitTime = 0;
    NumCustomers = 0;
    NumItems = 0;
    ItemLimit =std::numeric_limits<int>::max();
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

int CheckoutLine::getItemLimit() const{
    return ItemLimit;
}

void CheckoutLine::setItemLimit(int n){
    ItemLimit = n;
}

void CheckoutLine::incNumCustomers(Customer in){
    NumCustomers++;
    customerLine.push_back(in);
};
void CheckoutLine::decNumCustomers(Customer out){
    NumCustomers--;
    for (int i = 0; i<customerLine.size(); i++){
        if (customerLine[i].getId() == out.getId()){
            customerLine.erase(customerLine.begin()+ i);
        }
    }
};
void CheckoutLine::updateNumItems(int n){
    NumItems = NumItems + n;
};
void CheckoutLine::updateWaitTime(int n){
    WaitTime = WaitTime + n;
};

bool CheckoutLine::getStatus() const
{
  return Open;
}

void CheckoutLine::togStatus()
{
  if(Open){
    Open = false;
  }
  else{
    Open = true;
  }
}

void CheckoutLine::update() {
    NumItems = 0;
    NumCustomers = 0;
    WaitTime = 0;
    for(int i=0; i<customerLine.size();i++){
        NumCustomers ++;
        NumItems += customerLine[i].getNumItems();
        //undecide just set 5 to test
        WaitTime += customerLine[i].getNumItems() * 5;
    }
};
