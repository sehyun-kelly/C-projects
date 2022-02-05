#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE (100)
#define MAX_LINE_SIZE (1000)
#define TEMP_FILE_NAME "temp.txt"
#define NUM_OF_ARGS (2)
#define FILE_INDEX (1)

void numArgCheck(int argc, char *fileName);

void fileSetting(char *fileName);

void wordInput(char *fileName, FILE *readFile, FILE *writeFILE);

void replaceWords(char *fileName, FILE *readFile, FILE *writeFile,
                  char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]);

void wordFound(int ifFound, char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]);

void updateFile(char *fileName, FILE *writeFile, char newString[MAX_LINE_SIZE]);

int main(int argc, char *argv[]) {
    numArgCheck(argc, argv[FILE_INDEX]);
    return 0;
}

/**
 * Checks the number of arguments and terminates the program
 * if it's not equal to the expected number, 2
 * @param argc
 * @param fileName
 */
void numArgCheck(int argc, char *fileName) {
    if (argc != NUM_OF_ARGS) {
        printf("The number of arguments is not the expected number, 2.\n");
        assert(argc == NUM_OF_ARGS);
    }

    fileSetting(fileName);
}

/**
 * Opens the input file and creates a temp file.
 * Terminates the program if either is NULL
 * @param fileName
 */
void fileSetting(char *fileName) {
    FILE *readFile = fopen(fileName, "r");
    FILE *writeFile = fopen(TEMP_FILE_NAME, "w");

    if (readFile == NULL || writeFile == NULL) {
        printf("\nError! Cannot open file(s)\n");
        exit(EXIT_SUCCESS);
    }

    wordInput(fileName, readFile, writeFile);
}

/**
 * Prompts the user to enter the old word to be replaced
 * and a new word to replace the old word
 * @param fileName
 * @param readFile
 * @param writeFILE
 */
void wordInput(char *fileName, FILE *readFile, FILE *writeFILE) {
    char oldWord[MAX_WORD_SIZE];
    char newWord[MAX_WORD_SIZE];

    printf("Enter word to replace: ");

    fgets(oldWord, MAX_WORD_SIZE, stdin);
    if(oldWord[strlen(oldWord) - 1] == '\n'){
        oldWord[strlen(oldWord) - 1] = '\0';
    }

    printf("Replace \'%s\' with: ", oldWord);
    fgets(newWord, MAX_WORD_SIZE, stdin);
    if(newWord[strlen(newWord) - 1] == '\n'){
        newWord[strlen(newWord) - 1] = '\0';
    }

    replaceWords(fileName, readFile, writeFILE, oldWord, newWord);
}

/**
 * replaces the old word with the new word and creates a new string
 * @param fileName
 * @param readFile
 * @param writeFile
 * @param oldWord
 * @param newWord
 */
void replaceWords(char *fileName, FILE *readFile, FILE *writeFile,
                  char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]) {
    char readString[MAX_LINE_SIZE];
    char newString[MAX_LINE_SIZE];
    const char* ptrReadString;
    char *substring;

    int ifFound = 0;

    while (fgets(readString, MAX_LINE_SIZE, readFile) != NULL) {
        ptrReadString = readString;

        while(*ptrReadString != '\0'){
            substring = strstr(ptrReadString, oldWord);
            if(substring == NULL){
                strcat(newString, ptrReadString);
                ptrReadString += strlen(ptrReadString);
            } else{
                ifFound = 1;
                strncat(newString, ptrReadString, strlen(ptrReadString) - strlen(substring));
                strcat(newString, newWord);
                ptrReadString += (strlen(ptrReadString) - strlen(substring) + strlen(oldWord));
            }
        }
    }

    wordFound(ifFound, oldWord, newWord);

    updateFile(fileName, writeFile, newString);
}

/**
 * prints the message whether the old word exists in the string
 * and whether the replacement has been completed successfully
 * @param ifFound
 * @param oldWord
 * @param newWord
 */
void wordFound(int ifFound, char oldWord[MAX_WORD_SIZE], char newWord[MAX_WORD_SIZE]) {
    if (ifFound == 0) {
        printf("\nCould not find \'%s\'\n", oldWord);
        exit(EXIT_SUCCESS);
    } else {
        printf("Successfully replaced all occurrences of \'%s\' with \'%s\'\n", oldWord, newWord);
    }
}

/**
 * writes the new string into the temp file, removes the original file,
 * and renames the temp file as the name of the original
 * @param fileName
 * @param writeFile
 * @param newString
 */
void updateFile(char *fileName, FILE *writeFile, char newString[MAX_LINE_SIZE]) {
    fputs(newString, writeFile);

    if (remove(fileName) == 0) {
        rename(TEMP_FILE_NAME, fileName);
        fclose(writeFile);
    }
}

