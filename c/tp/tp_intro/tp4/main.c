#include <stdio.h> 
 
struct Rectangle { 
    float length; 
    float width; 
				}; 
 
int main() { 

    struct Rectangle r; 
 
    // Input dimensions 
    printf("Enter length: "); 
    scanf("%f", &r.length); 
    printf("Enter width: "); 
    scanf("%f", &r.width); 
 
    // Calculate and print area and perimeter 
    float area = r.length * r.width; 
    float perimeter = 2 * (r.length + r.width); 
 
    printf("Area: %.2f\n", area); 
    printf("Perimeter: %.2f\n", perimeter); 
 
    return 0; 
} 
