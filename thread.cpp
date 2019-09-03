#include "thread.h"
#include "pcb.h"
#include "Timer.h"
#include "schedule.h"
#include "Queue.h"
#include <dos.h>
#include <iostream.h>



Thread::Thread(StackSize stackSize , Time timeSlice){
	INT_MASK;
	if(stackSize>65536) stackSize=65536;
	myPCB = new PCB(this, stackSize/sizeof(unsigned), timeSlice);
	INT_UNMASK;
}

Thread::~Thread(){
	INT_MASK;
	if(myPCB!=0) waitToComplete();
	if(myPCB!=0) delete myPCB;
	INT_UNMASK;
}

ID Thread::getId(){
	return myPCB->getId();
}

ID Thread::getRunningId(){
	return PCB::running->getId();
}

Thread* Thread::getThreadById(ID id){
	Thread* t = (PCB::procesi)->getThreadById(id);
return t;
}


void Thread::start(){
INT_MASK;
if(myPCB->stanje==NEW){
	myPCB->setState(READY);
	Scheduler::put(myPCB);
}
INT_UNMASK;
}


void Thread::waitToComplete(){
	INT_MASK;
	if(myPCB!=0){
	if(myPCB->getState()==RUNNING || myPCB->getState()==FINISHED || myPCB->getState()==NEW || myPCB->getState()==KILL || myPCB->getState()==IDLE) {INT_UNMASK;   return;}
	else{
		PCB::running->setState(BLOCKED);
		myPCB->queue->ins((PCB*)PCB::running);
		INT_UNMASK;
		dispatch();
	}
	}
}


void dispatch(){
		INT_MASK;
		Timer::dispatchFlag = 1;
		asm int 08h;
		INT_UNMASK;
	}

void Thread::signal(SignalId s){
	myPCB->signal(s);
}


void Thread::registerHandler(SignalId signal, SignalHandler handler) {
	myPCB->registerHandler(signal, handler);
}

void Thread::unregisterAllHandlers(SignalId id) 	{
	myPCB->unregisterAllHandlers(id);
}

void Thread::swap(SignalId id, SignalHandler hand1, SignalHandler hand2){
	myPCB->swap(id, hand1, hand2);
}

void Thread::blockSignal(SignalId signal){
	myPCB->blockSignal(signal);
}
void Thread::blockSignalGlobally(SignalId signal){
	PCB::blockSignalGlobally(signal);
}
void Thread::unblockSignal(SignalId signal){
	myPCB->unblockSignal(signal);
}
void Thread::unblockSignalGlobally(SignalId signal){
	 PCB::unblockSignalGlobally(signal);
}



