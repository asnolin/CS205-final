//
// Written by William Slocum and Andrew Borg
//

#ifndef CS205_FINAL_CUSTOMER_H
#define CS205_FINAL_CUSTOMER_H

class Customer
{
  private:
    int id;
    int numItems;
    //How Long it Takes a Customer to Check Out (Scan Items With Cashier)
    int checkoutLength;
    //Impatience Factor is Length of Time Customer Will Wait in Store Before Leaving It
    int impFactor;
    //Opprotunism Factor is Length of Time Customer Will Wait in Line Before Changing Lines
    int oppFactor;
    //Time Customer Arrives In Store
    int inStoreTime;
    //Time Customer Enters a Checkout Line
    int inLineTime;
    //Absolute Time that a Customer Will Leave the Store
    int abandonTime;
    static int idSeed;

    // Mean Number of Items Shoppers will Have, Used in genRandExp
    static const int meanNumItems = 20;
    // Mean Opprotunism Factor, Used in genRandExp
    static const int meanOppFactor = 10;
    // Mean Impatience Factor, Used in genRandExp
    static const int meanImpFactor = 20;

    double genRandExp(double beta) const;

  public:
    int getID() const;
    int getNumItems() const;

    int getImpFactor() const;
    int getOppFactor() const;

    int getInStoreTime() const;

    int getAbandonTime() const;
    void setAbandonTime(int t);

    int getInLineTime() const;
    void setInLineTime(int t);

    int getCheckoutLength() const;
    void setCheckoutLength(int t);

    Customer(int arriveTime);
};

#endif /* LIBRARY_FILENAME_H */
