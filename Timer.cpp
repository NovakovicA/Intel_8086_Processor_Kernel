#include "Timer.h"
#include <dos.h>
#include <iostream.h>
#include "ivtentry.h"

Time Timer::brojac=1;
Idle* Timer::idleNit=0;
Thread* Timer::pocetniThread=0;
volatile unsigned int Timer::lockFlag=1;
volatile unsigned int Timer::dispatchFlag=0;

void interrupt Timer::timer(...){
	if (!dispatchFlag) {if(PCB::running->vreme) brojac--;  PCB::semafori->timeDec(); }
	if (brojac == 0 || dispatchFlag) {
		if(lockFlag==1){
		if(PCB::running->vreme!=0 || dispatchFlag || PCB::running->getState()!=RUNNING){
		dispatchFlag = 0;
		asm mov tsp, sp;
		asm mov tss, ss;
		asm	mov tbp, bp;

		/*{int br=0; Queue* que=new Queue(); PCB* t;
				while((t=Scheduler::get())!=0){
					br+=1; que->ins(t);
				}
				cout << "=======================" << endl; asm cli;
				cout << "Broj niti u sched: " << br << "." << endl; asm cli;
				cout << "=======================" << endl; asm cli;

				while(!que->isEmpty()) Scheduler::put(que->del());
				delete que;}*/

		PCB::running->sp=tsp;
		PCB::running->ss=tss;
		PCB::running->bp=tbp;
		if (PCB::running->getState()==RUNNING) { PCB::running->setState(READY); Scheduler::put((PCB*)PCB::running);}


		PCB::running=Scheduler::get();

		if(PCB::running==0) {PCB::running=idleNit->myPCB;}

		if(PCB::running!=idleNit->myPCB) PCB::running->setState(RUNNING);

		PCB::running->obradiSignale();


		while (PCB::running->getState()==KILL) {
			PCB::running->krajNiti();
			PCB::running->kill();
			PCB::running=Scheduler::get();
			if(PCB::running==0) {PCB::running=idleNit->myPCB;}
			if(PCB::running!=idleNit->myPCB) PCB::running->setState(RUNNING);
			PCB::running->obradiSignale();
		}

		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;

		if(PCB::running->vreme!=0) brojac = PCB::running->vreme;
		else brojac=1;



		asm mov sp, tsp;
		asm mov ss, tss;
		asm mov bp, tbp;
		}
		}
		else dispatchFlag = 1;
		}
	if(!dispatchFlag) { tick(); asm int 60h;}
}




Timer::Timer(){
	INT_MASK;
	oldINTR=getvect(0x08);
	setvect(0x08,Timer::timer);
	setvect(0x60,oldINTR);

	PCB::gBlokiraniSignali=new SignalId[16];

	PCB* temp=new PCB();
	pocetniThread=temp->mojThread;
	idleNit = new Idle();
	idleNit->start();
	PCB::running=temp;
	for(int i=0;i<16;i++) PCB::gBlokiraniSignali[i]=0;
	INT_UNMASK;
}

Timer::~Timer(){
	INT_MASK;
	setvect(0x08,oldINTR);
	delete PCB::procesi;
	delete PCB::semafori;
	delete idleNit;
	delete pocetniThread;
	delete [] PCB::gBlokiraniSignali;
	INT_UNMASK;
}




