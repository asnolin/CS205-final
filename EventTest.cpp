#include"Event.hpp"
#include<queue>
#include<vector>
#include<iostream>

#define MAX_SIZE 100

using namespace std;

class Data{
	private:
		int data;
	public:
		int get_data(){
			return data;
		}
};//end Data class


int main(int argc, char* argv[]){
	EventQueue<Data> eventQ;
	cout << "compiled" << endl;
	return 0;
}
