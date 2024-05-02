#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>

union semun {
	int value;
	struct sem_id *buf;
	ushort *array;
};

void sem_signal(){

}

void sem_wait(){

}

int main(){
		
}
