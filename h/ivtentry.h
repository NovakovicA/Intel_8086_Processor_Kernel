#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "pcb.h"
#include "Timer.h"
#include "event.h"
#include "kerevent.h"

class KernelEv;

class IVTEntry{
	pInterrupt oldISR;
	IVTNo num;


public:
	IVTEntry(int i,pInterrupt p);
	IVTEntry(){}
	static IVTEntry* IVT[];
	KernelEv* event;
	void signal();
	void callOld();
	~IVTEntry();
};



#endif
