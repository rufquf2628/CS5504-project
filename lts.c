#include <stdio.h>
#include <stdlib.h>


#define num 8 //128 //matrix size

//clock_t start, end;
//double cpu_time_used; //cannot use time.h in syscall emulation mode of GEM5. Must check the time in stats.txt 

void lts(int**  mat_A , int* unknowns, int* vector_array, int N)
{
  //first row has just one element, so solve the corresponding unknown directly
	unknowns[0]= vector_array[0];
  //rest of the unknowns
	for (int i = 1; i < N; i++) {
		int sum =0;
    for (int  j= 0; j < i; j++) {
      sum += mat_A[i][j]*unknowns[j];
		}
		unknowns[i] = vector_array[i] - sum; //ideally should be x[i]=  (y[i] - sum)/mat[i][i], but we are generating matices with diagonal elements =1
  }
  return;
}
 

int main (int argc, char *argv[])

{

  printf("Generating matrix of size %d * %d \n",num,num);
  int **mat_A = (int **)malloc(num * sizeof(int *)); 
  int *unknowns = (int *)malloc(num * sizeof(int));
  int *vector_data = (int *)malloc(num * sizeof(int));
  
  for (int i=0; i<num; i++){ 
    mat_A[i] = (int *)malloc(num * sizeof(int)); 
  }
 
  for( int i=0; i<num; i++){
	vector_data[i]=1;       //set all elements to one. 
	unknowns[i]=0;
  	for(int j=0; j<num; j++){
  		if (j<i)
  			mat_A[i][j]= i-j; //syscalls for rng are not implemented, just use a function of i and j to create the data
  		if (j==i)
  			mat_A[i][j]= 1;   //set diags to 1
  		if (j>i)
  			mat_A[i][j]= 0;   //we are generating lower triangular matrix, set all elements above diagonal to 0
  	}
  }
  
  printf("computing the results\n");

  lts(mat_A, unknowns, vector_data, num);
  
  
  printf("printng A \n");
  for (int i = 0; i < num; i++) {
      for (int j = 0; j < num; j++) {	
		printf("%d ", mat_A[i][j]);
		}
	 printf("\n");
 	}
  printf("\n");
  for (int j = 0; j < num; j++) {	
		printf("%d ", unknowns[j]);
		}
  printf("\n");   	
  
  
  for (int i=0; i<num; i++)
  {
   free(mat_A[i]);
  }

   free(mat_A);
   free(unknowns);
   free(vector_data);
   //free(product_opt);
  return (0);

}

