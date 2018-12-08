//
// Written by Yile Li
//

#ifndef CS205_FINAL_CHECKOUTLINE_H
#define CS205_FINAL_CHECKOUTLINE_H

#include <string>
#include <vector>
#include "Customer.hpp"

using namespace std;


class CheckoutLine
{
  private:

      int ID;
      int NumCustomers;
      int NumItems;
      int WaitTime;
      int ItemLimit;

      bool Open = true;;

      static int idSeed;

  public:

      CheckoutLine();

      vector <Customer> customerLine;

      int getID() const;
      int getNumCustomers() const;
      int getNumItems() const;
      int getWaitTime() const;
      int getItemLimit() const;

      bool getStatus() const;
      void togStatus();

      void setItemLimit(int n);

      void incNumCustomers(Customer in);
      void decNumCustomers(Customer out);
      void updateNumItems(int n);
      void updateWaitTime(int n);
      void update();
};


#endif //CS205_FINAL_CHECKOUTLINE_H
