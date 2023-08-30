//Made By Erick Parada & Andre Francois 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//GLOBAL VARIABLES
bool FIRST_TERM_HAS_MINUS = false;
int signs[10];
//matrix A
int matrix_1[11][11];
//matrix B
int matrix_2[11][11];
/*
 * This struct is very important, we can store in Term the coefficient
 * the exponents and the two variables used, typedef is for more readability
 * so we can create an array of the struct as an array of Terms 
 */
typedef struct {
		int coefficient;
		int variable_exponent1;
		int variable_exponent2;
		char first_variable;
		char second_variable;
} Term;

void print_the_matrix(Term* terms, int num_of_terms,int matrix[11][11]) {
		// bool to identify when the first term was already processed 
		// we need to know this because the first term can or can not
		// be negative, in both cases is very important to recognice 
		// that the first term is not being evaluated anymore
		bool FIRST_TERM_GONE = false;
		printf("\n");
		for (int i = 1; i < 1; i++) {
		printf("Num: %d\n", terms[i].coefficient );
		printf("var1: %c\n", terms[0].first_variable );
		printf("var2: %c\n", terms[0].second_variable);
		printf("exp1: %d\n", terms[i].variable_exponent1);
		printf("exp2: %d\n", terms[i].variable_exponent2);
		}
		printf("\n");
		int temp_matrix[11][11] = {0};

		// filling matrix with all the info we have of the terms
		for (int i = 0, j = 0; i < num_of_terms; i++) {
				// assigning term values to local variables
				int exponent_var1 = terms[i].variable_exponent1;
				int exponent_var2 = terms[i].variable_exponent2;
				int coefficient = terms[i].coefficient;
				
				// when the first term is minus we have to adjust the index of the signs
				// the signs work with a different index because we can have x + y - a
				// where terms are 3 but signs there are two explicit signs
				if (FIRST_TERM_HAS_MINUS) {
						puts("first term has minus");
						j++;
						// as we need the negative of the coefficient the trick here is to 
						// multiply by -1
						int negative_coefficient = coefficient * -1;
						temp_matrix[exponent_var1][exponent_var2] = negative_coefficient;
						FIRST_TERM_HAS_MINUS = false;
						FIRST_TERM_GONE = true;
						// the critical first term is gone now the sign must be explicit
				} else if (FIRST_TERM_GONE) {
						// if negative
						if (signs[j] == 2) {
								int negative_coefficient = coefficient * -1;
								temp_matrix[exponent_var1][exponent_var2] = negative_coefficient;
						// else is positive
						} else {
								temp_matrix[exponent_var1][exponent_var2] = coefficient;
						}
						j++;
				} else {
						// and finaly this else is for when the first term is just positive
						puts("first term is positive");
						temp_matrix[exponent_var1][exponent_var2] = coefficient;
						FIRST_TERM_GONE = true;
				}
		}
		// assigning matrix with the numbers finaly processed
		for (int i = 0; i < 11; i ++){
				for (int j = 0; j < 11; j++) {
						matrix[i][j] = temp_matrix[i][j];
						printf("%d\t", matrix[i][j]);
				}
				printf("\n");
		}
}

