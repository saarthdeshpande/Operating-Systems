#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include<iostream>
using namespace std;

#define SIZE 10

int A[SIZE][SIZE], B[SIZE][SIZE];
long int C[SIZE][SIZE];

void *mul_thread(void *arg)
{
  int *rcArgs = (int *) arg;
	long int return_val = 0;

	int row = rcArgs[0], col = rcArgs[1], k	= rcArgs[2];
	// printf("\n[ Thread %d-%d ] - Joined",row+1,col+1);
	for(int i = 0;i < k;i++)
	{
		return_val += A[row][i] * B[i][col];
		printf("\n[ Thread %d-%d ] - Calculated %d x %d = %d ----> %ld",row+1,col+1,A[row][i],B[i][col],A[row][i]*B[i][col],return_val);
		int z = rand()%10;
		printf("\n[ Thread %d-%d ] - Paused. Sleeping for %d seconds.",row+1,col+1,z);
		sleep(z);
		printf("\n[ Thread %d-%d ] - Resumed.", row+1,col+1);
	}
	printf("\n[ Thread %d-%d ] - Exiting.", row+1,col+1);
	pthread_exit((void *) return_val);
}

void display_matrix(int M[SIZE][SIZE], int rows, int cols)
{
	printf("\n");
	for(int i = 0;i < rows;i++) {
		for(int j = 0;j < cols;j++)
			printf("%d  ",M[i][j]);
		printf("\n");
	}
}

int main() {
	int rcArgs[3], *status, r1, c1 = 1, r2 = 0, c2;
	pthread_t P[SIZE][SIZE];

  while (c1 != r2) {
    cout << "Matrix A:\nRows: ";
    cin >> r1;
    cout << "Columns: ";
    cin >> c1;
    cout << "\nMatrix B:\nRows: ";
    cin >> r2;
    cout << "Columns: ";
    cin >> c2;
  }
  cout << "\nElements of Matrix A:\n";
  for (int i = 0; i < r1; i++)
    for (int j = 0; j < c1; j++)
      cin >> A[i][j];

  cout << "\nElements of Matrix B:\n";
  for (int i = 0; i < r2; i++)
    for (int j = 0; j < c2; j++)
      cin >> B[i][j];


	for(int i = 0;i < r1;i++) {
		for(int j = 0;j < c2;j++) {
			rcArgs[0] = i;
			rcArgs[1] = j;
			rcArgs[2] = c1;

			if(pthread_create(&P[i][j], NULL, mul_thread, rcArgs) != 0)
				printf("\nCannot create thread.\n");
			else {
				printf("\n[ Thread %d-%d ] - Created",i + 1,j + 1);
				sleep(2);
			}
		}
	}

	printf("\n\nMatrix A:");
	display_matrix(A, r1, c1);
	printf("\nMatrix B:");
	display_matrix(B, r2, c2);

	for(int i = 0;i < r1;i++) {
		for(int j = 0;j < c2;j++) {
				if(pthread_join(P[i][j],(void **) &status) != 0)
					perror("\nThread join failed.\n");
        else
          printf("\n[ Thread %d-%d ] - Joined", i + 1, j + 1);
				C[i][j] = (long int)status;
		}
	}

	printf("\n\nResultant Matrix:\n");
	for(int i = 0;i < r1;i++) {
		for(int j = 0;j < c2;j++){
			printf("%ld  ",C[i][j]);
		}
		printf("\n");
	}
	exit(EXIT_SUCCESS);
}
