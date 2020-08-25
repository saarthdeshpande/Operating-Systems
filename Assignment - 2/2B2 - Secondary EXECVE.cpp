#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

int main(int argc, char* argv[])
{

	int a[10], key, flag = 0;

	cout << "\nIn Parent Process of Searching Code\n" << getpid();
  cout << "\nReceived sorted array: \n";
  for(int i = 0;i < argc;i++)
    cout << argv[i] << " ";
  cout << endl;

	for(int i = 0;i < argc;i++)
		a[i] = atoi(argv[i]);

  cout << "\nInterger type sorted array:\n";
	for(int i = 0;i < argc;i++)
    cout << a[i] << " ";
  cout << endl;
	
	cout << "Enter number to search: ";
  cin >> key;

  int l = 0,u = argc - 1, mid;
	while(l <= u)	{
    mid = (l + u) / 2;
    if(key == a[mid])	{
   		flag = 1;
   		break;
   	} else if(key < a[mid]) {
   		 u = mid - 1;
   	  } else {
     		l = mid + 1;
	 	    }
	}
	if(flag == 0)
    	cout << "\nNumber not found.\n";
	else
     	cout << "\nNumber found.\n";

	return 0;
}
