//-----------------------------
// Brandon Delgado
// bdelgad3
// cse15
// November 27 2019
// IntegerQueue.c - pa4
// Node-based linked list ADT for Integer Queue
// Compile:  gcc –std=c-99 –Wall –o IntegerQueue IntegerQueue.c

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"IntegerQueue.h"
#define BREAKER_TEST_RANGE 1000
// Exported Type ----------------------------------------------------------------------

// NodeObj
// Exported reference type  
typedef struct NodeObj{
   int job;
   struct NodeObj *next;
} NodeObj;

// Constructors-Destructors -----------------------------------------------------------

// Node
// Constructor for the IntegerQueue ADT
typedef struct NodeObj *Node;

// newNode()
// Constructor for private Node type.
Node newNode(int x){
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->job = x;
   N->next = NULL;
   return N;
}
// freeNode()
// Deconstructor for private Node type.
void freeNode(Node *pN){
   if(*pN!=NULL && pN!=NULL){
      free(*pN);
      *pN = NULL;
   }
}
// IntegerQueueObj
typedef struct IntegerQueueObj{
   Node front; // front of the IntegerQueue
   Node back; // back of the IntegerQueue
   int items; // keeps count of the number of nodes in the list
}IntegerQueueObj;

// IntegerQueue
typedef struct IntegerQueueObj* IntegerQueue;

// newIntegerQueue()
// Constructor for IntegerQueue ADT.
IntegerQueue newIntegerQueue(){
   IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
   Q->front = NULL;
   Q->back = NULL;
   Q->items = 0; // keeps count of the items in the list
   return Q;
}

void freeIntegerQueue(IntegerQueue *pQ){
   if(*pQ!=NULL && pQ!=NULL){
      free(*pQ);
      *pQ = NULL;
   }
}
 
// ADT Operations --------------------------------------------------------------------

//isEmpty()
// Returns 1 (true) if Queue Q is empty, 0 (false) otherwise.
int isEmpty(IntegerQueue Q){
   if(Q->front==NULL){
      return 1;
   }
   else {
      return 0;
   }
}

// Length()
// Returns the number of elements of elements in Q
int length(IntegerQueue Q){
   if(Q==NULL){
      fprintf(stderr, "length() error: IntegerQueue is null");
      exit(EXIT_FAILURE);
   }
   return (Q->items);
}

// enqueue()
// Inserts x at back of Q.
void enqueue(IntegerQueue Q, int x){
   Node N = newNode(x);
   Node P;
   if(Q->front==NULL){
      Q->front = N;
      Q->back = N;
   }
   else{
      P = Q->back; // node that originally was in the back
      Q->back = N; // setting back to new Node
      N->next = Q->back; // new node points to the back
      P->next = N; // node that was originally in back points to the new node in the back
   }
   (Q->items)++;
}

// dequeue()
// Deletes and returns the item at front of Q.
// Pre: !isEmpty()
int dequeue(IntegerQueue Q){
   int x;
   Node N;
   if(isEmpty(Q) == 1){
      fprintf(stderr, "dequeue() error: IntegerQueue Q is empty.");
      exit(EXIT_FAILURE);
   }
   x = Q->front->job;
   N = Q->front;
   // executes if there is only one item in the list
   if(Q->front == Q->back){
      Q->front = Q->back = NULL;   
   }
   // executes when there is more than one item in the list
   else{
      Q->front = N->next;
   }
   (Q->items)--;
   freeNode(&N);
   return x;
}
// peek()
// Returns the item at front of Q.
// Pre: !isEmpty()
int peek(IntegerQueue Q){
   if(isEmpty(Q)==1){
   fprintf(stderr, "peek() error: IntegerQueue Q is empty.");
   exit(EXIT_FAILURE);
   }
   return Q->front->job;
}
// dequeueAll()
// Resets Q to the empty state.
void dequeueAll(IntegerQueue Q){ 
   if(Q==NULL){
      fprintf(stderr, "dequeueAll() error: IntegerQueue Q is empty.");
      exit(EXIT_FAILURE);
   }
   while(Q->items > 0){
      dequeue(Q);      
   }
   Q->front = Q->back = NULL;
}

// Other Operations -----------------------------------------------------------

// IntegerQueueToString()
// Determines a text representation of IntegerQueue Q. Returns a pointer to a 
// char array, allocated from heap memory, containing the integer sequence 
// represented by Q. The sequence is traversed from front to back, each integer
// is added to the string followed by a single space. The array is terminated 
// by a NUL '\n' character. It is the responsibility of the calling function to 
// free this heap memory.
char* IntegerQueueToString(IntegerQueue Q){
   Node N;
   char* seq;
   int i = 0;
   if(Q==NULL){
      fprintf(stderr, "IntegerToQueue error: IntegerQueue Q is empty.");
      exit(EXIT_FAILURE);
   }
   seq = calloc((Q->items*4), sizeof(char));
   N = Q->front;
   
   while(i < ((Q->items*4) - 1)){
        seq[i] = N->job + '0';
        seq[i+1] = '.';
        seq[i+2] = '0';
        seq[i+3] = ' ';
        N = N->next;
        i = i+4;
   }
   seq[((Q->items*4) - 1)] = '\0';
   return seq;
}

// equals()
// Returns true (1) if Q and R are matching sequences of integers, false (0) 
// otherwise.
int equals(IntegerQueue Q, IntegerQueue R){
   Node N, P;
   // both are NULL integer queues
   if(Q->front==NULL && R->front==NULL){
      return 1;
   }
   if(length(Q) != length(R)){
      return 0;
   }
   else {
      N = Q->front;
      P = R->front;
      while(N != Q->back && P!= R->back){
      if(N->job != P->job){
         return 0;
      }
      N = N->next;
      P = P->next;
      }
   }
   return 1; 
}


