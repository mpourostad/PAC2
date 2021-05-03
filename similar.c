#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Function:  removeSpaces 
 * --------------------
 * converts multiple space charcters to one.
 *
 *  char* str: the array of chars to shrink its possible multiple space
 *                charcters to one.
 * 
 *  no return
 */
void removeSpaces(char* str) {
    int i, j;
    for(i=j=0; str[i]; ++i){
        if(!isspace(str[i]) || (i > 0 && !isspace(str[i-1]))){
            str[j++] = str[i];
        }
    }    
  str[j] = '\0';
}

/*
 * Function:  partOfArray 
 * --------------------
 * creates a substring from the given array of chars.
 *
 *  char *origin: the array of char to assign some of its elements to the new array (substring).
 * 
 *  k: size of the array. (same as the size of substring).
 * 
 *  num: marking an element in the origin array that its value will be assigned to the 
 *       first elemen of the substring array.
 *
 *  returns: an array that contains some of the elements of the origin array.
 */
char *partOfArray(char *origin, int k, int num){
    char* substring = (char*) malloc(k + 1);
    for (int i = 0; i < k; i++ ){
        substring[i] = origin[num];
        num++;
    }
    substring[k] = '\0';
    return substring;
}
/*
 * Function:  preprocessed 
 * --------------------
 * tokenizing the given array of chars. converting possible upper case 
 * characters to lower case and dealing with special space characters 
 * (tab, new line, etc.).
 * 
 *  no return
 */

void preprocessed(char *str){
    for(int i = 0; i < strlen(str); i++){
        str[i] = tolower(str[i]);
        if(isspace(str[i])){
            str[i] = ' ';
        }
    }
    removeSpaces(str);  
}
/*
 * Function:  ctr 
 * --------------------
 * counting the number of matches between substrings of two given arrays.
 *
 *  char *a: the array containg the characters of the first given documents
 *           to compare the similarity of the second documents against it.
 *  char *b: the array containg the characters of the second given documents
 *           to compare its similarity against the first document. 
 * 
 *  returns number of matches found between substrings of "a" and "b". 
 */
int ctr(int k, char *a, char *b){
    int count = 0;
    int size_a = strlen(a);
    int size_b = strlen(b);
    int substring_a = size_a - k + 1;
    int substring_b = size_b - k + 1;

    for(int i = 0; i < substring_a ; i++){ 
        char *tempa = partOfArray(a, k, i);
        for(int j = 0; j < substring_b; j++){
            char *tempb = partOfArray(b, k, j);

            if (strcmp(tempa, tempb) == 0){
                count++;
            }
            free(tempb);
        }
        free(tempa);
    }
    return count;
}
int main(int argc, char *argv[]){
    if (argc < 6){
        printf("Please pass all the neccessary arguments");
    }
    else{
        // converting the length of substring from char to an int.
        int k = atoi(argv[1]);

        //reading the content of the first document into an array of chars (buffer_a).
        FILE* file_a = fopen(argv[2], "r");
        int size_a = atoi(argv[3]);
        char* buffer_a = (char *)malloc(size_a + 1);
        fread(buffer_a, 1, size_a, file_a);
        fclose(file_a);

        //reading the content of the second document into an array of chars (buffer_b).
        FILE* file_b = fopen(argv[4], "r");
        int size_b = atoi(argv[5]);
        char* buffer_b = (char*) malloc(size_b + 1);
        fread(buffer_b, 1, size_b, file_b);
        fclose(file_b);

        // calling the preprocessed function to tokenize first document.
        // changing the size_a variable after preprocessing in case the size of buffer_a changed.
        preprocessed(buffer_a);
        size_a = strlen(buffer_a);

        // calling the preprocessed function to tokenize the second document.
        preprocessed(buffer_b);
        
        /* measuring the similarity by dividing the number of matches to 
        the number of substrings in the first document. */
        double result = (double) ctr(k, buffer_a, buffer_b) / (double) (size_a - k + 1);
        printf("Similarity = %f", result);
        putchar('\n');

        free(buffer_a);
        free(buffer_b);
    }
}
