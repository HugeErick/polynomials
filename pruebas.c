//libraries used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// we are only working with max exponent 10
// GLOBAL VARS
#define MAX_TERMS 10
bool FIRST_TERM_HAS_MINUS = false;
bool FIRST_TERM_GONE = false;
int SIGNCOUNT = 0;

/*
 * Structure in order  to represent a term
 * why? Using a struct allows us to sort out the coefficients and 
 * the exponents and we need to use typedef in order to avoid repetition
 * so we can type "Term name_of_variable" AND this allows us to implement
 * the most important part of this which is to make AN ARRAY OF TERMS
 *
 * Term[];
 *
 * this allows us to store the coefficient and the exponent of equation
 */

typedef struct {
    int coefficient;  // Coeficient of term 
    int exponent;     // Exponent of term 
		char variable;
		char sign;
} Term; //name of the needed struct


//FUNCTIONS
void printSigns (Term* terms) {
		printf("\n %d \n", SIGNCOUNT);
}

// Function that splits the terms in the equation
// type is void because we dont need to return to user anything
void separateTerms(char* equation, Term* terms, int* numTerms) {
		int len = (strlen(equation) -1 );
		//we were debugging
		//printf("\n %d \n",len);
		if (equation[0] == 45) {
						FIRST_TERM_HAS_MINUS = true;
						equation++; // Move the equation pointer one character ahead
						len--; // Decrease the length of the equation by one
						SIGNCOUNT++;
		}

		for (int i = 0; i < len; i++) {
				// 43 ASCII = "+" and 45 ASCII = "-"
				if (equation[i] == 43 || equation[i] == 45) {
						char theSign = equation[i]; 
						terms[SIGNCOUNT].sign = theSign; 
						//we were debugging
						//printf("%c ", theSign);
						SIGNCOUNT++;
				}
		}

		// spliting with our delimeter being every "+-" of the equation given
		// i.e. every time it encounters a "+-" we SPLIT and therefero get all the individual terms 
		// we are getting the term string as a string pointer
    char* termStr = strtok(equation, "+-");
		// while loop in order to achieve the following: 
    while (termStr != NULL) {
				// we declare two local variables 
        int coefficient, exponent; //acts like a temp variable
				char variable;
				// we need to use sscanf to READ the values and assign them to our local variables  
				// why? because we have a string and scanf doesn work with strings
				// this regex "%dx^%d" is the format 
        sscanf(termStr, "%d%c^%d", &coefficient, &variable, &exponent);

				/*
				 * The read values are assigned to the corresponding members of the terms
				 * structure at position *numTerms. The * operator is used to get the current
				 * value of numTerms and access the correct position in the terms array.
				 */
        terms[*numTerms].coefficient = coefficient;
				terms[*numTerms].variable = variable;
        terms[*numTerms].exponent = exponent;
        (*numTerms)++;

				// we use strtok to get the next term
				/*
				 * By the way, if we want the function to keep
				 * splitting our string; in the following calls
				 * to it we must not pass the string (but NULL)
				 * , and also the delimiters.
				 */
        termStr = strtok(NULL, "+-");
    }
}

// Function in order to print the matrix
void printMatrix(Term* terms, int numTerms) {
		//add a line to be more clean
		printf("\n");
    int matrix[10][10] = {0};  // Matriz para almacenar los coeficientes

		// Filling matrix
    for (int i = 0, j = 0; i < numTerms; i++) {
        int exponent = terms[i].exponent;
        int coefficient = terms[i].coefficient;
				char sign = terms[j].sign;
				if (FIRST_TERM_HAS_MINUS) {
						j++;
						int negativeCoefficient = coefficient * -1;
						matrix[exponent][terms[i].variable - 'a'] += negativeCoefficient;
						FIRST_TERM_HAS_MINUS = false;
						FIRST_TERM_GONE = true;
				} else if (FIRST_TERM_GONE) {
						j++;
						if (sign == 45) {
								int negativeCoefficient = coefficient * -1;
								matrix[exponent][terms[i].variable - 'a'] += negativeCoefficient;
						} else {
								matrix[exponent][terms[i].variable - 'a'] += coefficient;
						}
				} else {
						matrix[exponent][terms[i].variable - 'a'] += coefficient;
						FIRST_TERM_GONE = true;
				}  
    }

		//actually printing the matrix
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// main function where u just simply ask for inputs and print the arrays
int main() {
    char equation[100];
    printf("Please give equation with the following \"2x^3 + 3xy^2 - 5\"\n");
		//printf("If u are going to put a term with exponent one please use \"x^1\"\n");
		// read string input
    fgets(equation, sizeof(equation), stdin);

		//this of course will add more depending on the input
    int numTerms = 0;
    Term terms[MAX_TERMS];

		// calling functions
    separateTerms(equation, terms, &numTerms);
    printMatrix(terms, numTerms);
		//printSigns(terms);

    return 0;
}


