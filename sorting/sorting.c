#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_ARGS (3)
#define FILE_INDEX (1)
#define NUM_INDEX (2)
#define MAX_INPUT (1000)
#define MAX_LENGTH (100)

void numArgCheck(int argc, char *fileName, int numOfProducts);

void fileSetting(char *fileName, int numOfProducts);

void structSetting(FILE *readFile, int numOfProducts);

struct laptop{
    char brand[MAX_LENGTH];
    float price;
};

int main(int argc, char *argv[]){
    numArgCheck(argc, argv[FILE_INDEX], argv[NUM_INDEX]);
    return 0;
}

/**
 * Checks the number of arguments and terminates the program
 * if it's not equal to the expected number, 3
 * @param argc
 * @param fileName
 */
void numArgCheck(int argc, char *fileName, int numOfProducts) {
    if (argc != NUM_OF_ARGS) {
        printf("The number of arguments is not the expected number, 3.\n");
        exit(EXIT_SUCCESS);
    }

    fileSetting(fileName, numOfProducts);
}

/**
 * Opens the input file and creates a temp file.
 * Terminates the program if either is NULL
 * @param fileName
 */
void fileSetting(char *fileName, int numOfProducts) {
    FILE *readFile = fopen(fileName, "r");

    if (readFile == NULL) {
        printf("\nError! Cannot open file(s)\n");
        exit(EXIT_SUCCESS);
    }

    structSetting(readFile, numOfProducts);
}

void structSetting(FILE *readFile, int numOfProducts){
    char eachLine[MAX_LENGTH];
    struct laptop each_laptop[MAX_INPUT];
    int structIndex = 0;

    while(fgets(eachLine, MAX_LENGTH, readFile) != NULL){
        sscanf(eachLine, "%s %f", each_laptop[structIndex].brand, &each_laptop[structIndex].price);

        printf("%s ", each_laptop[structIndex].brand);
        printf("%f\n", each_laptop[structIndex].price);
        structIndex++;
    }
}

void sortProducts(int numOfProducts){

}
