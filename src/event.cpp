#include <iostream.h>
#include "event.h"
#include "Timer.h"
#include "kerevent.h"

Event::Event (IVTNo ivtNo){
	INT_MASK;
	myImpl=new KernelEv(ivtNo);
	INT_UNMASK;
}

void Event::wait(){
	INT_MASK;
	myImpl->wait();
	INT_UNMASK;
}

void Event::signal(){
	INT_MASK;
	myImpl->signal();
	INT_UNMASK;
}


Event::~Event(){
	INT_MASK;
	delete myImpl;
	INT_UNMASK;
}


