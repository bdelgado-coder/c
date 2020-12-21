//-----------------------------
// Brandon Delgado
// bdelgad3
// cse15
// November 27 2019
// Simulation.c - pa4
// Integer Queue based simulation of m processors
// Compile:  gcc –std=c-99 –Wall –o Simulation Simulation.c
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Job.h"
#include"IntegerQueue.h"

//-----------------------------------------------------------------------------
// The following function may be of use in assembling the initial backup array.
// You may use it as is, alter it as you see fit, or delete it altogether.
//-----------------------------------------------------------------------------

// getjob()
// Reads two numbers from file in, and returns a new Job with those numbers
// as arrival and duration.
Job getJob(FILE* in){
   int a, d;
   fscanf(in, "%d %d\n", &a, &d);
   return newJob(a, d);
}

//-----------------------------------------------------------------------------
// The following stub for function main() contains a possible algorithm for 
// this project.  Follow it if you like.  Note that there are no instructions 
// included below for writing to either of the output files.  You must 
// intersperse those commands as necessary.
//-----------------------------------------------------------------------------

// main()
int main(int argc, char* argv[]){
   FILE *in, *trace, *report;   // handles for input and output files 
   int m; // number of jobs 
   int i; // for loop general variable
   int j; // for loop general variable 
   int k; // for loop general varibale 
   int n; // number of processors
   int time = 0; // variable for keeping track of time
   char* ttitle; // stores the title of the trace file
   char* rtitle; // stores the title of the report file
   Job* backup; // backup array - keeps track of original order of jobs
   IntegerQueue* Q; // array of IntegerQueues 
   
   // check command Q arguments
   if(argc != 2){
      printf("Usage: %s <input file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   // open files for reading and writing
   // open input file for reading 
   in = fopen(argv[1], "r");
   if( in==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }
   // setting the names for the output files
   ttitle = calloc(strlen(argv[1])+4, sizeof(char));
   rtitle = calloc(strlen(argv[1])+4, sizeof(char));

   for(i = 0; i < strlen(argv[1]); i++){
      ttitle[i] = argv[1][i];
   }

   for(i = 0; i < strlen(argv[1]); i++){
      rtitle[i] = argv[1][i];
   }

   ttitle[strlen(argv[1])] = '.';
   ttitle[strlen(argv[1])+1] = 't';
   ttitle[strlen(argv[1])+2] = 'r';
   ttitle[strlen(argv[1])+3] = 'c';

   rtitle[strlen(argv[1])] = '.';
   rtitle[strlen(argv[1])+1] = 'r';
   rtitle[strlen(argv[1])+2] = 'p';
   rtitle[strlen(argv[1])+3] = 't';

   // create trace file and open for writing
   trace = fopen(ttitle, "w");
   // create report file and open for writing
   report = fopen(rtitle, "w");
   
   if(trace == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create trace file.\n");
        exit(EXIT_FAILURE);
    }
    if(report == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create report file.\n");
        exit(EXIT_FAILURE);
    }
   
   // parses number of jobs from in file
   fscanf(in, "%d", &m);
   
   // allocating memory for the array of jobs 
   backup = calloc(m, sizeof(Job*));
   Q = calloc(m, sizeof(IntegerQueue*));

   // initializes each index of backup as Job
   for(i = 0; i < m; i++){
      backup[i] = malloc(sizeof(Job));
   }
   
   // initializes each index of Q as IntegerQueue
   for(i = 0; i < m; i++){
      Q[i] = newIntegerQueue();
   }

   // places jobs in backup array to keep track of their order
   for(i = 0; i < m; i++){
      backup[i] = getJob(in);
   }
   
   // loop: run simulation with n processors for n=1 to n=m-1 {
   for(i = 1; i <= m; i++){
      // number of processors is equal to i
      n = i; 
      // place Job indices from backup array into storage queue
      for(j = 0; j < m; j++){
      enqueue(Q[0], i);
      }
   //    loop: process all Jobs in this simulation {
      for(k = 0; k < m; k++){
   //       determine the time of the next arrival or finish event and update time
   //
   //       if any Jobs finish now, then complete them in the order they appear in 
   //       the queue array, i.e. lowest index first.
   //
   //       if any Jobs arrive now, then assign them to a processor queue 
   //       of minimum length and with lowest index in the queue array.
      }
   //    compute the total wait, maximum wait, and average wait for 
   //    all Jobs, then reset finish times for next simulation
   //
   }
   // end loop
   //
   // free all heap memory, close input and output files


   free(backup);
   free(Q);
   fclose(in);
   fclose(trace);
   fclose(report);
   return EXIT_SUCCESS;
}


