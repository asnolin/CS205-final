#include "Customer.hpp"

int getId(){
  return id;
}

int getItems(){
  return items;
}

int getImp(){
  return imp;
}

int getOpp(){
  return opp;
}

int getInStore(){
  return inStore;
}

int getInLine(){
  return inLine;
}

double genRandExp(double beta) {
  double u, x;
  u = drand48();
  x = -beta * log(1.0 - u); // this is the natural log
  return(x);
}

Customer(){
  id = idSeed;
  idSeed++;

  items = genRandExp(meanNumItems)

}
