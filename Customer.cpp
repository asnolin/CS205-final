#include "Customer.hpp"

int getId(){
  return id;
}

int getNumItems(){
  return items;
}

int getImpFactor(){
  return imp;
}

int getOppFactor(){
  return opp;
}

int getInStoreTime(){
  return inStore;
}

int getInLineTime(){
  return inLine;
}

void setInLineTime(int t){
  inLineTime = t;
}

double genRandExp(double beta) {
  double u, x;
  u = drand48();
  x = -beta * log(1.0 - u); // this is the natural log
  return(x);
}

Customer(int arriveTime){
  id = idSeed;
  idSeed++;

  items = genRandExp(meanNumItems);
  opp = genRandExp(meanOppFactr);
  imp = genRandExp(meanImpFactr);

  inStore = arriveTime;

}

~Customer(){
  //TODO
}
