#include "idle.h"
#include "Timer.h"
#include <iostream.h>


void Idle::run(){
	while(1) {
		//for(int i=0;i<30000;i++) for(int j=0;j<30000;j++);
	//cout << "Idle nit(" << getId() << ") radi..." << endl;
	}
}

void Idle::start(){
	INT_MASK;
	myPCB->setState(IDLE);
	INT_UNMASK;
}
