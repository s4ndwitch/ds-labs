#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"
#include "math.h"

int isoperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')' ||
        c == '!' || c == 'V' || c == 's' || c == 'c' || c == '%';
}

int funccmp(char a, char b) {
    char prioritisation[256];
    prioritisation['+'] = 1;
    prioritisation['-'] = 1;
    prioritisation['*'] = 2;
    prioritisation['/'] = 2;
    prioritisation['!'] = 3;
    prioritisation['^'] = 3;
    prioritisation['%'] = 3;
    prioritisation['V'] = 3;
    prioritisation['s'] = 3;
    prioritisation['c'] = 3;

    return prioritisation[(int)a] - prioritisation[(int)b];
}

void handleOperator(char c, struct Stack *operators, struct Stack *numbers) {
    char *newOperator = malloc(sizeof(char) * 1);
    newOperator[0] = c;
    if (c == '(') {
        push(operators, newOperator);
        return;
    }
    struct Stack *previousElement = top(operators);
    if (previousElement->data == NULL) {
        push(operators, newOperator);
        return;
    }
    char previousOperator = *((char *)(previousElement->data));
    if (previousOperator == '(') {
        if (c == ')') {
            previousElement = pop(operators);
            removeElement(previousElement);
            return;
        }
        push(operators, newOperator);
        return;
    }
    if (c != ')' && c != '\0' && funccmp(c, previousOperator) > 0) {
        push(operators, newOperator);
        return;
    }
    previousElement = pop(operators);
    struct Stack *firstElement;
    struct Stack *secondElement;
    double firstNumber;
    double secondNumber;
    double *result = (double *)malloc(firstNumber * sizeof(double));
    switch (previousOperator) {
        case '+':
            firstElement = pop(numbers);
            secondElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            secondNumber = *((double *)(secondElement->data));
            *result = secondNumber + firstNumber;
            push(numbers, result);

            removeElement(firstElement);
            removeElement(secondElement);
            removeElement(previousElement);

            break;
        case '-':
            firstElement = pop(numbers);
            secondElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            secondNumber = *((double *)(secondElement->data));
            *result = secondNumber - firstNumber;
            push(numbers, result);

            removeElement(firstElement);
            removeElement(secondElement);
            removeElement(previousElement);

            break;
        case '*':
            firstElement = pop(numbers);
            secondElement = pop(numbers);
            double firstNumber = *((double *)(firstElement->data));
            double secondNumber = *((double *)(secondElement->data));            
            double *result = (double *)malloc(firstNumber * sizeof(double));
            *result = secondNumber * firstNumber;
            push(numbers, result);

            removeElement(firstElement);
            removeElement(secondElement);
            removeElement(previousElement);

            break;
        case '/':
            firstElement = pop(numbers);
            secondElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            secondNumber = *((double *)(secondElement->data));
            *result = secondNumber / firstNumber;
            push(numbers, result);

            removeElement(firstElement);
            removeElement(secondElement);
            removeElement(previousElement);

            break;
        case '^':
            firstElement = pop(numbers);
            secondElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            secondNumber = *((double *)(secondElement->data));
            *result = pow(firstNumber, secondNumber);
            push(numbers, result);

            removeElement(firstElement);
            removeElement(secondElement);
            removeElement(previousElement);

            break;
        case '!':
            firstElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            *result = factorial(firstNumber);
            push(numbers, result);

            removeElement(firstElement);
            removeElement(previousElement);

            break;
        case 'V':
            firstElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            *result = sqrt(firstNumber);
            push(numbers, result);

            removeElement(firstElement);
            removeElement(previousElement);

            break;
        case 's':
            firstElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            *result = sin(firstNumber);
            push(numbers, result);

            removeElement(firstElement);
            removeElement(previousElement);

            break;
        case 'c':
            firstElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            *result = cos(firstNumber);
            push(numbers, result);

            removeElement(firstElement);
            removeElement(previousElement);

            break;
        case '%':
            firstElement = pop(numbers);
            struct Stack *secondElement = pop(numbers);
            firstNumber = *((double *)(firstElement->data));
            secondNumber = *((double *)(secondElement->data));
            
            if (firstNumber / 1 != firstNumber || secondNumber / 1 != secondNumber) {
                fprintf(stderr, "Float number is given to modulus operator.\n");
                exit(1);
            }

            *result = (double)((int)secondNumber % (int)firstNumber);

            push(numbers, result);

            removeElement(firstElement);
            removeElement(secondElement);
            removeElement(previousElement);

            break;
        default:
            fprintf(stderr, "Unknown operator: %c\n", c);
            exit(1);
    }

    if (c != '\0')
        handleOperator(c, operators, numbers);
}

void parseInput(char *input) {
    char newInput[strlen(input) + 1];
    char *word;
    while ((word = strstr(input, "sin")) != NULL) {
        memcpy(newInput, input, (word - input) + 1);
        memcpy(newInput + (word - input) + 1, word + 3, strlen(word + 3) + 1);
        memcpy(input, newInput, strlen(newInput) + 1);
    }
    while ((word = strstr(input, "cos")) != NULL) {
        memcpy(newInput, input, (word - input) + 1);
        memcpy(newInput + (word - input) + 1, word + 3, strlen(word + 3) + 1);
        memcpy(input, newInput, strlen(newInput) + 1);
    }
    while ((word = strstr(input, "sqrt")) != NULL) {
        word[0] = 'V';
        memcpy(newInput, input, (word - input) + 1);
        memcpy(newInput + (word - input) + 1, word + 4, strlen(word + 4) + 1);
        memcpy(input, newInput, strlen(newInput) + 1);
    }
    while ((word = strstr(input, " ")) != NULL) {
        memcpy(newInput, input, (word - input));
        memcpy(newInput + (word - input), word + 1, strlen(word + 1) + 1);
        memcpy(input, newInput, strlen(newInput) + 1);
    }
}

int main(int argc, char *argv[]) {

    char *input;
    if (argc < 2) {
        printf("Not enough arguments, please, enter a line:\n");
        input = (char *)malloc(sizeof(char) * 2500);
    } else {
        int inputSize = 0;

        for (int i = 1; i < argc; i++)
            inputSize += strlen(argv[i]);

        input = (char *)malloc(sizeof(char) * inputSize);

        for (int i = 1; i < argc; i++)
            strcpy(input, argv[i]);

        input[inputSize - 1] = '\0';
        parseInput(input);
    }

    struct Stack *numbers = createStack();
    struct Stack *operators = createStack();
    
    for (int i = 0; i < strlen(input) + 1; i++) {
        if (isdigit(input[i])) {
            double *newNumber = (double *)malloc(sizeof(double));
            char *endPointer;
            *newNumber = strtod(input + i, &endPointer);
            i += endPointer - (input + i);
            push(numbers, newNumber);
        } else if (input[i] == '\0' || isoperator(input[i])) {
            handleOperator(input[i], operators, numbers);
        } else {
            fprintf(stderr, "Invalid input");
            return 1;
        }
    }
    printf("%f\n", *((double *)(pop(numbers)->data)));
    return 0;
}
