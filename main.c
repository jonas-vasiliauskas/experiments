#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

float get_float(const char *msg){
    const int BUFFER_SIZE = 100;
    bool isFloat;
    int i;
    
    float result;
    char buffer[BUFFER_SIZE];
    do{
        isFloat = true;
        memset(buffer,0,BUFFER_SIZE);
        puts(msg);
        fgets(buffer,BUFFER_SIZE,stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        for (i=BUFFER_SIZE-1;i>=0;--i)
            if (!isdigit(buffer[i]) && buffer[i]!='.' && buffer[i]!=0 && buffer[i]!='-'){
                isFloat = false;
                puts("Klaida");
                break;
            }
    }
    while(!isFloat);
    result = atof(buffer);
    return result;
}

int main(){
    float first_number,second_number;
    first_number=get_float("Iveskite pirma skaiciu");
    second_number=get_float("Iveskite antra skaiciu");
    const float sum = first_number + second_number;
    printf("%s%f\n","suma ",sum);
    return 0;
}
