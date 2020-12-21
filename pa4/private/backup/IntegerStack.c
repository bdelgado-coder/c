// Brandon Delgado
// bdelgad3
// cse15
// 1 November 2019
// IntegerStack.c
// Array based implementation of Integer Stack ADT in C
// Compile:  gcc –std=c-99 –Wall –o IntegerStack IntegerStack.c

#include<stdio.h>
#include<stdlib.h>
#include"IntegerStack.h"

// Private Types and Functions ------------------------------------------------

// InitialSize
static const int InitialSize = 1;

// IntegerStackObj
typedef struct IntegerStackObj{
   int* item;         // array of IntegerStack items
   int numItems;      // number of items in this IntegerStack
   int physicalSize;  // current length of underlying array
} IntegerStackObj;

// doubleItemArray
// Doubles the physical size of the underlying array L->item.
void doubleItemArray(IntegerStack S){
   int i;
   int* newArray;
   int* oldArray = S->item;
   S->physicalSize *= 2;
   newArray = calloc(S->physicalSize, sizeof(int));
   for( i=0; i<(S->numItems); i -= -1){
      newArray[i] = oldArray[i];
   }
   S->item = newArray;
   free(oldArray);
}

// Constructors-Destructors ---------------------------------------------------

// newIntegerStack()
// Constructor for the IntegerStack ADT
IntegerStack newIntegerStack(){
   IntegerStack S = malloc(sizeof(IntegerStackObj));
   S->item = calloc(InitialSize, sizeof(int));
   S->numItems = 0;
   S->physicalSize = InitialSize;
   return S;
}

// freeIntegerStack()
// Destructor for the List ADT
void freeIntegerStack(IntegerStack* pS){
   if( pS!=NULL && *pS!=NULL ){
      free((*pS)->item);
      free(*pS);
      *pS = NULL;
   }
}

// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Stack S is empty, 0 (false) otherwise
int isEmpty(IntegerStack S){
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   return (S->numItems == 0);
}

// push()
// Inserts int x at top of S
void push(IntegerStack S, int x){
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: add() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   // increase physical size of array if necessary
   if( (S->numItems)==(S->physicalSize) ){
      doubleItemArray(S);
   }
   S->item[(S->numItems)] = x;
   S->numItems++;
}  

// pop()
// Pops integer at top and returns integer at top S
// Pre: !isEmpty(S)
int pop(IntegerStack S){
   if( isEmpty(S) == 1 ){
      fprintf(stderr, "IntegerStack Error: delete() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   S->numItems--;
   return S->item[S->numItems];
   
   
}

// peek()
// Returns integer at top S
// Pre: !isEmpty(S)
int peek(IntegerStack S) {
   if( isEmpty(S) == 1 ){
      fprintf(stderr, "IntegerStack Error: popAll() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   return S->item[S->numItems-1]; // returns integer at top
}

// popAll()
// Reset S to the empty state
void popAll(IntegerStack S){
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: popAll() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   S->numItems = 0;
} 


// Other Operations -----------------------------------------------------------

// printIntegerStack()
// Prints a space separated list of items in S to file stream pointed to by out
void printIntegerStack(FILE* out, IntegerStack S){
   int i;
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: printIntegerStack() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   for( i=(S->numItems-1); i>=0; i--){
      fprintf(out, "%d ", S->item[i] );
      // fprintf(out, "%d \n", i );
   }
   fprintf(out, "\n");
}

// equals()
// Returns true (1) if S and T are matching sequences of integers, false (0) 
// otherwise
int equals(IntegerStack S, IntegerStack T){
   int i, eq;
   if( S==NULL || T==NULL ){ 
      fprintf(stderr, "IntegerStack Error: equals() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   eq = ( (S->numItems)==(T->numItems) );
   for( i=1; eq && i<=(S->numItems); i++){
      eq = ( (S->item[i])==(T->item[i]) );
   }
   return eq;
}
