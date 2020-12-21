/*
#  Subset.c
#  Uses a recursive method to print out all possible element subsets of a given set
#  CruzID: bdelgad3
#  Class: CSE15
#  Date: 11 October 2019
#  Compile: make
#  Run: Subset n k   
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX_SIZE 100

void printSet(int B[], int n) { // B[0] is ignored for sake of program, begin at B[1]
  printf("{");
  int tripwire = 0; // number of commas
  int count = 0; // number of elements
  int i;
  char* str = "{";
  for(int j = 1; j < n+1; j++){
    if(B[j] == 1){
      
      //strcat(str, j);
      //strcat(str, ", ");
      if(tripwire < count && count > 0){
        printf(", ");
      }
      printf("%d", j);
      count++;
      

    }
    
  }
  printf("}");
  printf("\n");
  /*
  for(i = 1; i <= MAX_SIZE; i++) {
    if((B[i] == 1) || (tripwire == 1)) {
      printf("%d", i);
      tripwire = 1;
    }
    else {
      printf(", ");
    }
  }
  if ((tripwire == 0) && (B[i] == 0)){
      printf(" } \n");
    }
    else {
      printf("} \n");
    }*/
}

void printSubsets(int B[], int n, int k, int i) {
  if(k == 0 || k == n) {
      printSet(B,n);
    } 
  else if(k > (n-i+1)) {
    return;
  }
  else {
    B[i] = 1; // left side branch
    printSubsets(B, n, k-1, i+1);
    B[i] = 0; // right side branch
    printSubsets(B, n, k, i+1);
  }
}

int main(int argc, char* argv[]) {
  int n; // number of distinct items
  int k;
  int i = 1;
  char *argtemp1; // temp string array where the argv1 will be stored
  char *argtemp2; 

  if(argc == 3) { // checks to see if there are a valid amount of arguments
    argtemp1 = argv[1]; // converts command line argument into string
    argtemp2 = argv[2];
    n = atoi(argv[1]); // converts string into int
    k = atoi(argv[2]);
  }
  else {
    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100");
    return EXIT_SUCCESS;
  }
  if(n > 100) {
    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100");
    return EXIT_SUCCESS;
  }
  else if(k > 100) {
    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100");
    return EXIT_SUCCESS;
  }
  else if(n < 0) {
    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100");
    return EXIT_SUCCESS;
  }
  else if(k < 0) {
    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100");
    return EXIT_SUCCESS;
  }
  else if(n < k) {
    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100");
    return EXIT_SUCCESS;
  }
  else {
    int B[MAX_SIZE+1]; // initialize int array
    for(int i = 1; i < MAX_SIZE+1; i++) {
      B[i] = 0;
    }
    printSubsets(B, n, k, i);
  }
}  