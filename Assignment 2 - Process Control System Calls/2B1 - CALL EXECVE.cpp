#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

void bubbleSort(int *array, int n)
{
	for (int i = 0; i < n - 1;i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (array[j] > array[j + 1]) {
				int swap = array[j];
				array[j] = array[j + 1];
				array[j + 1] = swap;
			}
		}
	}
}

int main()
{
	int a[15],n;
	char *arg[10],str[15],*str2;
	cout << "Size of array: ";
	cin >> n;
	cout << "Elements of array: ";
	for(int i = 0;i < n;i++)
		cin >> a[i];
	cout << "In Parent Process: " << getpid() << endl;
	cout << "\nSorting Numbers\n";
	bubbleSort(a,n);
	pid_t id = fork();
	if(id == 0)
	{
		cout << "In Child Process: " << getpid() << endl;
		printf("\nSorted Numbers: ");
		for(int i = 0;i < n;i++)
		{
			sprintf(str, "%d", a[i]);
			arg[i] = new char;
			strcpy(arg[i], str);
		}

		arg[n] = NULL;

		for(int i = 0;i < n;i++)
			cout << arg[i] << " ";
		cout << endl;

		cout << "\nExecuting execve.\n";
		execve("./2b2",arg,NULL);
		cout << "\nExecve completed.\n";
		cout << "\nChild Process completed. Child exiting.\n";
	}
	else if(id > 0)
	{
		cout << "\nIn Parent process. Waiting.\n";
		wait(0);
		cout << "\nParent execution complete. Exiting.\n";
	}
	return 0;
}
