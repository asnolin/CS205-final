class Customer{
  public:
    int id;
    int items;
    int imp;
    int opp;
    int inStore;
    int inLine;

    static int idSeed = 1;

    // Mean Number of Items Shoppers will Have, Used in genRandExp
    static int meanNumItems = 0;

    int getId();
    int getItems();
    int getImp();
    int getOpp();
    int getInStore();
    int getInLine();

    double genRandExp(double beta);

    Customer();

    ~Customer();

}
