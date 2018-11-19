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

	void set_data(int inData){
		data = inData;
	}//end set_data

};//end Data class

class Stuff{
	private:
	int thing;

	public:
	int get_thing(){
		return thing;
	}//end get_thing

	void set_thing(int inThing){
		thing = inThing;
	}//end set_thing

};//end Stuff class

int main(int argc, char* argv[]){
	EventQueue<Data, Stuff> eventQueue;

	EventNode<Data,Stuff> node1;
	EventNode<Data, Stuff> node2;

	cout << "compiled" << endl;

	Data d1 = Data();
	Data d2 = Data();

	Stuff myStuff = Stuff();

	try{
		cout<<"testing the ordering of the EventQueue"<<endl;
		eventQueue.make_event(1, &d1, &myStuff, VOID_EVENT);
		cout<<"created a node with time = 1" <<endl;
		eventQueue.make_event(0, &d2, &myStuff, VOID_EVENT);
		cout << "created node with time = 0" <<endl;
		node1= eventQueue.pop();
		cout <<"time of first popped item = "<< node1.get_time() << " should be 0" << endl;
		node1 = eventQueue.pop();
		cout << "time of second popped item = " << node1.get_time() << " should be 1" <<endl;

		cout<<"testing ordering of eventNodes with same time field"<<endl;
		d1.set_data(1);
		d2.set_data(2);
		//since the node with &d1 was made first, it should be first
		eventQueue.make_event(2, &d1, &myStuff, VOID_EVENT);
		cout<<"created node with time = 2 and obj1.get_data = 1"<<endl;
		eventQueue.make_event(2, &d2, &myStuff, VOID_EVENT);
		cout<<"created node with time = 2 and obj1.get_data = 2"<<endl;
		node1 = eventQueue.pop();
		cout<<"value of obj1.get_data for the first node  is: " <<node1.get_obj1()->get_data() <<" should be 1" <<endl;
		node2 = eventQueue.pop();
		cout<<"value of obj1.get_data for the second node  is: " <<node2.get_obj1()->get_data() <<" should be 2" <<endl;
		if(node1.get_obj1()->get_data() == 1){
			cout<<"order is preserved when inserting new nodes with the same time"<<endl;
		}else{
			cout<<"order is not preserved for nodes with same time value" <<endl;
		}

		cout<<"trying to add a node with a time that is before the EventQueue's current time"<<endl;
		cout<<"the current time in the EventQueue is: " <<eventQueue.get_current_time() <<endl;
		if(eventQueue.make_event(0, &d1, &myStuff, VOID_EVENT)){
			cout << "eventQueue allows for nodes to have a time < currentTime"<<endl;
		}else{
			cout <<"eventQueue correctly rejected the new node" <<endl;
			cout <<"trying to pop a node from the EventQueue now should result in an error" <<endl;
			node1 = eventQueue.pop();
		}
	}//end try block
	catch(const std::runtime_error){
		cout<< "ERROR EventQueue was empty when pop() was called"<<endl;
	}
	return 0;
}
