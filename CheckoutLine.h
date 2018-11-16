//
// Created by Ylee on 11/9/2018.
//

#ifndef CS205_FINAL_CHECKOUTLINE_H
#define CS205_FINAL_CHECKOUTLINE_H

using namespace std;


class CheckoutLine {
private:
    //fields
    int ID;
    int NumCustomers;
    int NumItems;
    int WaitTime;

    static int idSeed;
public:
    CheckoutLine();
    //getter
    int getID() const;
    int getNumCustomers() const;
    int getNumItems() const;
    int getWaitTime() const;

    //setter
    //void setID(int ID);
    //void setNumCustomers(int NumCustomers);
    //void setNumItems(int NumItems);
    //void setWaitTime(int WaitTime);

    void incNumCustomers();
    void decNumCustomers();
    void updateNumItems(int n);
    void updateWaitTime(int n);




};


#endif //CS205_FINAL_CHECKOUTLINE_H
