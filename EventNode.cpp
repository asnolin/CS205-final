/*
 * EventNode.cpp
 *
 * TODO
 * finish eventQueue
 * rename file
 *
 */

#include"EventNode.hpp"


//Event Node constructors
template<class T>
EventNode<T>::EventNode(){
	time = 1;
	obj = nullptr;
	type = VOID_EVENT;
}//end no-arg constructor

template<class T>
EventNode<T>::EventNode(unsigned long int inTime, T *inObj, eventType inType){
	time = inTime;
	obj = inObj;
	type = inType;
}//end constructor



//EventNode overloaded <
template<class T>
bool EventNode<T>::operator<(EventNode rhs) const{
	return time < rhs.time;
}//end overloaded < op


//EventNode getters
template<class T>
unsigned long int EventNode<T>::get_time(){
	return time;
}//end get_time

template<class T>
T *EventNode<T>::get_obj(){
	return obj;
}//end get_obj

template<class T>
eventType EventNode<T>::get_type(){
	return type;
}//end get_type


//EventQueue constructor
template<class T>
EventQueue<T>::EventQueue(){
	//init eventQ
	//TODO
}//end no-arg constructor

template<class T>
bool EventQueue<T>::make_event(unsigned long int inT, T*inObj, eventType inType){
	//TODO
	//create new EventNode in heap
	//add EventNode to eventQ
	//return true if successful
}//end make_event



//EventQueue getters
template<class T>
unsigned long int EventQueue<T>::get_current_time(){
	return currentTime;
}//end get_current_time

template<class T>
EventNode<T> EventQueue<T>::pop(){
	return eventQ.pop();
}//end get_cust()

