#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_VARIABLES 2

int main() {
    char input[50];
    printf("Enter the input: ");
    fgets(input, sizeof(input), stdin);

    int exponents[MAX_VARIABLES] = {0};
    int coefficient = 1;
    int coefficientParsed = 0;
    int currentIndex = 0;

    // Parse the coefficient if present
    while (isdigit(input[currentIndex])) {
        coefficientParsed = coefficientParsed * 10 + (input[currentIndex] - '0');
        currentIndex++;
    }

    if (coefficientParsed != 0) {
        coefficient = coefficientParsed;
    }

    // Process the rest of the input
    while (currentIndex < strlen(input)) {
        if (islower(input[currentIndex])) {
            int varIndex = -1;
            for (int j = 0; j < MAX_VARIABLES; j++) {
                if (exponents[j] == 0) {
                    exponents[j] = 1;
                    varIndex = j;
                    break;
                } else if (input[currentIndex] == 'a' + j) {
                    varIndex = j;
                    break;
                }
            }

            if (varIndex != -1 && currentIndex + 2 < strlen(input) && input[currentIndex + 1] == '^' && isdigit(input[currentIndex + 2])) {
                int exponent = input[currentIndex + 2] - '0';
                exponents[varIndex] = exponent;
            }
        }
        currentIndex++;
    }

    int var1_exp = exponents[0];
    int var2_exp = exponents[1];

    printf("Coefficient: %d\n", coefficient);
    printf("var1_exp: %d var2_exp: %d\n", var1_exp, var2_exp);

    return 0;
}

