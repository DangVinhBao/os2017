#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main (){
	
	int pid1 = fork();
	if (pid1 == 0){
	
		printf("\nChild process 1:");
		system("ps -ef");

		int pid2 = fork();
		if (pid2 == 0) {

			printf("\nChild process 2:");
			system("free -h");

		}
		else return 0;
		
	}
	else return 0;
		

	return 0;

}