#ifndef SEMQUEUE_H_
#define SEMQUEUE_H_

#include "kersem.h"
#include <dos.h>

class KernelSem;




class SemQueue {
	class Elem {
			KernelSem* sem;
			Elem* next;
			friend class SemQueue;
			Elem(KernelSem* s) {
				sem = s;  next = 0;
			}
			~Elem(){
				sem=0; next=0;
			}
		};
	Elem* p;
	Elem* z;
	int length;

	friend class Timer;
	friend class KernelSem;
	friend class PCB;

	//public:

	SemQueue() {
		p = z = 0;
		length=0;
	}

	int len() const{
		return length;
	}

	void ins(KernelSem* s);

	void del(KernelSem* s) ;

	KernelSem* del();

	int isEmpty() const{
		if(p==0) return 1;
		else return 0;
	}

	void timeDec();

	~SemQueue();


};



#endif
