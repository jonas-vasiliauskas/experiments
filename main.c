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

typedef struct word_freq_stats_t{
    int index;
    int frequency;
}word_freq_stats_t;

int get_file_statistics(const char *file_name,const unsigned int word_size, word_freq_stats_t **word_freq_stats){
    FILE *data_file = fopen(file_name,"rb");
    if (data_file == NULL)
        return 1;
    if (word_size < 2 || word_size > 16)
        return 2;
    
    const unsigned int BITS_IN_BYTE = 8;    
    const unsigned int READ_BLOCK_SIZE = 4096;
    const unsigned int EXPANDED_READ_BLOCK_SIZE = READ_BLOCK_SIZE*BITS_IN_BYTE;
    const unsigned int WORD_COUNT = 1 << word_size;
    unsigned int i,j,byte_count = READ_BLOCK_SIZE;
    unsigned char read_block[READ_BLOCK_SIZE],expanded_read_block[EXPANDED_READ_BLOCK_SIZE];
    
    *word_freq_stats =(word_freq_stats_t*) calloc (sizeof(word_freq_stats_t),WORD_COUNT);
    if (word_freq_stats == NULL)
        return 3;
    for (i=0;i<WORD_COUNT;++i)
        (*word_freq_stats)[i].index = i;  
        
    
    while (byte_count == READ_BLOCK_SIZE){
        memset(read_block,0,READ_BLOCK_SIZE);
        memset(expanded_read_block,0,EXPANDED_READ_BLOCK_SIZE);
        byte_count=fread(read_block,sizeof(char),READ_BLOCK_SIZE,data_file);
        for (i=0;i<byte_count;++i)
            for (j=1;j<BITS_IN_BYTE;++j)
                expanded_read_block[i*BITS_IN_BYTE+j]=(read_block[i]>>(BITS_IN_BYTE-j-1))%2;
        
        unsigned int bit_counter=0,word_value=0;
        
        const unsigned int WORD_COUNT=byte_count*BITS_IN_BYTE;
        const unsigned int COMPLETE_WORD_COUNT = WORD_COUNT % word_size == 0?WORD_COUNT:WORD_COUNT-1;
        
        for (i=0;i<COMPLETE_WORD_COUNT;++i)
            if ((bit_counter+1)<word_size){
                word_value=(word_value<<1)+expanded_read_block[i];
                ++bit_counter;
            }
            else{
                word_value=(word_value<<1)+expanded_read_block[i];
                ++((*word_freq_stats)[word_value].frequency);
                bit_counter=0;
                word_value=0;
            }
        if (COMPLETE_WORD_COUNT!=WORD_COUNT){    
            for (i=COMPLETE_WORD_COUNT;i<WORD_COUNT;++i)
                word_value=word_value<<1;
            ++((*word_freq_stats)[word_value].frequency);
            bit_counter=0;
            word_value=0;
        }
    }
   
    fclose(data_file);
    return 0;
}

typedef struct huffman_compression_item_t{
    char *starting_bytes;
    char *huffman_encoding;
}huffman_compression_item_t;

int comp(const void *first, const void *second){
    const word_freq_stats_t *first_obj = (word_freq_stats_t*) first;
    const word_freq_stats_t *second_obj = (word_freq_stats_t*) second;
    return (first_obj->frequency-second_obj->frequency);
}

int get_huffman_compression_table(const int word_size, word_freq_stats_t *word_freq_stats,
    huffman_compression_item_t **huffman_compression_items){
    const unsigned int WORD_COUNT = 1 <<word_size;
    if (word_freq_stats==NULL)
        return 1;
        
    *huffman_compression_items =(huffman_compression_item_t*) malloc (sizeof(huffman_compression_item_t)*WORD_COUNT);
    qsort(word_freq_stats,WORD_COUNT, sizeof(word_freq_stats[0]), comp);
    puts("---------------------------------------------");
    unsigned int i;
    for (i=0;i<WORD_COUNT;++i)
        printf("%i %i\n",word_freq_stats[i].index,word_freq_stats[i].frequency);
    puts("---------------------------------------------");
    return 0;
}

int main(int arg_c, char **arg_v){
    if (arg_c != 3){
        fprintf(stderr,"%s\n","Netinkamas parametru skaicius");
        return 1;
    }
    word_freq_stats_t *word_freq_stats=NULL;
    const int  WORD_SIZE = atoi(arg_v[2]);
    //const int WORD_COUNT = 1 << WORD_SIZE;
    const int return_code = get_file_statistics(arg_v[1],WORD_SIZE,&word_freq_stats);
    if (return_code != 0){
        fprintf(stderr,"%s%i\n","funkcija grazino pabaigos koda ",return_code);
        return return_code;
    }
    
    //int i;
    
   // for (i=0;i<WORD_COUNT;++i)
   //     printf("%i %i\n",word_freq_stats[i].index,word_freq_stats[i].frequency);
    huffman_compression_item_t *huffman_compression_items=NULL;       
    get_huffman_compression_table(WORD_SIZE,word_freq_stats,&huffman_compression_items);
    free(word_freq_stats);
    free(huffman_compression_items);
    return 0;
}
