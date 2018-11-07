class Customer{
  public:
    int id;
    int items;
    int imp;
    int opp;
    int inStore;
    int inLine;

    static int idSeed = 1;

    int getId();
    int getItems();
    int getImp();
    int getOpp();
    int getInStore();
    int getInLine();

    Customer();

    ~Customer();

}
