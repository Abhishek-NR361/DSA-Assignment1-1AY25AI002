
#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

/* Function to add two polynomials */
polynomial add(polynomial a, polynomial b) {
    polynomial c;
    int i, exp;

    c.degree = (a.degree > b.degree) ? a.degree : b.degree;

    for (i = 0; i <= c.degree; i++) {
        exp = c.degree - i;

        if (exp <= a.degree)
            c.coef[i] = a.coef[a.degree - exp];
        else
            c.coef[i] = 0;

        if (exp <= b.degree)
            c.coef[i] += b.coef[b.degree - exp];
    }

    return c;
}

/* Function to display a polynomial */
void display(polynomial p) {
    int i, exp, printed = 0;
    float value;

    for (i = 0; i <= p.degree; i++) {
        value = p.coef[i];
        exp = p.degree - i;

        if (value == 0)
            continue;

        if (printed && value > 0)
            printf(" + ");
        else if (printed && value < 0)
            printf(" - ");
        else if (value < 0)
            printf("-");

        if (value < 0)
            value = -value;

        if (exp == 0) {
            printf("%g", value);
        } else {
            if (value != 1)
                printf("%g", value);

            printf("x");

            if (exp > 1)
                printf("^%d", exp);
        }

        printed = 1;
    }

    if (!printed)
        printf("0");

    printf("\n");
}

int main(void) {
    polynomial a, b, c;
    int i;

    printf("Enter degree of first polynomial: ");
    scanf("%d", &a.degree);

    if (a.degree < 0 || a.degree > 100) {
        printf("Invalid degree.\n");
        return 1;
    }

    printf("Enter coefficients in descending order:\n");

    for (i = 0; i <= a.degree; i++) {
        printf("Coefficient of x^%d: ", a.degree - i);
        scanf("%f", &a.coef[i]);
    }

    printf("\nEnter degree of second polynomial: ");
    scanf("%d", &b.degree);

    if (b.degree < 0 || b.degree > 100) {
        printf("Invalid degree.\n");
        return 1;
    }

    printf("Enter coefficients in descending order:\n");

    for (i = 0; i <= b.degree; i++) {
        printf("Coefficient of x^%d: ", b.degree - i);
        scanf("%f", &b.coef[i]);
    }

    c = add(a, b);

    printf("\nFirst polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    printf("Sum: ");
    display(c);

    return 0;
}

