#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void removeSpaces(char* str) {
    int i, j;
    for(i=j=0; str[i]; ++i){
        if(!isspace(str[i]) || (i > 0 && !isspace(str[i-1]))){
            str[j++] = str[i];
        }
    }    
  str[j] = '\0';
}
char *partOfArray(char *a, int k, int num){
    char* part = (char*) malloc(k + 1);
    for(int i = 0; i < k; i++ ){
        part[i] = a[num];
        num++;
    }
    part[2] = '\0';
    return part;
}
void preprocessed(char *str){
    removeSpaces(str);
    for(int i = 0; i < strlen(str); i++){
        str[i] = tolower(str[i]);
        if(isspace(str[i])){
            str[i] = ' ';
        }
    }
    
}
int ctr(int k, char *a, char *b){
    int count = 0;
    int size_a = strlen(a);
    int size_b = strlen(b);
    int substring_a = size_a - k + 1;

    for(int i = 0; i < substring_a ; i++){ 
        //printf("i is %d, array a is: %s, k is: %d", i, a, k);
        char *tempa = partOfArray(a, k, i);
        //printf(" sub string a is %s\n", tempa );
        for(int j = 0; j < size_b - k + 1; j++){
            char *tempb = partOfArray(b, k, j);
            //printf(" sub string b is %s\n", tempb );

            if (strcmp(tempa, tempb) == 0){
                count++;
                 //printf("--------");
                 //printf("%d", count);
            }
            free(tempb);
        }
        free(tempa);
    }
    return count;
}
int main(int argc, char *argv[]){
    int k = *argv[1] - '0';
    FILE* file_a = fopen(argv[2], "r");
    //fseek(file_a, 0, SEEK_END);
    int size_a = atoi(argv[3]);
    //fseek(file_a, 0, SEEK_SET);
    char* buffer_a = (char *)malloc(size_a + 1);
    fread(buffer_a, 1, size_a, file_a);
    //fgets(buffer_a, size_a, file_a);
    fclose(file_a);
    printf("unprocessed file a: \n");
    printf("%s", buffer_a);
    putchar('\n');

    FILE* file_b = fopen(argv[4], "r");
    //fseek(file_b, 0, SEEK_END);
    int size_b = atoi(argv[5]);
    //fseek(file_b, 0, SEEK_SET);
    char* buffer_b = (char*) malloc(size_b + 1);
    fread(buffer_b, size_b, 1, file_b);
    //fgets(buffer_a, size_a, file_a);
    printf("unprocessed file b: \n");
    printf("%s", buffer_b);
    fclose(file_b);
    putchar('\n');

    preprocessed(buffer_a);
    printf("processed file a: \n");
    printf("%s", buffer_a);
    size_a = strlen(buffer_a);
    //printf("\n%d\n size a", sizea);
    putchar('\n');

    preprocessed(buffer_b);
    printf("processed file b: \n");
    printf("%s", buffer_b);
    size_b = strlen(buffer_b);
    printf("\n%d\n size b", size_b);
    putchar('\n');
    //int counter = ctr(k, buffer_a, buffer_b);
    //printf("counter is: %d\n", counter);

    double result = (double) ctr(k, buffer_a, buffer_b) / (double) (size_a - k + 1);
    putchar('\n');
    printf("Similarity = %f", result);

    // free your buffer_a
    free(buffer_a);
    free(buffer_b);
}
