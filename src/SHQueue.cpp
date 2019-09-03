#include "SHQueue.h"


void SHQueue::ins(SignalHandler s){
	INT_MASK;
	Cvor* q = new Cvor(s);
	if (p == 0) { p = z = q; }
	else { z->next = q; z = q; }
	length++;
	INT_UNMASK;
}

SHQueue::~SHQueue(){
INT_MASK;
Cvor* stari = 0;
for (Cvor* q = p; q != 0; q = q->next) {
	if (stari) {  delete stari; }
	stari = q;
}
if (stari) {  delete stari; }
length=0;
INT_UNMASK;
}

void SHQueue::delAll(){
	INT_MASK;
	Cvor* stari = 0;
	for (Cvor* q = p; q != 0; q = q->next) {
		if (stari) {  delete stari; }
		stari = q;
	}
	if (stari) {  delete stari; }
	length=0; p=0; z=0;
	INT_UNMASK;
}

SignalHandler SHQueue::del(){
		INT_MASK;
		SignalHandler vrati;
		if (p == 0) {INT_UNMASK; return 0;}
		else {
			Cvor* stari = p;
			vrati = p->sh;
			p = p->next;
			delete stari;
		}
		length--;
		INT_UNMASK;
		return vrati;
	}


void SHQueue::swap(SignalHandler s1,SignalHandler s2){
	INT_MASK;
	if(s1==s2) {INT_UNMASK; return;}
	Cvor* prvi=0,*drugi=0;
	for(Cvor* q=p;q!=0;q=q->next) {
		if(q->sh==s1) {prvi=q;}
		if(q->sh==s2) {drugi=q;}
	}
	if(prvi==0 || drugi==0) {INT_UNMASK; return;}
	SignalHandler temp=prvi->sh;
	prvi->sh=drugi->sh;
	drugi->sh=temp;
	INT_UNMASK;
}


void SHQueue::call(){
	for(Cvor* q=p;q!=0;q=q->next){
		(*(q->sh))();
	}
}
