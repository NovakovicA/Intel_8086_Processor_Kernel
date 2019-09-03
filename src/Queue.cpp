#include "Queue.h"
#include <iostream.h>


void Queue::ins(PCB* c,Time t){
		INT_MASK;
		Cvor* q = new Cvor(c,t);
		if (p == 0) { p = z = q; }
		else { z->next = q; z = q; }
		length++;
		INT_UNMASK;
	}

PCB* Queue::del(){
		INT_MASK;
		PCB* vrati;
		if (p == 0) {INT_UNMASK; return 0;}
		else {
			Cvor* stari = p;
			vrati = p->pcb;
			p = p->next;
			delete stari;
		}
		length--;
		INT_UNMASK;
		return vrati;
	}


Thread* Queue::getThreadById(ID id){
		INT_MASK;
		Cvor* temp; Thread* t=0;
		for(temp=p;temp!=0;temp=temp->next) if(temp->pcb!=0) if(temp->pcb->getId()==id) {t=temp->pcb->myThread(); break;}
		INT_UNMASK;
		return t;
	}

int Queue::contains(PCB* s){
		INT_MASK;
		Cvor* temp;
		for(temp=p;temp!=0;temp=temp->next) if(temp->pcb!=0) if(temp->pcb==s) {INT_UNMASK; return 1;}
		INT_UNMASK;
		return 0;
	}


Queue::~Queue(){
INT_MASK;
mojSem=0;
Cvor* stari = 0;
for (Cvor* q = p; q != 0; q = q->next) {
	if (stari) {  delete stari; }
	stari = q;
}
if (stari) {  delete stari; }
INT_UNMASK;
}

void Queue::del(PCB* s){
		INT_MASK;
		Cvor* q=0; Cvor* qq=0;
		if (p == 0) {INT_UNMASK; return;}
		else {
			for(q=p;q!=0;q=q->next) {
				if(q->pcb==s) {
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


void Queue::timeDec(){
for(Cvor* q=p;q!=0;){
	Cvor* s=q->next;
	if(q->time!=0) {
		q->time-=1;
		if(q->time==0){
			PCB* ret=q->pcb;
			del(q->pcb);
			if(mojSem!=0) mojSem->val++;
			ret->waitReturn=0; ret->setState(READY);
			Scheduler::put(ret);
		}
	}
	q=s;
}



}
