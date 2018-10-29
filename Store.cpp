/*
 * Store.cpp
 */

//include Store header file
#include"Store.hpp"

Store::Store(){
	time = 0;
}//end store default constructor

Store::~Store(){
	lines->clear();
}//end store default destructor

Store::bool makeEvent(unsigned long int inTime, eventType inType, Customer* inCust){
	return true;
}
int main(int argc, char *argv[]){
	return 0;
}//end main
