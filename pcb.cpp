#include "pcb.h"
#include "SHQueue.h"
#include <dos.h>
#include <iostream.h>

int PCB::gID=1000;
volatile PCB* PCB::running=0;
SemQueue* PCB::semafori=new SemQueue();
Queue* PCB::procesi=new Queue();
SignalId* PCB::gBlokiraniSignali=0;


PCB::PCB(Thread* t, StackSize stackSize, Time timeSlice ){
	INT_MASK;
	id=gID++;
	mojThread=t;
	vreme=timeSlice;
	queue=new Queue();
	waitReturn=1;
	maker=(PCB*)PCB::running;
	stek = new unsigned[stackSize];
	stek[stackSize-1] =0x200;
	stek[stackSize-2] = FP_SEG(&(wrapper));
	stek[stackSize-3] = FP_OFF(&(wrapper));
	sp = FP_OFF(stek+stackSize-12);
	ss = FP_SEG(stek+stackSize-12);
	bp = FP_OFF(stek+stackSize-12);
	stanje=NEW;
	signali=new SHQueue*[16];
	pSignali = new SIDQueue();
	blokiraniSignali=new SignalId[16];
	for(int i=0;i<16;i++) {
		signali[i]=new SHQueue();
		if(maker){
		blokiraniSignali[i]=maker->blokiraniSignali[i];
		int brhandlera=(maker->signali[i])->len();
		for(int j=0;j<brhandlera;j++){
			SignalHandler sh=(maker->signali[i])->del();
			signali[i]->ins(sh);
			(maker->signali[i])->ins(sh);
		}}
		else blokiraniSignali[i]=0;
	}
	procesi->ins(this);
	registerHandler(0, killThread);
	mojSem=0;
	INT_UNMASK;
}

PCB::PCB(){
	INT_MASK;
	id=gID++;
	mojThread=new Thread();
	delete mojThread->myPCB;
	mojThread->myPCB=this;
	gID--;
	vreme=0;
	sp=ss=bp=0; stek=0;
	queue=new Queue();
	waitReturn=1;
	maker=0;
	stanje=RUNNING;
	signali=new SHQueue*[16];
	pSignali = new SIDQueue();
	blokiraniSignali=new SignalId[16];
	for(int i=0;i<16;i++) {
		signali[i]=new SHQueue();
		blokiraniSignali[i]=0;
	}
	procesi->ins(this);
	registerHandler(0, killThread);
	mojSem=0;
	INT_UNMASK;
}


void PCB::run(){
	mojThread->run();
	setState(FINISHED);
	krajNiti();
	dispatch();
}


void PCB::wrapper(){
	PCB::running->run();
}

PCB::~PCB()	{
INT_MASK;
if(PCB::procesi->contains(this)){
obradiSignale();
procesi->del(this);
for(int i=0;i<16;i++) delete signali[i];
delete [] signali;
delete pSignali;
delete [] blokiraniSignali;
if (stek!=0) delete [] stek;
mojSem=0;
}
INT_UNMASK;
}

void PCB::kill(){
	if (stek!=0) delete [] stek;
	stek=0;
}


void PCB::signal(SignalId id){
	INT_MASK;
	if(id<16) {
		pSignali->ins(id);
	}
	INT_UNMASK;
}

void PCB::registerHandler(SignalId signal, SignalHandler handler) {
	INT_MASK;
	if(signal<16) {
		signali[signal]->ins(handler);
	}
	INT_UNMASK;
}

void PCB::unregisterAllHandlers(SignalId id){
	INT_MASK;
	if(id<16) {
		signali[id]->delAll();
	}
	INT_UNMASK;
}

void PCB::swap(SignalId id, SignalHandler hand1, SignalHandler hand2){
	INT_MASK;
	if(id<16) {
		signali[id]->swap(hand1,hand2);
	}
	INT_UNMASK;

}

void PCB::blockSignal(SignalId signal){
	INT_MASK;
	blokiraniSignali[signal]=1;
	INT_UNMASK;
}

void PCB::blockSignalGlobally(SignalId signal){
	INT_MASK;
	gBlokiraniSignali[signal]=1;
	INT_UNMASK;
}

void PCB::unblockSignal(SignalId signal){
	INT_MASK;
	blokiraniSignali[signal]=0;
	INT_UNMASK;
}

void PCB::unblockSignalGlobally(SignalId signal){
	INT_MASK;
	gBlokiraniSignali[signal]=0;
	INT_UNMASK;
}

void PCB::obradiSignale(){
	Timer::lockFlag=0;
	asm sti;
	int brsig=pSignali->len();
	for(int i=0;i<brsig;i++){
		SignalId sig=pSignali->del();
		if(sig!=17){
			if(!blokiraniSignali[sig] && !gBlokiraniSignali[sig]){
				signali[sig]->call();
			}
			else{
				pSignali->ins(sig);
			}
		}
	}
	asm cli;
	Timer::lockFlag=1;
}


void PCB::krajNiti(){
			while(!queue->isEmpty()){
					PCB* t=queue->del();
					t->setState(READY);
					Scheduler::put(t);
				}
			if(stanje==KILL && mojSem!=0){
				mojSem->signal();
				mojSem=0;
				}
				if(maker) {maker->signal(1);}
				signal(2);
}
