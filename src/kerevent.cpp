#include "kerevent.h"
#include <iostream.h>

KernelEv::KernelEv(IVTNo i){
	INT_MASK;
	num=i;
	IVTEntry::IVT[num]->event=this;
	maker=(PCB*)PCB::running;
	blocked=0; val=0;
	INT_UNMASK;
}


void KernelEv::wait(){
	if(PCB::running==maker){
	if (val==0){
		PCB::running->setState(BLOCKED);
		blocked=(PCB*)PCB::running;
		dispatch();
	}
	else val=0;
	}
}

void KernelEv::signal(){
	INT_MASK;
	if(blocked==0) {val=1; INT_UNMASK; return;}
	blocked->setState(READY);
	Scheduler::put(blocked);
	blocked=0;
	INT_UNMASK;
}


KernelEv::~KernelEv(){
	INT_MASK;
	IVTEntry::IVT[num]->event=0;
	if(blocked){
		blocked->setState(READY);
		Scheduler::put(blocked);
		blocked=0;
	}
	INT_UNMASK;
}
