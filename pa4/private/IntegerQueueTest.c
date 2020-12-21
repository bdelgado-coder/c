//-----------------------------
// Brandon Delgado
// bdelgad3
// cse15
// November 27 2019
// IntegerQueueTest.c - pa4
// Integer Queue exercises
// Compile:  gcc –std=c-99 –Wall –o IntegerQueueTest IntegerQueueTest.c

#include<stdio.h>
#include<stdlib.h>
#include"IntegerQueue.h"

int main(){
   IntegerQueue Q = newIntegerQueue();
   IntegerQueue R = newIntegerQueue();
   
   if(isEmpty(Q) == 1){
      printf("IntegerQueue Q is Empty\n");
   }

   if(isEmpty(R) == 1){
      printf("IntegerQueue R is Empty\n");
   }

   enqueue(Q,1);
   enqueue(Q,2);

   enqueue(R,1);
   enqueue(R,2);

   if(equals(Q,R) == 1){
      printf("IntegerQueues Q & R are equal");
   }

   dequeue(R);

   if(equals(Q,R) == 0){
      printf("IntegerQueues Q & R are not equal");
   }

   printf("Length of Q: %d\n Length of R: %d\n", length(Q), length(R));

   if(peek(Q) != peek(R)){
      printf("Front values not equal in Q and R");
   }

   dequeueAll(Q);

   if(equals(Q,R) == 0){
      printf("IntegerQueues Q & R are not equal");
   }

   printf("IntegerQueue Q contains: %s", IntegerQueueToString(Q));
   printf("IntegerQueue R contains: %s", IntegerQueueToString(R));

   dequeueAll(R);

   freeIntegerQueue(Q);
   freeIntegerQueue(R);

   return EXIT_SUCCESS;

}
