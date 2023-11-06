//ASSIGNMENT 5

#include <stdio.h>

int main(){
    int m,n;  // m = number of processes, n = number of resources
    printf("Enter processes : \n");
    scanf("%d",&m);
    printf("Enter resources : \n");
    scanf("%d",&n);
    
    int alloc[m][n];   // Matrix to store the allocated resources for each process
    printf("Enter allocated : \n");
    for(int i=0;i<m;i++) 
    	for(int j=0;j<n;j++) 
    		scanf("%d",&alloc[i][j]);
    
    int max[m][n];   // Matrix to store the maximum required resources for each process
    printf("Enter max : \n");
    for(int i=0;i<m;i++) 
    	for(int j=0;j<n;j++) 
    		scanf("%d",&max[i][j]);
    
    int avail[n];   // Array to store the available resources
    printf("Enter available : \n");
    for(int i=0;i<n;i++) 
    	scanf("%d",&avail[i]);

    int need[m][n];   // Matrix to store the needed resources for each process
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            need[i][j] = max[i][j] - alloc[i][j];
        
    

    int success[m];   // Array to track if a process is successfully executed
    int index[m];     // Array to store the order of execution
    
    for(int i=0;i<m;i++) 
    	success[i] = 0;    // Initialize all processes as not successfully executed
    for(int i=0;i<m;i++) 
    	index[i] = 0;    // Initialize the index array

    int ind = 0;    // Index variable for the order of execution
    for(int i=0;i<m;i++){
    	if(ind<m){
	    	for(int j=0;j<m;j++){
		    if(!success[j]){   // Check if the process has not been successfully executed
		        int flag = 1;  // Flag to check if resources can be allocated to the process
		        for(int k=0;k<n;k++){
		            if(need[j][k] > avail[k]){   // Check if resources needed are greater than available
		                flag = 0;
		                break;
		            }
		        }
		        if(flag){
		            success[j] = 1;    // Mark the process as successfully executed
		            for(int k=0;k<n;k++) 
		            	avail[k] += alloc[j][k];   // Release allocated resources
		            index[ind++] = j+1;   // Record the order of execution
		        }
		    }
    		}
        }
       	else break;
    }
    int flag = 0;
    for(int i=0;i<m;i++){
        if(!success[i]) flag = i;   // Check if any process could not be successfully executed
    }
    if(flag) printf("Deadlock");   // If a process couldn't be executed, it's a deadlock
    else{
        for(int i=0;i<m;i++){
            printf("p%d-> ",index[i]);   // Print the order of execution
        }
    }
    return 0;
}

