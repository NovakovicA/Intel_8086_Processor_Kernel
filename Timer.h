
#ifndef TIMER_H_
#define TIMER_H_
#include <dos.h>
#include "pcb.h"
#include "schedule.h"
#include "idle.h"

typedef void interrupt (*pInterrupt)(...);
class PCB;



#define INT_MASK asm {\
	pushf;\
	cli;\
}

#define INT_UNMASK asm popf

extern void tick();

static unsigned		 tsp;
static unsigned		 tss;
static unsigned 	 tbp;

class Timer{
	static Time			 brojac;
	static Idle* 		 idleNit;
	static Thread* 		 pocetniThread;
	pInterrupt 			 oldINTR;
	static void interrupt timer(...);


public:
	static volatile unsigned int lockFlag;
	static volatile unsigned int dispatchFlag;
	 Timer();
	~Timer();

};



#endif
