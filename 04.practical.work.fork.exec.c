#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main (){

	printf("Main before fork()\n");
	
	int pid1 = fork();
	if (pid1 == 0){
	
		printf("\nChild process run ps -ef:\n");
		char *ps_cmd[] = {"ps", "-ef", NULL};
		execvp("ps", ps_cmd);

		
	}
	
	else{

	int pid2 = fork();
	if (pid2 == 0) {

		printf("\nChild process run free -h:\n");
		char *free_cmd[] = {"free", "-h", NULL};
		execvp("free", free_cmd);

	}

	}

	return 0;

}
