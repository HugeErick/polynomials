#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool FIRST_TERM_HAS_MINUS = false;
int signs[10];

typedef struct {
		int coefficient;
		int variable_exponent1;
		int variable_exponent2;
		char first_variable;
		char second_variable;
} Term;

void print_the_matrix(Term* terms, int num_of_terms) {
		bool FIRST_TERM_GONE = false;
		printf("\n");
		for (int i = 0; i < num_of_terms; i++) {
				printf("\tCoefficient %d: %d\n", i, terms[i].coefficient);
				printf("\texponent_var 1 index%d: %d\n", i, terms[i].variable_exponent1);
				printf("\texponent_var 2 index%d: %d\n", i, terms[i].variable_exponent2);
				printf("\tsign index %d: %d\n", i, signs[i] );
		}

		printf("\n");
		int matrix[11][11] = {0};

		for (int i = 0, j = 0; i < num_of_terms; i++) {
				int exponent_var1 = terms[i].variable_exponent1;
				int exponent_var2 = terms[i].variable_exponent2;
				int coefficient = terms[i].coefficient;
				
				if (FIRST_TERM_HAS_MINUS) {
						puts("first term has minus");
						j++;
						int negative_coefficient = coefficient * -1;
						matrix[exponent_var1][exponent_var2] = negative_coefficient;
						FIRST_TERM_HAS_MINUS = false;
						FIRST_TERM_GONE = true;
				} else if (FIRST_TERM_GONE) {
						if (signs[j] == 2) {
								int negative_coefficient = coefficient * -1;
								matrix[exponent_var1][exponent_var2] = negative_coefficient;
						} else {
								matrix[exponent_var1][exponent_var2] = coefficient;
						}
						j++;
				} else {
						puts("first term is positive");
						matrix[exponent_var1][exponent_var2] = coefficient;
						FIRST_TERM_GONE = true;
				}
		}

		for (int i = 0; i < 11; i ++){
				for (int j = 0; j < 11; j++) {
						printf("%d  ", matrix[i][j]);
				}
				printf("\n");
		}
}

void process_polynomial(char* raw_equation, Term* terms, int* num_of_terms) {
		int count_raw_terms = 0;
		char* raw_term = strtok(raw_equation, "+-"); 

		while (raw_term != NULL) {
				char clean_term[50] = "";
				int get_coefficient = 0;
				count_raw_terms++;

				if (isdigit(raw_term[0]) && (raw_term[1] == terms[0].first_variable ||
										raw_term[1] == terms[0].second_variable) ) { //case 8x
						get_coefficient += atoi(&raw_term[0]);
						terms[*num_of_terms].coefficient = get_coefficient; 
						terms[*num_of_terms].variable_exponent2 = 0;
						for (int i = 1, j = 0; i < (strlen(raw_term)); i++, j++)
								clean_term[j] = raw_term[i];

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

								
						printf("Clean term %d = %s\n", count_raw_terms, clean_term);

				} else if (isalpha(raw_term[0])) { //case x
						get_coefficient = 1;
						terms[*num_of_terms].coefficient = get_coefficient; 
						for (int i = 0; i < (strlen(raw_term)); i++) {
								clean_term[i] = raw_term[i];
						}

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
						printf("Clean term %d = %s\n", count_raw_terms, clean_term);

				} else if (isdigit(raw_term[0]) && isdigit(raw_term[1]) && (raw_term[2] == terms[0].first_variable ||
										raw_term[2] == terms[0].second_variable)) { //case 11x
						sscanf(raw_term, "%d", &get_coefficient); 
						terms[*num_of_terms].coefficient = get_coefficient;
						for (int i = 2, j = 0; i < strlen(raw_term); i++, j++) {
								clean_term[j] = raw_term[i];
						}
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

						printf("Clean term %d = %s\n", count_raw_terms, clean_term);
				} else {
						get_coefficient += atoi(&raw_term[0]);
						terms[*num_of_terms].coefficient = get_coefficient; 
						terms[*num_of_terms].variable_exponent1 = 0;
						terms[*num_of_terms].variable_exponent2 = 0;
						printf("Clean term %d = %s\n", count_raw_terms, raw_term);
				}


				printf(" Coefficient:%u\n",get_coefficient);
				//terms index
				(*num_of_terms)++;
				//take next token
				raw_term = strtok(NULL, "+-");
		}
}

void process_input(char* input, Term* terms, int* num_of_terms) {
		// need it local variables
		int index_of_signs = 0;
		bool keep_checking_for_variables = true;
		char variable1 = '\0', variable2 = '\0';
		//int input_length = strlen(input);

		// Remove the newline character from input if present
		/*
		if (input_length > 0 && input[input_length -1] == '\n') {
				input[input_length - 1] = '\0';
		}
		 */

		int z = 0;
		for(int i = 0; input[i] != '\0'; i++) {
				if (input[0] == 45) {
						FIRST_TERM_HAS_MINUS = true;
				}
				if (input[i] == 43) {
				puts("hi?");
						signs[index_of_signs] = 1;
						index_of_signs++;
				}
				if (input[i] == 45) {
				puts("hi?");
						signs[index_of_signs] = 2;
						index_of_signs++;
				}
				if (input[i] != '^' && isalpha(input[i]) && keep_checking_for_variables) {
						if (variable1 == '\0') {
								variable1 = input[i];
								terms[0].first_variable = variable1;
						} else if (variable2 == '\0') {
								variable2 = input[i];
								terms[0].second_variable = variable2;
								//stop doing this to improve performance
								keep_checking_for_variables = false;
						} 
				}

				if (input[i] != ' ') {
						input[z] = input[i];
						z++;
				}
		}
		input[z] = '\0';

		printf("\nvar1:%c\t var2:%c\n", variable1, variable2);
		process_polynomial(input, terms, num_of_terms);
}

int main() {
		char input[200];
		printf("input... :");
		fgets(input, sizeof(input), stdin);
		int num_of_terms = 0;

		Term terms[9];

		process_input(input,terms, &num_of_terms);

		print_the_matrix(terms, num_of_terms);
    return 0;
}


