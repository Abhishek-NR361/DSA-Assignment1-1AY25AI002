
#include <stdio.h>
#include <stdlib.h>

#define FULL_TIME 1
#define CONTRACT 2

typedef struct {
    char name[20];
    int emp_id;
    int type;

    union {
        float salary;

        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;

    } pay;

} Employee;

int main(void) {
    Employee *emp;
    int n, i;
    float total_pay, total_bill = 0.0f;

    printf("Enter number of employees: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    emp = (Employee *)malloc(n * sizeof(Employee));

    if (emp == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Read employee details */
    for (i = 0; i < n; i++) {
        printf("\nEnter employee name: ");
        scanf("%19s", (emp + i)->name);

        printf("Enter employee ID: ");
        scanf("%d", &(emp + i)->emp_id);

        printf("Enter type (1-Full-time, 2-Contract): ");
        scanf("%d", &(emp + i)->type);

        if ((emp + i)->type == FULL_TIME) {
            printf("Enter monthly salary: ");
            scanf("%f", &(emp + i)->pay.salary);
        }
        else if ((emp + i)->type == CONTRACT) {
            printf("Enter hourly rate: ");
            scanf("%f",
                &(emp + i)->pay.contract_info.hourly_rate);

            printf("Enter hours worked: ");
            scanf("%d",
                &(emp + i)->pay.contract_info.hours_worked);
        }
        else {
            printf("Invalid employee type.\n");
            free(emp);
            return 1;
        }
    }

    /* Display payslips */
    printf("\n--- EMPLOYEE PAYSLIPS ---\n");

    for (i = 0; i < n; i++) {
        printf("\nEmployee Name: %s\n", (emp + i)->name);
        printf("Employee ID: %d\n", (emp + i)->emp_id);

        if ((emp + i)->type == FULL_TIME) {
            total_pay = (emp + i)->pay.salary;
            printf("Type: Full-time\n");
        }
        else {
            total_pay =
                (emp + i)->pay.contract_info.hourly_rate *
                (emp + i)->pay.contract_info.hours_worked;

            printf("Type: Contract\n");
        }

        printf("Total Pay: Rs. %.2f\n", total_pay);
        total_bill += total_pay;
    }

    printf("\nTotal Salary Bill: Rs. %.2f\n", total_bill);

    free(emp);
    return 0;
}

