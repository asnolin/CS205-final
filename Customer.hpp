class Customer{
  private:
    int id;
    int numItems;
    int impFactor;
    int oppFactor;
    int inStoreTime;
    int inLineTime;
    int abandonTime;

    static int idSeed;

    // Mean Number of Items Shoppers will Have, Used in genRandExp
    static const int meanNumItems = 10;

    static const int meanOppFactor = 1;
    static const int meanImpFactor = 1;

    double genRandExp(double beta) const;

  public:
    int getId() const;
    int getNumItems() const;

    int getImpFactor() const;
    int getOppFactor() const;

    int getInStoreTime() const;
    int getInLineTime() const;

    int getAbandonTime() const;
    void setAbandonTime(int t);

    void setInLineTime(int t);

    Customer(int arriveTime);
};
