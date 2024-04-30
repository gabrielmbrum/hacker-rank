#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    int n, b, aux=0, count;
    scanf("%d", &n);
  	// Complete the code to print the pattern.

    for (int i = 1; i < n*2; i++) { // control the quantify of lines

        if (i > n) {aux += 2; i -= aux;} //makes the adjustment for the printing mode

        b = 0; count = 0;
        while (n - b > n - i && n - b > 0) {
            printf("%d ", n-(b++)); count++;
        } 
        while (count < n*2 - i) {printf("%d ", n-b+1); count++;}
        b--;       
        while (n - b < n) {
            printf("%d ", n-(--b));
        }
        printf("\n");

        if (aux) i += aux;
    }

    return 0;
}