#include <stdio.h>

int main(void)
{
    double firstNumber;
    double secondNumber;
    double result;
    char operation;

    printf("Smart Calculator\n");
    // gets the two numbers and operation
    printf("Enter the first number: ");
    if (scanf("%lf", &firstNumber) != 1) {
        printf("Invalid number.\n");
        return 1;
    }

    printf("Enter an operation (+, -, *, /): ");
    if (scanf(" %c", &operation) != 1) {
        printf("Invalid operation.\n");
        return 1;
    }

    printf("Enter the second number: ");
    if (scanf("%lf", &secondNumber) != 1) {
        printf("Invalid number.\n");
        return 1;
    }

    // uses operaation user picked
    switch (operation) {
    case '+':
        result = firstNumber + secondNumber;
        break;
    case '-':
        result = firstNumber - secondNumber;
        break;
    case '*':
        result = firstNumber * secondNumber;
        break;
    case '/':
        // ! / 0
        if (secondNumber == 0.0) {
            printf("Cannot divide by zero.\n");
            return 1;
        }
        result = firstNumber / secondNumber;
        break;
    default:
        printf("Unknown operation.\n");
        return 1;
    }

    printf("Result: %.2f\n", result);
    return 0;
}
