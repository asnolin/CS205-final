/*
 * Store.cpp
 */

//include Store header file
#include"Store.hpp"

Store::Store(){
	time = 0;
}//end store default constructor

Store::~Store(){
	for(int i = 0; i < lines.size(); ++i){
		lines[i].clear();
	}
}//end store default destructor

bool Store::makeEvent(unsigned long int inTime, eventType inType, Customer &inCust){
	bool isMade = false;
	
	return isMade;
}
int main(int argc, char *argv[]){
	return 0;
}//end main