// now comes the actuall big part: the input whole processing 
// we first process the input #see process_input function
// after we adjust the input we can peacefuly
// process a more simple term each time
void process_polynomial(char* raw_equation, Term* terms, int* num_of_terms) {
		int count_raw_terms = 0;
		// raw term consist of the term separated by the signs,
		// meaning that we only have the coefficient, the variables
		// and the exponents
		printf("\n %s \n", raw_equation);
		char* raw_term = strtok(raw_equation, "+-"); 

		while (raw_term != NULL) {
				// this clean term it's purpose is to exist withouth
				// the explicit coefficient if there is one explicit coefficient 
				char clean_term[50] = "";
				// local var to add the corresponding coefficient
				int get_coefficient = 0;
				// index of raw terms 
				count_raw_terms++;

				// gathering all the information when the case where we have an explicit
				// constant and it's variable
				if (isdigit(raw_term[0]) && (raw_term[1] == terms[0].first_variable ||
										raw_term[1] == terms[0].second_variable) ) { // e.g. case 8x
																																 
						get_coefficient += atoi(&raw_term[0]);
						terms[*num_of_terms].coefficient = get_coefficient; 
						terms[*num_of_terms].variable_exponent2 = 0;
						// here we remove the coefficient to have the clean_term with just 
						// the variables (and it's exponents)
						for (int i = 1, j = 0; i < (strlen(raw_term)); i++, j++)
								clean_term[j] = raw_term[i];

						// algorithm to extract exponents no matter the order of the variables
						// also if a variable is not writted meaning ^0 we also are aware of that
						for (int i = 0; i < (strlen(clean_term)); i++) {
								if (clean_term[i] == terms[0].first_variable) {
										if (clean_term[i + 1] == '^') {
												// assigning explicit exponent to first variable exponent
												sscanf(clean_term +  i + 2, "%d", &terms[*num_of_terms].variable_exponent1);
										} else {
												terms[*num_of_terms].variable_exponent1 = 1;
										}
								} else if (clean_term[i] == terms[0].second_variable) {
										if (clean_term[i + 1] == '^') {
												// assigning explicit exponent to second...
												sscanf(clean_term +  i + 2, "%d", &terms[*num_of_terms].variable_exponent2);
										} else {
												terms[*num_of_terms].variable_exponent2 = 1;
										}
								}
						}
						printf("Clean term:%s\n", clean_term);
					// case when we don't have an explicit coefficient but we have
					// the varibale so coefficient = 1
				} else if (isalpha(raw_term[0])) { //case e.g. xy
						get_coefficient = 1;
						terms[*num_of_terms].variable_exponent2 = 0;
						terms[*num_of_terms].coefficient = get_coefficient; 
						for (int i = 0; i < (strlen(raw_term)); i++) {
								clean_term[i] = raw_term[i];
						}

						// same algorithm to extract exponents
						for (int i = 0; i < (strlen(clean_term)); i++) {
								if (clean_term[i] == terms[0].first_variable) {
										if (clean_term[i + 1] == '^') {
												sscanf(clean_term +  i + 2, "%d", &terms[*num_of_terms].variable_exponent1);
										} else {
												terms[*num_of_terms].variable_exponent1 = 1;
										}
								} else if (clean_term[i] == terms[0].second_variable) {
										if (clean_term[i + 1] == '^') {
												sscanf(clean_term +  i + 2, "%d", &terms[*num_of_terms].variable_exponent2);
										} else { 
												terms[*num_of_terms].variable_exponent2 = 1;
										}
								}
						}
						printf("Clean term:%s\n", clean_term);
					// case when the coefficient has two digits and it has it's varibale(s)
				} else if (isdigit(raw_term[0]) && isdigit(raw_term[1]) && (raw_term[2] == terms[0].first_variable ||
										raw_term[2] == terms[0].second_variable)) { //case e.g. 11x
						sscanf(raw_term, "%d", &get_coefficient); 
						terms[*num_of_terms].coefficient = get_coefficient;
						terms[*num_of_terms].variable_exponent2 = 0;
						// again, in the clean term we don't have the coefficient
						for (int i = 2, j = 0; i < strlen(raw_term); i++, j++) {
								clean_term[j] = raw_term[i];
						}
						// same algorithm to extract exponents
						for (int i = 0; i < (strlen(clean_term)); i++) {
								if (clean_term[i] == terms[0].first_variable) {
										if (clean_term[i + 1] == '^') {
												sscanf(clean_term +  i + 2, "%d", &terms[*num_of_terms].variable_exponent1);
										} else {
												terms[*num_of_terms].variable_exponent1 = 1;
										}
								} else if (clean_term[i] == terms[0].second_variable) {
										if (clean_term[i + 1] == '^') {
												sscanf(clean_term +  i + 2, "%d", &terms[*num_of_terms].variable_exponent2);
										} else {
												terms[*num_of_terms].variable_exponent2 = 1;
										}
								}
						}
						printf("Clean term:%s\n", clean_term);
					// else we just have a constant e.g. 200
				} else {
						get_coefficient += atoi(&raw_term[0]);
						terms[*num_of_terms].coefficient = get_coefficient; 
						terms[*num_of_terms].variable_exponent1 = 0;
						terms[*num_of_terms].variable_exponent2 = 0;
						printf("Clean term:%s\n", clean_term);
					
				}

				//terms index
				(*num_of_terms)++;
				//take next token
				raw_term = strtok(NULL, "+-");
		}
}

