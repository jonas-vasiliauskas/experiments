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
    bool isDouble=false;
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
    *val = (int*)malloc(sizeof(int)*ARRAY_SIZE);
    for (i=0;i<ARRAY_SIZE;++i)
        (*val)[i]=i*i;
}


int get_file_statistics(const char *file_name,const int word_size, int **word_freq_stats){
    FILE *data_file = fopen(file_name,"rb");
    if (data_file == NULL)
        return 1;
    if (word_size < 1 || word_size > 16)
        return 2;
    
    const int BITS_IN_BYTE = 8;    
    const int READ_BLOCK_SIZE = 4096;
    const int EXPANDED_READ_BLOCK_SIZE = READ_BLOCK_SIZE*BITS_IN_BYTE;
    const int WORD_COUNT = 1 << word_size;
    int i,j,byte_count = READ_BLOCK_SIZE;
    char read_block[READ_BLOCK_SIZE],expanded_read_block[EXPANDED_READ_BLOCK_SIZE];
    
    *word_freq_stats =(int*) malloc (sizeof(int)*WORD_COUNT);
    if (word_freq_stats == NULL)
        return 3;
        
    
    while (byte_count == READ_BLOCK_SIZE){
        memset(read_block,0,READ_BLOCK_SIZE);
        memset(expanded_read_block,0,EXPANDED_READ_BLOCK_SIZE);
        byte_count=fread(read_block,sizeof(char),READ_BLOCK_SIZE,data_file);
        for (i=0;i<byte_count;++i)
            for (j=1;j<BITS_IN_BYTE;++j)
                expanded_read_block[i*BITS_IN_BYTE+j]=(read_block[i]>>(BITS_IN_BYTE-j-1))%2;
        
        int bit_counter=0,word_value=0;
        for (i=0;i<byte_count*BITS_IN_BYTE;++i)
            if (bit_counter<word_size){
                word_value=(word_value<<1)+expanded_read_block[i];
                ++bit_counter;
            }
            else{
                ++(*word_freq_stats)[word_value];
                bit_counter=0;
                word_value=0;
            }
    }
   
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
        printf("%i ",word_freq_stats[i]);
    free(word_freq_stats);
    return 0;
}
