#include<iostream>
using namespace std;
typedef struct{
	int x;
	int y;
}Tester;

int main(int argc, char *argv[]){
	Tester tester;
	tester.x = 5;
	tester.y = 4;
	cout << tester.x <<endl;
	Tester *ptr = &tester;
	cout << ptr->x << endl;
	new(ptr) Tester();
	cout << ptr->x << endl;
	Tester *ptr2 = new Tester();
	ptr2->x = 5;
	cout << ptr2->x <<endl;
	return 0;
}
