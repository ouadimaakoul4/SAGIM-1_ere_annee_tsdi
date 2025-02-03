#include <stdio.h> 
struct Point { int x; int y;}; 
int areEqual(struct Point p1, struct Point p2) {  
			return (p1.x == p2.x && p1.y == p2.y);
		} 
int main() { 
    struct Point p1 = {3, 4}; 
    struct Point p2 = {3, 4}; 
    if (areEqual(p1, p2)) { 
        printf("The points are equal.\n"); 
    } else { 
        printf("The points are not equal.\n"); 
    } 
    return 0; 
} 
