#ifndef SHQUEUE_H_
#define SHQUEUE_H_
#include "pcb.h"
#include "thread.h"
#include "Timer.h"
#include <dos.h>


class SHQueue {
	class Cvor {
			SignalHandler sh;
			Cvor* next;
			friend class SHQueue;
			Cvor(SignalHandler p) {
				sh = p;  next = 0;
			}
			~Cvor(){
				sh=0;
				next=0;
			}
		};
	Cvor* p;
	Cvor* z;
	int length;

	friend class Thread;
	friend class PCB;

	//public:

	SHQueue() {
		p = z = 0;
		length=0;
	}

	int len() const{
		return length;
	}

	void ins(SignalHandler s);

	void delAll();

	SignalHandler del();

	void swap(SignalHandler s1,SignalHandler s2);

	int isEmpty() const{
		if(p==0) return 1;
		else return 0;
	}

	void call();

	~SHQueue();

};





#endif
