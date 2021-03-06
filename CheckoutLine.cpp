//
// Written by Yile Li
//

#include "CheckoutLine.h"
#include <stdlib.h>
#include <limits>

int CheckoutLine::idSeed = 1;

CheckoutLine::CheckoutLine()
{
    ID = idSeed;
    idSeed++;
    WaitTime = 0;
    NumCustomers = 0;
    NumItems = 0;
    //There Is No Item Limit for Non-Express Lanes
    ItemLimit = std::numeric_limits<int>::max();
};

int CheckoutLine::getID() const
{
    return ID;
}

int CheckoutLine::getNumCustomers() const
{
    return NumCustomers;
};

int CheckoutLine::getNumItems() const
{
    return NumItems;
};

int CheckoutLine::getWaitTime() const
{
    return WaitTime;
};

int CheckoutLine::getItemLimit() const
{
    return ItemLimit;
}

void CheckoutLine::setItemLimit(int n)
{
    ItemLimit = n;
}

//Add Customer to Checkout Line Vector
void CheckoutLine::incNumCustomers(Customer in)
{
    NumCustomers++;
    customerLine.push_back(in);
};

//Remove Customer for Checkout Line Vector
void CheckoutLine::decNumCustomers(Customer out)
{
    NumCustomers--;
    for (int i = 0; i<customerLine.size(); i++)
    {
        if (customerLine[i].getID() == out.getID())
        {
            customerLine.erase(customerLine.begin()+ i);
        }
    }
};

void CheckoutLine::updateNumItems(int n)
{
    NumItems = NumItems + n;
};

void CheckoutLine::updateWaitTime(int n)
{
    WaitTime = WaitTime + n;
};

bool CheckoutLine::getStatus() const
{
  return Open;
}

//Toggles Open/Closed Status
void CheckoutLine::togStatus()
{
  if(Open)
  {
    Open = false;
  }
  else
  {
    Open = true;
  }
}

//Not Used
void CheckoutLine::update()
{
    NumItems = 0;
    NumCustomers = 0;
    WaitTime = 0;
    for(int i=0; i<customerLine.size();i++)
    {
        NumCustomers ++;
        NumItems += customerLine[i].getNumItems();
        WaitTime += customerLine[i].getNumItems() * 5;
    }
};
