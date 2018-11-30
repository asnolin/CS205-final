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
	int id;

	public:
	int get_data(){
		return data;
	}//end get_data

	int get_id(){
		return id;
	}//end get_id

	void set_data(int inData){
		data = inData;
	}//end set_data

	void set_id(int inId){
		id = inId;
	}//end set_id
};//end Data class

class Stuff{
	private:
	int thing;
	int id;
	public:
	int get_thing(){
		return thing;
	}//end get_thing

	int get_id(){
		return id;
	}//end get_id

	void set_thing(int inThing){
		thing = inThing;
	}//end set_thing

	void set_id(int inId){
		id = inId;
	}//end set_id

};//end Stuff class

int main(int argc, char* argv[]){
	EventQueue<Data, Stuff> eventQueue;

	EventNode<Data,Stuff> node1;
	EventNode<Data, Stuff> node2;

	cout << "compiled" << endl;

	
	try{
		Data d1 = Data();
		Data d2 = Data();

		Stuff myStuff = Stuff();

		cout<<"testing the ordering of the EventQueue"<<endl;
		eventQueue.make_event(1, &d1, d1.get_id(), &myStuff, myStuff.get_id(), VOID_EVENT);
		cout<<"created a node with time = 1" <<endl;
		eventQueue.make_event(0, &d2, d2.get_id(), &myStuff, myStuff.get_id(),  VOID_EVENT);
		cout << "created node with time = 0" <<endl;
		node1= eventQueue.pop();
		cout <<"time of first popped item = "<< node1.get_time() << " should be 0" << endl;
		node1 = eventQueue.pop();
		cout << "time of second popped item = " << node1.get_time() << " should be 1" <<endl;

		cout<<"testing ordering of eventNodes with same time field"<<endl;
		d1.set_data(1);
		d2.set_data(2);
		//since the node with &d1 was made first, it should be first
		eventQueue.make_event(2, &d1, d1.get_id(), &myStuff, myStuff.get_id(), VOID_EVENT);
		cout<<"created node with time = 2 and obj1.get_data = 1"<<endl;
		eventQueue.make_event(2, &d2, d2.get_id(), &myStuff,myStuff.get_id(),  VOID_EVENT);
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
		if(eventQueue.make_event(0, &d1, d1.get_id(), &myStuff, myStuff.get_id(), VOID_EVENT)){
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

	//testing advance_head, and getters for EventQueue
	Data d1, d2, d3;
	Stuff s1, s2, s3;
	d1 = Data();
	d1.set_data(1);
	d1.set_id(11);
	d2 = Data();
	d2.set_data(2);
	d2.set_id(22);
	d3 = Data();
	d3.set_data(3);
	d3.set_id(33);
	s1 = Stuff();
	s1.set_thing(10);
	s1.set_id(101);
	s2 = Stuff();
	s2.set_thing(20);
	s2.set_id(202);
	s3 = Stuff();
	s3.set_thing(30);
	s3.set_id(303);
	
	//order is d2, d3, d1
	eventQueue.make_event(10, &d1, d1.get_id(), &s1, s1.get_id(), CUSTOMER_ARRIVES);
	eventQueue.make_event(3, &d2, d2.get_id(), &s2, s2.get_id(), CUSTOMER_CHECKOUT_FINISH);
	eventQueue.make_event(5, &d3, d3.get_id(), &s3, s3.get_id(), CUSTOMER_CHANGES_LINE);
	cout<<"The current time of the EventQueue is: " << eventQueue.get_current_time() <<" which should be 3" <<endl;
	cout << "The first node's obj1 value should be 2 and the address should match " << &d2<< endl;
	cout <<"obj1's data is: " << eventQueue.get_ptr1()->get_data() <<" address is: "<< eventQueue.get_ptr1() << endl;
	
	eventQueue.advance_head();
	cout << "head was advanced" <<endl;
	cout << "The second node's time is: " << eventQueue.get_current_time() <<" which should be 5" << endl;
	cout << "The second node's type is: " << eventQueue.get_current_type() <<" which should be: " << CUSTOMER_CHANGES_LINE << endl;
	eventQueue.advance_head();
	cout << "head was advanced"<<endl;
	cout << "The third node's time is: "<< eventQueue.get_current_time() <<" which should be 10" << endl;


	cout << "Testing the print function" << endl;
	cout << eventQueue.to_str() << endl;
	eventQueue.advance_head();
	cout << eventQueue.to_str() << endl;
	eventQueue.make_event(100, &d1, d1.get_id(), &s1, s1.get_id(), CUSTOMER_ARRIVES);
	eventQueue.make_event(300, &d2, d2.get_id(), &s2, s2.get_id(), CUSTOMER_CHECKOUT_FINISH);
	eventQueue.make_event(500, &d3, d3.get_id(), &s3, s3.get_id(), CUSTOMER_CHANGES_LINE);
	cout << eventQueue.to_str() << endl;
	return 0;
}//end main
