#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int ar[10],n ;

void swap(int *n1, int *n2){
	int temp;
	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void getarray(){
	printf("ENTER NO. OF ELEMENTS:: ");
	scanf("%d",&n);
	
	printf("\nENTER ELEMENTS:: \n");
	for(int i=0; i<n; i++){
		printf("\tElement %d : ",i+1);
		scanf("%d",&ar[i]);
	}
	
	printf("\nGIVEN ELEMENTS:: \n");
	printf("\t[\t");
	for(int i=0; i<n; i++){
		printf("%d\t",ar[i]);
	}
	printf("]\n");	
}

void bubblesort(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1;j++){
		    if (ar[j] > ar[j+1])
		      swap(&ar[j], &ar[j+1]);
		}    
    	}
    	
    	printf("\tSORTED ELEMENTS:: \n");
	printf("\t[\t");
	for(int i=0; i<n; i++){
		printf("%d\t",ar[i]);
	}
	printf("]\n\n");
}

void insertionsort(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n-1;j++){
		    if (ar[j] > ar[j+1])
		      swap(&ar[j], &ar[j+1]);
		}    
    	}
    	
    	printf("\tSORTED ELEMENTS:: \n");
	printf("\t[\t");
	for(int i=0; i<n; i++){
		printf("%d\t",ar[i]);
	}
	printf("]\n\n");
}

int main(){
	int pid, n, ch;
	getarray();
	
	printf("\n************* MENU *************");
	printf("\n1] NORMAL PROCESS \n2] ORPHAN \n3] ZOMBIE \n4] EXIT \n");
	printf("\n********* ENTER CHOICE *********\n");		
	

	while(ch!=4){		
		scanf("%d",&ch);
	printf("\n");		
		switch(ch){
			case 1:{ 			
				pid_t pid = fork();		// creating child process
								
				if(pid==0){
					printf("\nCreating child process.\n");
					printf("Child process created with id : %d\n",getpid());
					printf("-- CHILD PROCESS -->\n");
					
					insertionsort();
				}
				else if(pid>0){
					printf("\nCreating parent process.\n");
					printf("Parent process created with id : %d\n",getppid());
					printf("-- PARENT PROCESS -->\n");
					
					bubblesort();
				}
				else{
					printf("\nERROR OCCURED !!\n");
				}
				break;
			}
			case 2:{
				pid_t pid=fork();
				if(pid<0){
					printf("\nERROR OCCURED !!\n");
				}
				else if(pid==0){
					printf("\n-- ORPHAN PROCESS -->\n");
					printf("Child process id: %d\n",getpid());
					printf("Parent process id: %d\n",getppid());
					sleep(3);			// allow parent to finish
					
				}
				else{
					printf("Parent process id: %d\n",getppid());
					printf("Parent has finished.\n");
				}
				break;
			}
			case 3:{
				pid_t pid=fork();
				if(pid<0){
					printf("\nERROR OCCURED !!\n");
				}
				else if(pid==0){
					printf("\n-- ZOMBIE PROCESS -->\n");
					printf("Child process id: %d\n",getpid());						
				}
				else{
					sleep(3);			// allow parent to finish
					printf("Parent process id: %d\n",getppid());
					printf("Parent has finished.\n");
				}
				break;
			}
			case 4:{
				printf("************* PROGRAM EXITED *************\n");
				break;
			}
			default:{
				printf("WRONG CHOICE. SELECT AGAIN !!\n");
			} 				
		}
		
	}
	return 0;
}

