#include"Event.hpp"
#include<queue>
#include<vector>
#include<iostream>
#include<boost/lambda/lambda.hpp>
#define MAX_SIZE 100

using namespace std;

class Data{
	private:
		int data;
	public:
		int get_data(){
			return data;
		}//end get_data

};//end Data class


int main(int argc, char* argv[]){
	EventQueue<Data> eventQ;
	cout << "compiled" << endl;
	priority_queue<int> intPQ;
	try{
		eventQ.pop();
	}//end try block
	catch(const std::runtime_error){
		cout<< "the EventQueue was empty when "<<endl;
	}
	return 0;
}
