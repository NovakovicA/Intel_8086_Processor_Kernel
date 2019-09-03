
#ifndef _PCB_H_
#define _PCB_H_
#include <Queue.h>
#include <thread.h>
#include <dos.h>
#include "SIDQueue.h"
#include <iostream.h>

#include "SemQueue.h"
#include "Timer.h"


enum State{FINISHED=0,READY=1,BLOCKED=2,NEW=3,RUNNING=4,KILL=5,IDLE=6};

class SIDQueue;
class Queue;
class Thread;
class SemQueue;
class SHQueue;


class PCB {
	unsigned int  sp;
	unsigned int  ss;
	unsigned int  bp;
	unsigned*     stek;
	State         stanje;
	Time          vreme;
	Thread*       mojThread;
	static   ID   gID;
	ID            id;
	Queue* 		  queue;

	SHQueue** signali;
	SIDQueue* pSignali;
	SignalId* blokiraniSignali;
	static SignalId* gBlokiraniSignali;
	PCB* maker;
	KernelSem* mojSem;





	friend class Thread;
	friend class Timer;
	friend class Idle;
	friend class Queue;
	friend class KernelSem;
	friend class KernelEv;

	void obradiSignale();

	static void killThread(){
		PCB::running->setState(KILL);
	}

	void krajNiti();

	void kill();
	PCB();

//public:
	volatile static PCB* running;
	static Queue* procesi;
	static SemQueue* semafori;

	int waitReturn; // 1 za odblokiranje u okviru wait() i ako nije odblokirana, 0 za odblokiranje u okviru prekidne rutine timer()

	PCB(Thread* t, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);

	State getState() const{
		return stanje;
	}

	void setState(State s){
		stanje=s;
	}

	Thread* myThread(){
		return mojThread;
	}

	ID getId() const{
		return id;
	}

	void run();

	static void wrapper();

	~PCB();
	void signal(SignalId signal);

	void registerHandler(SignalId signal, SignalHandler handler);
	void unregisterAllHandlers(SignalId id);
	void swap(SignalId id, SignalHandler hand1, SignalHandler hand2);

	void blockSignal(SignalId signal);
	static void blockSignalGlobally(SignalId signal);
	void unblockSignal(SignalId signal);
	static void unblockSignalGlobally(SignalId signal);

};


#endif
