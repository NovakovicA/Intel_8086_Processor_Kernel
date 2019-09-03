#include "SemQueue.h"
#include <iostream.h>



void SemQueue::ins(KernelSem* s){
	    INT_MASK;
		Elem* q = new Elem(s);
		if (p == 0) { p = z = q; }
		else { z->next = q; z = q; }
		length++;
		INT_UNMASK;
	}


 void SemQueue::del(KernelSem* s){
		INT_MASK;
		Elem* q=0; Elem* qq=0;
		if (p == 0) {INT_UNMASK; return;}
		else {
			for(q=p;q!=0;q=q->next) {
				if(q->sem==s) {
					if(qq==0) {p=p->next; delete q; length--; break;}
					else{
						if(z==q) z=qq;
						qq->next = q->next; delete q; length--; break;}
								}
				else{
					qq=q;
				}
			}
		}
		INT_UNMASK;
		return;
	}

 KernelSem* SemQueue::del(){
 		INT_MASK;
 		KernelSem* vrati;
 		if (p == 0) {INT_UNMASK; return 0;}
 		else {
 			Elem* stari = p;
 			vrati = p->sem;
 			p = p->next;
 			delete stari;
 		}
 		length--;
 		INT_UNMASK;
 		return vrati;
 	}


 SemQueue::~SemQueue(){
	 INT_MASK;
	 Elem* stari = 0;
	 for (Elem* q = p; q != 0; q = q->next) {
	 	if (stari) {  delete stari; }
	 	stari = q;
	 }
	 if (stari) {  delete stari; }
	 INT_UNMASK;
 }

 void SemQueue::timeDec(){
	 INT_MASK;
	 for(Elem* q=p;q!=0;q=q->next){
		 (q->sem)->timeDec();
	 }
	 INT_UNMASK;
 }
