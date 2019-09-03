#include <iostream.h>
#include "timer.h"



extern int userMain(int,char*[]);

int main(int argc, char* argv[]){
	Timer* timer=new Timer();
	int ret = userMain(argc,argv);
	delete timer;
	return ret;
}
