#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int get_int(const char *msg){
    const int BUFFER_SIZE =  100;
    bool isEqual = false;
    
    int result;
    char buffer1[BUFFER_SIZE],buffer2[BUFFER_SIZE];
    do{
        memset(buffer1,0,BUFFER_SIZE);
        memset(buffer2,0,BUFFER_SIZE);
        puts(msg);
        fgets(buffer1,BUFFER_SIZE,stdin);
        buffer1[strcspn(buffer1, "\n")] = 0;
        result=atoi(buffer1);
        snprintf(buffer2,BUFFER_SIZE,"%i",result);
        isEqual=strcmp(buffer1,buffer2)==0;
        if (!isEqual)
            puts("Klaida");
    }
    while(!isEqual);
    return result;
}

int main(){
    int first_number,second_number;
    first_number=get_int("Iveskite pirma skaiciu");
    second_number=get_int("Iveskite antra skaiciu");
    const int sum = first_number + second_number;
    printf("%s%i\n","suma ",sum);
    return 0;
}
