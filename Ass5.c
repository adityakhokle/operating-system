
#include <stdio.h>

int main(){
    int m,n;
    printf("Enter processes : \n");
    scanf("%d",&m);
    printf("Enter resources : \n");
    scanf("%d",&n);
    
    int alloc[m][n];
    printf("Enter allocated : \n");
    for(int i=0;i<m;i++) 
    	for(int j=0;j<n;j++) 
    		scanf("%d",&alloc[i][j]);
    
    int max[m][n];
    printf("Enter max : \n");
    for(int i=0;i<m;i++) 
    	for(int j=0;j<n;j++) 
    		scanf("%d",&max[i][j]);
    
    int avail[n];
    printf("Enter available : \n");
    for(int i=0;i<n;i++) 
    	scanf("%d",&avail[i]);

    int need[m][n];
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            need[i][j] = max[i][j] - alloc[i][j];
        
    

    int success[m];
    int index[m];
    
    for(int i=0;i<m;i++) 
    	success[i] = 0;
    for(int i=0;i<m;i++) 
    	index[i] = 0;

    int ind = 0;
    for(int i=0;i<m;i++){
    	if(ind<m){
	    	for(int j=0;j<m;j++){
		    if(!success[j]){
		        int flag = 1;
		        for(int k=0;k<n;k++){
		            if(need[j][k] > avail[k]){
		                flag = 0;
		                break;
		            }
		        }
		        if(flag){
		            success[j] = 1;
		            for(int k=0;k<n;k++) 
		            	avail[k] += alloc[j][k];
		            index[ind++] = j+1;
		        }
		    }
    		}
        }
       	else break;
    }
    int flag = 0;
    for(int i=0;i<m;i++){
        if(!success[i]) flag = i;
    }
    if(flag) printf("Deadlock");
    else{
        for(int i=0;i<m;i++){
            printf("p%d-> ",index[i]);
        }
    }
    return 0;
}

