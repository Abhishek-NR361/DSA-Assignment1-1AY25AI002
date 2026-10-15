
#include <stdio.h>

#define MAX 100

typedef struct {
    int row;
    int col;
    int value;
} term;

void display(term a[]) {
    int i;

    printf("Row\tColumn\tValue\n");

    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX];
    int starting_pos[MAX];
    int i, j, num_cols, num_terms;

    num_cols = a[0].col;
    num_terms = a[0].value;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms == 0) {
        printf("\nrow_terms[]: All zeros\n");
        printf("starting_pos[]: No positions needed\n");
        return;
    }

    /* Initialize row_terms */
    for (i = 0; i < num_cols; i++)
        row_terms[i] = 0;

    /* Count non-zero terms in each column */
    for (i = 1; i <= num_terms; i++)
        row_terms[a[i].col]++;

    printf("\nrow_terms[]:\n");
    for (i = 0; i < num_cols; i++)
        printf("%d ", row_terms[i]);

    /* Calculate starting positions */
    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++)
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];

    printf("\n\nstarting_pos[]:\n");
    for (i = 0; i < num_cols; i++)
        printf("%d ", starting_pos[i]);

    /* Place terms directly in transposed order */
    for (i = 1; i <= num_terms; i++) {
        j = starting_pos[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }

    printf("\n");
}

int main(void) {
    term a[MAX], b[MAX];
    int matrix[MAX][MAX];
    int rows, cols, i, j, count = 0;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows >= MAX || cols >= MAX ||
        rows * cols >= MAX) {
        printf("Invalid matrix size.\n");
        return 1;
    }

    printf("Enter matrix elements:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);

            if (matrix[i][j] != 0) {
                count++;
                if (count >= MAX) {
                    printf("Too many non-zero elements.\n");
                    return 1;
                }

                a[count].row = i;
                a[count].col = j;
                a[count].value = matrix[i][j];
            }
        }
    }

    /* Header triple */
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = count;

    printf("\nOriginal triples:\n");
    display(a);

    fast_transpose(a, b);

    printf("\nTransposed triples:\n");
    display(b);

    printf("\nThe transposed triples are in row-major order.\n");

    return 0;
}

