#include <stdio.h> 
#include <string.h> 
struct Student { 
		int id; 
		char name[50]; 
		float grade;
				}; 
void inputStudent(struct Student *s) { 
				    printf("Enter ID: "); 
				    scanf("%d", &s->id); 
				    printf("Enter Name: "); 
				    scanf(" %[^\n]", s->name); 
				    printf("Enter Grade: "); 
				    scanf("%f", &s->grade);
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
