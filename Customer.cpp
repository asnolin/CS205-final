//
// Written by Andrew Borg
//

#include "Customer.hpp"

#include <stdlib.h>
#include <math.h>

int Customer::getID() const
{
  return id;
}

int Customer::getNumItems() const
{
  return numItems;
}

int Customer::getImpFactor() const
{
  return impFactor;
}

int Customer::getOppFactor() const
{
  return oppFactor;
}

int Customer::getInStoreTime() const
{
  return inStoreTime;
}

int Customer::getInLineTime() const
{
  return inLineTime;
}

int Customer::getAbandonTime() const
{
  return abandonTime;
}

void Customer::setInLineTime(int t)
{
  inLineTime = t;
}

void Customer::setAbandonTime(int t)
{
  abandonTime = impFactor + t;
}

int Customer::getCheckoutLength() const
{
  return checkoutLength;
}

void Customer::setCheckoutLength(int t)
{
  checkoutLength = t;
}

double Customer::genRandExp(double beta) const
{
  double u, x;
  u = drand48();
  x = -beta * log(1.0 - u); // this is the natural log
  return(x);
}

int Customer::idSeed = 1;

Customer::Customer(int arriveTime)
{
  id = idSeed;
  idSeed++;

  numItems = genRandExp(meanNumItems)+1;
  oppFactor = genRandExp(meanOppFactor)+numItems+1;
  impFactor = genRandExp(meanImpFactor)+1+numItems+1;

  inStoreTime = arriveTime;
}
