#ifndef KEREVENT_H_
#define KEREVENT_H_
#include "event.h"
#include "pcb.h"
#include "ivtentry.h"

class IVTEntry;



class KernelEv{
	int val;
	PCB* blocked, * maker;
	IVTNo num;
	IVTEntry* entry;


	friend class IVTEntry;
	friend class Event;


//public:
	void wait();
	void signal();
	KernelEv(IVTNo i);
	~KernelEv();
};

#endif

