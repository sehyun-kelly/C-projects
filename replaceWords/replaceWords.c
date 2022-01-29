#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1000

void fileSetting(char* fileName);
void replaceWords(char* fileName, FILE* readFile, FILE* writeFile);

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("The number of arguments is not the expected number, 2.\n");
        assert(argc == 2);
    }

    char* fileName = argv[1];
    fileSetting(fileName);
    return 0;
}

//read file and write file okay
void fileSetting(char* fileName) {
    FILE *readFile = fopen(fileName, "r");
    FILE *writeFile = fopen("temp.txt", "w");

    if (readFile == NULL || writeFile == NULL) {
        printf("Error! Cannot open file(s)");
        exit(EXIT_SUCCESS);
    }

    replaceWords(fileName, readFile, writeFile);
}

void replaceWords(char* fileName, FILE* readFile, FILE* writeFile){
    char readString[MAX_LINE_SIZE];
    char

    //fgets - read each line okay, fputs - put into temp.txt okay
    while(fgets(readString, MAX_LINE_SIZE, readFile) != NULL){
        printf("%s\n", readString);
        fputs(readString, writeFile);
    }

    //is there any maximum length for newWord?
    //MAX_LINE_SIZE anything?
}