#include"EventNode.hpp"
#include<queue>
#include<vector>


#define MAX_SIZE 100

using namespace std;

void init_queue(priority_queue<EventNode> *q){
	for(int i = 0; i < MAX_SIZE; ++i){
		EventNode *node = new EventNode();
		q->push(*node);
	}
}

int main(int argc, char* argv[]){
	priority_queue<EventNode> eventQ;
	init_queue(&eventQ);
	return 0;
}
