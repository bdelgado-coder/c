//-----------------------------------------------------------------------------
// Brandon Delgado, bdelgad3
// 2020 Spring CSE101 PA1
// Lex.c
// Source file for manipulating List ADT to sort in* file
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

int main(int argc, char *argv[])
{
   FILE *in, *out;
   List L = NULL;
   char **A;
   char inChar;
   int n = 0;
   int i = 0;
   int j = 0;
   int k = 0;
   int dupl = 0;

   // Check if number of command line arguments is 3.
   if (argc != 3)
   {
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // Open input file for reading
   in = fopen(argv[1], "r");
   if (in == NULL)
   {
      fprintf(stderr, "Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // Reading through file for newline characters to count lines
   while ((inChar = fgetc(in)) != EOF)
   {
      if (inChar == '\n')
      {
         n++;
      }
   }

   // Resets the file pointer to the beggining of the in file
   rewind(in);

   // Open output file for writing
   out = fopen(argv[2], "w");
   if (out == NULL)
   {
      fprintf(stderr, "Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // Allocate array of char array of size n
   A = calloc(n, sizeof(char *));

   // Allocate memory for each char array
   for (i = 0; i < n; i++)
   {
      A[i] = calloc(256, sizeof(char));
   }

   // Collects each line as a string and stores at i index of str array
   for (i = 0; i < n; i++)
   {
      fgets(&A[i][0], 256, in);
   }

   // Allocate memory for new List L
   L = newList();

   // Inserts first index of the string array, Index 0
   prepend(L, 0);

   for (i = 1; i < n; i++)
   {
      // Resets cursor for the while loop
      moveFront(L);

      while (index(L) != -1)
      {

         // True if and only if s1 comes before s2
         if (strcmp(A[i], A[get(L)]) < 0)
         {
            insertBefore(L, i);
            break;
         }
         // True if and only if s1 equals s2
         if (strcmp(A[i], A[get(L)]) == 0)
         {

            // Check if list has duplicate string, if not, do not insertBefore().
            for (j = 0; j < n; j++)
            {

               for (k = 0; k < n; k++)
               {

                  if (strcmp(A[j], A[k]) == 0)
                  {
                     dupl++;
                  }
               }
            }
            if (dupl > n)
            {
               insertBefore(L, i);
               dupl = 0;
               break;
            }
         }
         moveNext(L);
         // If cursor reaches the end of list, append the element
         if (index(L) == -1)
         {
            append(L, i);
         }
      }
   }
   // Prints out the alphabetized list to the out file
   // Itterates through linked list, and prints the strings
   // in the order that they appear in the list
   moveFront(L);
   while (index(L) != -1)
   {
      fprintf(out, "%s", A[get(L)]);
      moveNext(L);
   }
   // Close in and out file
   fclose(in);
   fclose(out);
   // Frees memory for each char array within the arrays of strings
   for (i = 0; i < n; i++)
   {
      free(A[i]);
   }
   // Frees memory for string array and List
   free(A);
   freeList(&L);

   return EXIT_SUCCESS;
}