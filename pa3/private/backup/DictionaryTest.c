//------------------------------------------
// Brandon Delgado
// bdelgad3
// cse15
// 12 November 2019
// DictionaryTestClient.c
// Exercises different parts of Dictionary.c 
//------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Dictionary.h"

int main() {
   Dictionary D = newDictionary(); // creating new dictionary
   insert(D, "1", "blah");
   printf("value at key 1 is: %s\n", lookup(D,"1"));
   
   if(size(D) == 1)
   printf("size of dictionary is 1\n");
   
   insert(D, "2", "blah the sequel");
   
   if(size(D) == 2)
   printf("size of dictionary is 2\n");

   delete(D, "1");

   if(size(D) == 1)
   printf("size of dictionary is 1\n");

   insert(D, "3", "awdasdasd");
   insert(D, "4", "awdasdasd");
   delete(D,"4");

   printf("Size is %d\n", size(D));


   // if(size(D) == 1)
   //    printf("asserted that dictionary is of size 1\n");
   // makeEmpty(D);
   // if(size(D) == 0)
   //    printf("asserted that dictionary is of size 0\n");
   
   
   // printf("There are %d chars in the Dictionary\n", countChars(D));
   printf("%s\n",DictionaryToString(D));
   freeDictionary(&D);
   return EXIT_SUCCESS;
}