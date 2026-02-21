#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ARRAY_SIZE 1000

int get_int(const char *msg,const char *err_msg){
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
            puts(err_msg);
    }
    while(!isEqual);
    return result;
}

double get_double(const char *msg,const char *err_msg){
    const int BUFFER_SIZE = 100;
    bool isDouble;
    int i;
    
    double result;
    char buffer[BUFFER_SIZE];
    do{
        isDouble = true;
        memset(buffer,0,BUFFER_SIZE);
        puts(msg);
        fgets(buffer,BUFFER_SIZE,stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        for (i=BUFFER_SIZE-1;i>=0;--i)
            if (!isdigit(buffer[i]) && buffer[i]!='.' && buffer[i]!=0 && buffer[i]!='-'){
                isDouble = false;
                puts(err_msg);
                break;
            }
    }
    while(!isDouble);
    result = atof(buffer);
    return result;
}

void test3(int **val){
    int i;
    *val = malloc(sizeof(int)*ARRAY_SIZE);
    for (i=0;i<ARRAY_SIZE;++i)
        (*val)[i]=i*i;
}

int main(){
    int i,*test_value;
    test3(&test_value);
    for (i=0;i<ARRAY_SIZE;++i){
        printf("%6i ",test_value[i]);
        if (i % 10 == 0 && i!=0)
            puts("");
    }
    free(test_value);
}


/*int get_file_statistics(const char *file_name,const int word_size, int **word_freq_stats){
    FILE *data_file = fopen(file_name,"rb");
    if (data_file == NULL)
        return 1;
    if (word_size < 1 || word_size > 16)
        return 2;
        
    const int READ_BLOCK_SIZE = 4096;
    const int WORD_COUNT = 1 << word_size;
    int i;
    char read_block[READ_BLOCK_SIZE];
    memset(read_block,0,READ_BLOCK_SIZE);
    
    *word_freq_stats =(int**) malloc (sizeof(int*)*WORD_COUNT);
  //  for (i=0;i<WORD_COUNT;++i)
  //      *word_freq_stats[i]=1;
   
    fclose(data_file);
    return 0;
}

int main(){
    int *word_freq_stats=NULL;
    const int return_code = get_file_statistics("testas",2,&word_freq_stats);
    if (return_code != 0){
        printf("%s%i\n","funkcija grazino pabaigos koda ",return_code);
        return return_code;
    }
    const int WORD_COUNT = 1 << 2;
    int i;
    
    for (i=0;i<WORD_COUNT;++i)
        printf("%i",word_freq_stats[i]);
    free(word_freq_stats);
    return 0;
}*/
