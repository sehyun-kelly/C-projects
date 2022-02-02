#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE (100)
#define MAX_LINE_SIZE (1000)
#define TEMP_FILE_NAME "temp.txt"

void numArgCheck(int argc, char* fileName);
void wordInput(char* fileName);
void fileSetting(char* fileName, char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]);
void replaceWords(char* fileName, FILE* readFile, FILE* writeFile,
                  char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]);
void wordFound(int ifFound, char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]);
void updateFile(char* fileName, FILE* writeFile, char newString[MAX_LINE_SIZE]);

int main(int argc, char *argv[]){
    numArgCheck(argc, argv[1]);
    return 0;
}

void numArgCheck(int argc, char* fileName){
    if(argc != 2) {
        printf("The number of arguments is not the expected number, 2.\n");
        assert(argc == 2);
    }

    wordInput(fileName);
}

void wordInput(char* fileName){
    char oldWord[MAX_WORD_SIZE];
    char newWord[MAX_WORD_SIZE];
    char tempBuffer[MAX_WORD_SIZE];

    printf("Enter word to replace: ");

    //stdin okay?
    fgets(tempBuffer, MAX_WORD_SIZE, stdin);
    sscanf(tempBuffer, "%s", oldWord);
    printf("Replace \'%s\' with: ", oldWord);
    fgets(tempBuffer, MAX_WORD_SIZE, stdin);
    sscanf(tempBuffer, "%s", newWord);

    if(strcmp(oldWord, newWord) == 0){
        printf("\nOld word is the same as new word\n");
        exit(EXIT_SUCCESS);
    }

    fileSetting(fileName, oldWord, newWord);
}

void fileSetting(char* fileName, char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]) {
    FILE *readFile = fopen(fileName, "r");
    FILE *writeFile = fopen(TEMP_FILE_NAME, "w");

    if (readFile == NULL || writeFile == NULL) {
        printf("\nError! Cannot open file(s)\n");
        exit(EXIT_SUCCESS);
    }

    replaceWords(fileName, readFile, writeFile, oldWord, newWord);
}

void replaceWords(char* fileName, FILE* readFile, FILE* writeFile,
                  char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]){
    char readString[MAX_LINE_SIZE];
    char newString[MAX_LINE_SIZE];
    char* substring;
    int ifFound = 0;

    while(fgets(readString, MAX_LINE_SIZE, readFile) != NULL){
        substring = strstr(readString, oldWord);
        if(substring != NULL){
            ifFound = 1;
            strncat(newString, readString, strlen(readString) - strlen(substring));
            strcat(newString, newWord);
            for(int i = 0; i < strlen(oldWord); i++){
                substring++;
            }
            strcat(newString, substring);
        }else{
            strcat(newString, readString);
        }
    }

    wordFound(ifFound, oldWord, newWord);

    //to be deleted later
    if(ifFound == 1){
        printf("the new String is:\n%s\n", newString);
    }

    updateFile(fileName, writeFile, newString);
}

void wordFound(int ifFound, char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]){
    if(ifFound == 0){
        printf("\nCould not find \'%s\'\n", oldWord);
        exit(EXIT_SUCCESS);
    } else{
        printf("Successfully replaced all occurrences of \'%s\' with \'%s\'\n", oldWord, newWord);
    }
}

void updateFile(char* fileName, FILE* writeFile, char newString[MAX_LINE_SIZE]){
    fputs(newString, writeFile);

    if(remove(fileName) == 0){
        rename(TEMP_FILE_NAME, fileName);
    }
}

