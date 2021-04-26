#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void removeSpaces(char* str) {
  int i, x;
  for(i=x=0; str[i]; ++i)
    if(!isspace(str[i]) || (i > 0 && !isspace(str[i-1]))){
        str[x++] = str[i];
    }
  str[x] = '\0';
}
void lowerCase(char* str){
    long length = strlen (str);
    for(int i = 0; i < length; i++){
        str[i] = tolower(str[i]);
    }
}
void removeTab(char* str){
    long length = strlen (str);
    for(int i = 0; i < length; i++){
        if(str[i] == '\t'){
            str[i] = ' ';
        }
    }
}
char *partOfArray(char *a, int k, int num){
    char* part = malloc(k);
    for(int i = 0; i < k; i++ ){
        part[i] = a[num];
        num++;
    }
    return part;
}
char *preprocessed(char *str){
    removeSpaces(str);
    lowerCase(str);
    removeTab(str);
    return str;
}
int ctr(int k, char *a, char *b){
    int count = 0;
    int size_a = strlen(a);
    int size_b = strlen(b);
    int substring_a = size_a - k + 1;

    for(int i = 0; i < substring_a ; i++){ 
        char *tempa = partOfArray(a, k, i);
        for(int j = 0; j < size_b - k + 1; j++){
            char *tempb = partOfArray(b, k, j);

            if (strcmp(tempa, tempb) == 0){
                count++;
                // printf("--------");
                // printf("%d", count);
            }
            free(tempb);
        }
        free(tempa);
    }
    return count;
}
int main(int argc, char *argv[]){
    int k = *argv[1] - '0';
    FILE* filea = fopen(argv[2], "r");
    fseek(filea, 0, SEEK_END);
    int fsize_a = ftell(filea);
    fseek(filea, 0, SEEK_SET);
    char* buffer_a = malloc(fsize_a);
    fread(buffer_a, fsize_a, 1, filea);
    fclose(filea);

    FILE* fileb = fopen(argv[3], "r");
    fseek(fileb, 0, SEEK_END);
    int fsize_b = ftell(fileb);
    fseek(fileb, 0, SEEK_SET);
    char* buffer_b = malloc(fsize_b);
    fread(buffer_b, fsize_b, 1, fileb);
    fclose(fileb);

    buffer_a = preprocessed(buffer_a);
    printf("%s", buffer_a);
    long size_a = strlen(buffer_a);
    putchar('\n');

    buffer_b = preprocessed(buffer_b);
    printf("%s", buffer_b);
    putchar('\n');
    double result = (double) ctr(k, buffer_a, buffer_b) / (double) (size_a - k + 1);
    putchar('\n');
    printf("Similarity = %f", result);

    // free your buffer_a
    free(buffer_a);
    free(buffer_b);
}
