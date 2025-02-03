#include <stdio.h> 
#include <string.h> 
struct Book { 
    char title[100]; 
    char author[50]; 
    int year; 
}; 
int main() { 
    struct Book books[3]; 
 
    // Input details 
    int i ;
    for ( i = 0; i < 3; i++) { 
        printf("Enter details for book %d:\n", i + 1); 
        printf("Title: "); 
        scanf(" %[^\n]", books[i].title); //  ^ = alt + 94
        printf("Author: "); 
        scanf(" %[^\n]", books[i].author); 
        printf("Year: "); 
        scanf("%d", &books[i].year); 
    } 
    // Display details 
    printf("\nBooks Information:\n"); 
    
    for (i = 0; i < 3; i++) { 
        printf("Book %d:\n", i + 1); 
        printf("Title: %s\n", 
        books[i].title); 
        printf("Author: %s\n", 
        books[i].author); 
        printf("Year: %d\n\n", 
        books[i].year); 
    } 
    return 0; 
} 