// we chew the input a little bit in order to not mess up the 
// indexes later, have everything clean and more user experience
// because the user can put any spaces between terms and many terms
void process_input(char* input, Term* terms, int* num_of_terms) {
		// need it local variables
		int index_of_signs = 0;
		bool keep_checking_for_variables = true;
		char variable1 = '\0', variable2 = '\0';
		int z = 0;

		for(int i = 0; input[i] != '\0'; i++) {
				// checking and setting the minus of the first term flag
				if (input[0] == 45) {
						FIRST_TERM_HAS_MINUS = true;
				}
				// checking signs on the whole input 
				// because we are managing the signs 
				// independently of everything else
				// checking positive signs
				if (input[i] == 43) {
						signs[index_of_signs] = 1;
						index_of_signs++;
				}
				// checking negative signs 
				if (input[i] == 45) {
						signs[index_of_signs] = 2;
						index_of_signs++;
				}
				// assigning the two first founded variables in the input
				if (input[i] != '^' && isalpha(input[i]) && keep_checking_for_variables) {
						if (variable1 == '\0') {
								variable1 = input[i];
								terms[0].first_variable = variable1;
						} else if (variable2 == '\0' && input[i] != variable1) {
								variable2 = input[i];
								terms[0].second_variable = variable2;
								//stop doing this to improve performance
								keep_checking_for_variables = false;
						} 
				}

				// we remove all the spaces of the input
				// in order to not mess the indexes later
				if (input[i] != ' ') {
						input[z] = input[i];
						z++;
				}
		}
		input[z] = '\0';

		if (variable2 == '\0') {
			variable2 = 'y';
			terms[0].second_variable = variable2;
			// assigning to each term the exponent of the second variable 
			// to 0 because else it will crash due to trash assignment
			for (int i = 0; i < 9; i++) {
				terms[i].variable_exponent2 = 0;
			}
		}

		// now we can process the polynomial with the cleaned and altered input
		process_polynomial(input, terms, num_of_terms);
}

// function to sum or rest the arrays obtained
void TermsOperations(int Calc_opt){
		int final_matrix[11][11] = {0};
		// sum arrays
		if(Calc_opt == 1){
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 11; j++) {
					final_matrix[i][j] = matrix_1[i][j] + matrix_2[i][j];
					printf("%d\t ", final_matrix[i][j]);
				}
				printf("\n");
			}
		// substract arrays
		}else{
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 11; j++) {
					final_matrix[i][j] = matrix_1[i][j] - matrix_2[i][j];
					printf("%d\t ", final_matrix[i][j]);

				}
			printf("\n");
			}
		}
		// we print the resulting equation
		printf("\nla equacion resultante es:");
		for (int i = 10; i >= 0; i--){
			for (int j = 10; j >= 0; j--)
			{
				if(final_matrix[i][j]!=0){
					if(final_matrix[i][j] > 0){
						printf(" + ");
					}else{
						printf(" - ");
						final_matrix[i][j] *= -1;
					}
					printf("%dx^%dy^%d", final_matrix[i][j],i,j);
				}
			}
			
		}
}

int main() {
		// input of first equation
		char input[100];
		// input of second equation
		char input_2[100];
		int num_of_terms = 0;
		// operation option 1 for sum anything else for substraction
		int Calc_opt;

		printf("This is a polynomial calculator that allows you to sum or substract polynomials of power 0 to 10\nPlease input your first polynomial... :");
		fgets(input, sizeof(input), stdin);

		// the important array explained where the struct is
		Term terms[9];

		// calling functions
		process_input(input,terms, &num_of_terms);
		print_the_matrix(terms, num_of_terms,matrix_1);

		FIRST_TERM_HAS_MINUS = false;
		num_of_terms = 0;

		// same process for the second polynomial
		printf("\n\nInsert the other polynomial \n");
   	 	fgets(input_2, sizeof(input_2), stdin);
		
		process_input(input_2,terms, &num_of_terms);
		print_the_matrix(terms, num_of_terms,matrix_2);

		// operation handling
		printf("\n\nWhat do you wish to do?\nSum = 1\nSubstract = 2\n");
		scanf("%d", &Calc_opt);
		TermsOperations(Calc_opt);
	
	return 0;
}



