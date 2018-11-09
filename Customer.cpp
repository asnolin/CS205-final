#include "Customer.hpp"
#include <stdlib.h>
#include <math.h>
#include <time.h>


int Customer::getId() const{
  return id;
}

int Customer::getNumItems() const{
  return numItems;
}

int Customer::getImpFactor() const{
  return impFactor;
}

int Customer::getOppFactor() const{
  return oppFactor;
}

int Customer::getInStoreTime() const{
  return inStoreTime;
}

int Customer::getInLineTime() const{
  return inLineTime;
}

void Customer::setInLineTime(int t){
  inLineTime = t;
}

double Customer::genRandExp(double beta) const{
  double u, x;
  u = drand48();
  x = -beta * log(1.0 - u); // this is the natural log
  return(x);
}

int Customer::idSeed = 1;

Customer::Customer(int arriveTime){
  id = idSeed;
  idSeed++;

  srand48((long) time(NULL));
  numItems = genRandExp(meanNumItems);
  oppFactor = genRandExp(meanOppFactor);
  impFactor = genRandExp(meanImpFactor);

  inStoreTime = arriveTime;
}
