#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void bub_asc(int *arr, int n) {
  for (int i = 0;i < n - 1;i++) {
    for (int j = 0; j < n - i - 1;j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

void bub_desc(int *arr, int n) {
  for (int i = 0;i < n - 1;i++) {
    for (int j = 0; j < n - i - 1;j++) {
      if (arr[j] < arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}

int main() {
  int n;
  cout << "Number of elements in array: ";
  cin >> n;
  int arr[n];
  cout << "\nEnter array: ";
  for(int i = 0;i < n;i++) {
    cin >> arr[i];
  }
  int pid = fork();
  if (pid == 0) {
    cout << "\n\nCHILD PROCESS\n\nChild ID: " << getpid() << "\nParent ID: " << getppid() << endl;
    cout << "\nChild going to sleep.\n\n";
    sleep(10);
    bub_asc(arr, n);
    cout << "\nAscending Child Sort: ";
    for(int element: arr) {
      cout << element << " ";
    }
    cout << endl;
  }
  else {
    cout << "\nPARENT PROCESS\n\nMy ID: " << getpid() << endl;
    bub_desc(arr, n);
    cout << "\nDescending Parent Sort: \n";
    for(int element: arr) {
      cout << element << " ";
    }
    cout << endl;
    wait(0);
    cout << "\n\nParent process completed. Exiting now.\n";
    exit(0);
  }

  return 0;
}
