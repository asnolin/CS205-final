class Customer{
  private:
    int id;
    int numItems;
    int impFactor;
    int oppFactor;
    int inStoreTime;
    int inLineTime;

    static int idSeed = 1;

    // Mean Number of Items Shoppers will Have, Used in genRandExp
    static int meanNumItems = 0;

    static int meanOppFactor = 0;
    static int meanImpFactor = 0;

    double genRandExp(double beta);

  public:
    int getId();
    int getNumItems();

    int getImpFactor();
    int getOppFactor();

    int getInStoreTime();
    int getInLineTime();

    void setInLineTime(int t);

    Customer();

    ~Customer();

}
