//	Brandon Delgado
//	bdelgad3
//	cse15
//	26 October 2019
//	Finds solutions to n-Queens on a (n+1)*(n+1) board, and either prints number of solutions or prints board	 
//	
//	Compile:  gcc –std=c-99 –Wall –o Queens Queens.c
//	Run: Queens int n [-v]

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_ARRAY_SIZE 15
#define MAX_SIZE 100

// prototype functions
void placeQueen(int** B, int n, int i, int j);

void removeQueen(int** B, int n, int i, int j);

void printBoard(int** B, int n);

int findSolutions(int** B, int n, int i, char *mode);

// function main that reads command line arguments and while determine whether to run in verbose or normal mode
int main(int argc, char* argv[]) {

	char *mode; // tells findSolutions if running in normal mode or verbose mode
	int q = 0; // will store either the ints 1 or 2, in order to use for swtiches
	int n = 0; // stores number of rows and columns (n+1)x(n+1)
	int i = 1; // findsSolution beginning at row 1
	int **B; // array that will store int pointers that point int values, in order to a form a "2D" array

	// check for correct number of arguements
	
	if(argc == 3) { // verbose mode
		
		if(strcmp(argv[1], "-v") == 0) { // check for verbose command "-v"
			for(i = 0; argv[2][i] != 0; i++) {
				if(isdigit(argv[2][i]) != 0) {
					if((n >= 1) || (n <= 15)) {
						n = atoi(argv[2]);	// convert string to int
						q = 2;
					}
					else {
						fprintf(stderr, "Usage: Queens [-v] number\n");
						fprintf(stderr, "Option: -v verbose output, print all solutions\n");
						exit(EXIT_FAILURE);	
					}
				}
				else {
					fprintf(stderr, "Usage: Queens [-v] number\n");
					fprintf(stderr, "Option: -v verbose output, print all solutions\n");
					exit(EXIT_FAILURE);	
				}		
			}
		}
		else {
			fprintf(stderr, "Usage: Queens [-v] number\n");
			fprintf(stderr, "Option: -v verbose output, print all solutions\n");
			exit(EXIT_FAILURE);	
		}
	}

	else if(argc == 2) { // normal mode
		for(i = 0; argv[1][i] != 0; i++) {
			if(isdigit(argv[1][i]) != 0) {
				if((n >= 1) || (n <= 15)) {
					n = atoi(argv[1]);
					q = 1;
				}
				else {
					fprintf(stderr, "Usage: Queens [-v] number\n");
					fprintf(stderr, "Option: -v verbose output, print all solutions\n");
					exit(EXIT_FAILURE);	
				}
			}
			else {
			fprintf(stderr, "Usage: Queens [-v] number\n");
			fprintf(stderr, "Option: -v verbose output, print all solutions\n");
			exit(EXIT_FAILURE);	
			}
		}
	}

	else {
		fprintf(stderr, "Usage: Queens [-v] number\n");
		fprintf(stderr, "Option: -v verbose output, print all solutions\n");
		exit(EXIT_FAILURE);	
	}

	// switches that resume the program in either normal mode (q=1) or verbose mode (q=2)
	switch (q)  
	{
		case 1: // normal mode
			B = calloc(n+1,sizeof(int*)); // allocates memory for pointer of pointer array
			
			for(int i = 0; i <= n; i++) {
				B[i] = calloc(n+1,sizeof(int)); // allocates memory for array of ints
			}

			break;

		case 2: // verbose mode
			B = calloc(n+1,sizeof(int*)); // allocates memory for pointer 

			for(int i = 0; i <= n; i++) {
				B[i] = calloc(n+1,sizeof(int)); // allocates memory for array of ints
			}

			mode = calloc(MAX_SIZE, sizeof(char*)); // allocates 5 elements to mode char* array
 			strcpy(mode, "verbose"); // set mode to "verbose"
			break; 
	}

	findSolutions(B, n, i, mode);
	printf("%d-Queens has %d solutions\n", n, findSolutions(B, n, i, mode));
	free(B);

	for(int i = 1; i <= n; i++) {
		free(B[i]);
	}
	
	return EXIT_SUCCESS;
	}
	

	int findSolutions(int** B, int n, int i, char *mode) { // high level function that calls other sub-level functions 
		int sum = 0;
		
		if(i > n) {
			if(strcmp(mode, "verbose") == 0) { // checks for verbose mode
				printBoard(B, n);
			}
		return 1;
		}
			
		else {
			for(int j = 1; j <= n; j++) {
				if(B[i][j] == 0) {
					placeQueen(B, n, i, j);
					sum += findSolutions(B, n, i+1, mode);
					removeQueen(B, n, i, j);
				}
			}
		}
		return sum;
	}

	void placeQueen(int** B, int n, int i, int j){ 
		int k = i+1;
		int l = j;

		B[i][j] = 1; // indicates there is a queen
		B[i][0] = j; // indicates on which column there is a queen

		// indicates box is not safe vertically 
		for(;k <= n; k++) {
			B[k][l]--;
			
		}
		
		k = i+1;
		l = j+1;

		// indicates box is not safe diagonally-right
		for(;k <= n && l <= n; k++) {
			B[k][l]--; // decrements value at 
			l++;
		}
	
		k = i+1;
		l =	j-1;
		// indicates box is not safe diagonally-left
		for(;k <= n && l > 0; k++) {
			B[k][l]--;
			l--;
		}
	}

	void removeQueen(int** B, int n, int i, int j){
		int k = i+1;
		int l = j;

		B[i][j] = 0; // removes a queen
		B[i][0] = 0; // removes column indicator

		// indicates box is safe vertically 
		for(;k <= n; k++) {
			B[k][l]++;			
		}
		
		k = i+1;
		l = j+1;

		// indicates box is safe diagonally-right
		for(;k <= n && l <= n; k++) {
			B[k][l]++; // decrements value at 
			l++;
		}
	
		k = i+1;
		l =	j-1;
		// indicates box is safe diagonally-left
		for(;k <= n && l > 0; k++) {
			B[k][l]++;
			l--;
		}
	}

	void printBoard(int** B, int n) {
		printf("(");
		
		for(int i = 1; i <= n; i++) {	// itterates through 2D array and prints solutions for each row
			printf("%d", B[i][0]);
			
			if(i < n) {
				printf(", ");
			}

		}
		printf(")\n");
	}
