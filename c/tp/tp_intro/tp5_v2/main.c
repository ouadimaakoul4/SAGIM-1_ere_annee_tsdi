#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float grade;
};

void inputStudent(struct Student *s) {
    
    printf("You entered ID: %d. Is this correct? (y/n): ", s->id);
    char verify;
    while (getchar() != '\n'); // Clear the newline character left by previous scanf
    scanf("%c", &verify);
    if (verify == 'n' || verify == 'N') {
        printf("Re-enter ID: ");
        while (scanf("%d", &s->id) != 1) {
            printf("Invalid input. Please enter a valid ID: ");
            while (getchar() != '\n'); // Clear the input buffer
        }
    }

    printf("Enter Name: ");
    while (getchar() != '\n'); // Clear the newline character left by previous scanf
    if (fgets(s->name, sizeof(s->name), stdin) != NULL) {
        s->name[strcspn(s->name, "\n")] = '\0'; // Remove the newline character
    }

    printf("Enter Grade: ");
    while (scanf("%f", &s->grade) != 1) {
        printf("Invalid input. Please enter a valid grade: ");
        while (getchar() != '\n'); // Clear the input buffer
    }
}

void printStudent(struct Student s) {
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Grade: %.2f\n", s.grade);
}

int main() {
    struct Student students[5];
    int i;

    for (i = 0; i < 5; i++) {
        printf("Enter details for student %d:\n", i + 1);
        inputStudent(&students[i]);
    }

    printf("\nStudent Details:\n");
    for (i = 0; i < 5; i++) {
        printf("Student %d:\n", i + 1);
        printStudent(students[i]);
    }

    return 0;
}
