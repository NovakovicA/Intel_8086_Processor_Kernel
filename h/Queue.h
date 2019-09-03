#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "pcb.h"
#include "thread.h"
#include "Timer.h"
#include <dos.h>



class PCB;
class KernelSem;


class Queue {
	class Cvor {
			PCB* pcb;
			Time time;
			Cvor* next;
			friend class Queue;
			Cvor(PCB* p,Time t=0) {
				pcb = p; time=t; next = 0;
			}
			~Cvor(){
				pcb=0;
				next=0;
			}
		};
	Cvor* p;
	Cvor* z;
	KernelSem* mojSem;
	int length;

	friend class Timer;
	friend class Thread;
	friend class PCB;
	friend class KernelSem;

	//public:

	Queue(KernelSem* s=0) {
		p = z = 0;
		mojSem=s;
		length=0;
	}

	int len() const{
		return length;
	}

	void ins(PCB* c,Time t=0);

	PCB* del() ;
	void del(PCB* s);
	int contains(PCB* s);

	int isEmpty() const{
		if(p==0) return 1;
		else return 0;
	}

	~Queue();

	Thread* getThreadById(ID id);

	void timeDec();

};





#endif
