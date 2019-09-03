
#ifndef SIDQUEUE_H_
#define SIDQUEUE_H_
#include "pcb.h"
#include "thread.h"
#include "Timer.h"
#include <dos.h>

class SIDQueue {
	class Cvor {
			SignalId s;
			Cvor* next;
			friend class SIDQueue;
			Cvor(SignalId ss) {
				s=ss; next = 0;
			}
			~Cvor(){
				next=0; s=0;
			}
		};
	Cvor* p;
	Cvor* z;
	int length;

	friend class Timer;
	friend class Thread;
	friend class PCB;
	friend class KernelSem;

	//public:

	SIDQueue() {
		p = z = 0;
		length=0;
	}

	int len() const{
		return length;
	}

	void ins(SignalId s);

	SignalId del();

	int isEmpty() const{
		if(p==0) return 1;
		else return 0;
	}

	~SIDQueue();

};




#endif
