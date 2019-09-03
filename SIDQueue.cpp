#include "SIDQueue.h"
#include <iostream.h>


void SIDQueue::ins(SignalId s){
		INT_MASK;
		Cvor* q = new Cvor(s);
		if (p == 0) { p = z = q; }
		else { z->next = q; z = q; }
		length++;
		INT_UNMASK;
	}



SIDQueue::~SIDQueue(){
INT_MASK;
Cvor* stari = 0;
for (Cvor* q = p; q != 0; q = q->next) {
	if (stari) {  delete stari; }
	stari = q;
}
if (stari) {  delete stari; }
INT_UNMASK;
}



SignalId SIDQueue::del(){
		INT_MASK;
		SignalId vrati=17;
		if (p == 0) {INT_UNMASK; return 17;}
		else {
			Cvor* stari = p;
			vrati = p->s;
			p = p->next;
			delete stari;
		}
		length--;
		INT_UNMASK;
		return vrati;
	}




