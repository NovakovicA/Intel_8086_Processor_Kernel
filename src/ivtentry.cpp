#include "ivtentry.h"
#include <dos.h>

IVTEntry* IVTEntry::IVT[256]={0};


IVTEntry::IVTEntry(int i, pInterrupt pRut){
	INT_MASK;
	num=i;
	IVT[num]=this;
	event=0;
	oldISR=getvect(num);
	setvect(num,pRut);
	INT_UNMASK;
}

void IVTEntry::callOld(){
	oldISR();
}

void IVTEntry::signal(){
	INT_MASK;
	if(event!=0) event->signal();
	//dispatch();
	INT_UNMASK;
}

IVTEntry::~IVTEntry(){
	INT_MASK;
	IVT[num]=0;
	setvect(num,oldISR);
	INT_UNMASK;
}


