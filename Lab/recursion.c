#include <stdio.h>

int factorial(int n);
int main(){
    int number;
   
    printf("Enter an integer: ");  
    
    // reads and stores input
    scanf("%d", &number);
    // displays output
    printf("You entered: %d", number);
    
    return 0;
}
int factorial(int n){
    return n;
}