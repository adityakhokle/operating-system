/* Assignment No.2 A 

A. Implement the C program in which main program accepts the integers to be sorted. Main program
uses the FORK system call to create a new process called a child process. Parent process sorts the
integers using sorting algorithm and waits for child process using WAIT system call to sort the integers
using any sorting algorithm. Also demonstrate zombie and orphan states.
*/
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

// Function to perform Bubble Sort on an array
void childprocess(int n , int arr[]){
  // Bubble sort algorithm
  for(int i=0;i<n;i++){
    for(int j=i+1 ; j<n;j++){
      if(arr[i]>arr[j]){                 // Swap elements if they are in the wrong order
         int temp=arr[i];
         arr[i]=arr[j];
         arr[j]=temp;
      }
   }
 }
}
// Function to perform Quick Sort on an array
 // Quick Sort function
void parentprocess(int arr[], int low, int high)
{
	 int pivot , temp , i ,j;
       if(low < high){
          pivot=low;
          i=low;
          j=high;
          while(i<j){
             while(arr[i]<=arr[pivot] && i<high){            // Find elements smaller than or equal to pivot
                i++;
             }
             while(arr[j]>arr[pivot]){                     // Find elements greater than pivot
                j--;
             }
             if(i<j){                                       // Swap elements if they are in the wrong order
               temp=arr[i];
               arr[i]=arr[j];
               arr[j]=temp;
             }
          }
          temp=arr[pivot];                                 // Swap the pivot element with the element at position j
          arr[pivot]=arr[j];
          arr[j]=temp;
 // Recursively sort the two sub-arrays
          parentprocess(arr,low,j-1);
          parentprocess(arr,j+1,high);
       }
}

int main(void){
 
  int n;

	// Input the number of elements to be sorted
  printf("Enter the Number of elements:\n");
  scanf("%d",&n);
  
  int arr[n];
  printf("Enter the Numbers:\n");            // Input the array elements
  for(int i=0;i<n;i++){
     scanf("%d",&arr[i]);
} 
  int p;
  p=fork();                             // Create a child process using fork()
  if(p==-1){                            // Handle the fork() error case
    printf("There is an error while calling fork()\n");
    }
  if(p==0){
// Code executed in the child process (Bubble Sort)
    printf("We are in the child process (Bubble Sort) \n");
    printf("child  => PID:%d\n",getpid());  // Print child process ID
    printf("Parent => PID: %d\n", getppid());  // Print parent process ID
    childprocess(n,arr);   // Call Bubble Sort function
    for(int i=0 ;i<n;i++){
    printf("%d\n",arr[i]);    // Print the sorted array
   
  }
    }
  else{
 // Code executed in the parent process (Quick Sort)
     wait(NULL);  // Wait for the child process to complete
     printf("We are in the parent process (Quick sort)\n");
     printf("Parent => PID: %d\n", getpid());   // Print parent process ID
     parentprocess(arr,0,n-1);   // Call Quick Sort function
     for(int i=0 ;i<n;i++){
     printf("%d\n",arr[i]);   // Print the sorted array
   
  }
 }
  
  return 0;
}
