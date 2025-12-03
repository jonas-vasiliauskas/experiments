#include <stdio.h>

int main(){
    int first_number,second_number;
    puts("Iveskite pirma skaiciu");
    scanf("%i",&first_number);
    puts("Iveskite antra skaiciu");
    scanf("%i",&second_number);
    const int sum = first_number + second_number;
    printf("%s%i\n","suma ",sum);
    return 0;
}
