#include"Event.hpp"

//#define BOOST_TEST_MODULE EventQueue test
//#include<boost/test/unit_test.hpp>

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
		}//end get_data

};//end Data class

class Stuff{
	private:
		int thing;
	public:
		int get_thing(){
			return thing;
		}//end get_thing
};//end Stuff class

int main(int argc, char* argv[]){
	EventQueue<Data, Stuff> eventQueue;
	cout << "compiled" << endl;
	Data myData = Data();
	Stuff myStuff = Stuff();
	try{
		eventQueue.make_event(1, &myData, &myStuff, VOID_EVENT);
		eventQueue.make_event(0, &myData, &myStuff, VOID_EVENT);
		EventNode<Data, Stuff> poppedData = eventQueue.pop();
		cout << poppedData.get_time() << endl;
		poppedData = eventQueue.pop();
		cout << poppedData.get_time() << endl;
	}//end try block
	catch(const std::runtime_error){
		cout<< "the EventQueue was empty "<<endl;
	}
	return 0;
}
