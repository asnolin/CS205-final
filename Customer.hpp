#ifndef CS205_FINAL_CUSTOMER_H
#define CS205_FINAL_CUSTOMER_H

class Customer{
  private:
    int id;
    int numItems;
    int checkoutLength;
    int impFactor;
    int oppFactor;
    int inStoreTime;
    int inLineTime;
    int abandonTime;

    static int idSeed;

    // Mean Number of Items Shoppers will Have, Used in genRandExp
    static const int meanNumItems = 20;

    static const int meanOppFactor = 10; //20
    static const int meanImpFactor = 20; //50

    double genRandExp(double beta) const;

  public:
    int getId() const;
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
;
    Customer(int arriveTime);
};

#endif /* LIBRARY_FILENAME_H */
