#include "kersem.h"
#include "pcb.h"
#include <iostream.h>


KernelSem::KernelSem(int i){
	val=i;
	queue=new Queue(this);
	(PCB::semafori)->ins(this);
}

KernelSem::~KernelSem(){
	while (val<0) signal();
	delete queue;
	(PCB::semafori)->del(this);
}


int KernelSem::signal(int n){
	if(n<0) return n;


	else if(n==0){
		val++;
			if(val <= 0){
				PCB* p = queue->del();
				if(p){	p->setState(READY); p->waitReturn=1; Scheduler::put(p); }
			}
			return 0;
	}


	else if(n>0){
		int brOdblk=0;
		val+=n;
	while(n>0 && !queue->isEmpty()){
			PCB* p=queue->del();
			if (p) {p->setState(READY); p->waitReturn=1; Scheduler::put(p); }
			n--;
			brOdblk++;
	}
	return brOdblk;
	}
}



int KernelSem::wait(Time maxTimeToWait){
	val--;
	if(val < 0){
		queue->ins((PCB*)PCB::running,maxTimeToWait);
		(PCB::running)->setState(BLOCKED);
		if(!maxTimeToWait) (PCB::running)->mojSem=this;
		dispatch();
		if(!maxTimeToWait) (PCB::running)->mojSem=0;
		return (PCB::running)->waitReturn;
	}
	return 1;
}


void KernelSem::timeDec(){
	queue->timeDec();
}
