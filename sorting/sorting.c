#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_ARGS (3)
#define FILE_INDEX (1)
#define NUM_INDEX (2)
#define MAX_INPUT (1000)
#define MAX_LENGTH (100)

struct laptop{
    char brand[MAX_LENGTH];
    float price;
};

void numArgCheck(int argc);
int fileSetting(char *fileName, char brandList[MAX_INPUT][MAX_LENGTH], float priceList[MAX_INPUT]);
void structSetting(int numOfProduct, long desiredOutput, struct laptop *each_laptop,
                   char brandList[MAX_INPUT][MAX_LENGTH], float priceList[MAX_INPUT]);
void display(struct laptop *each_laptop, int numOfProducts);
void swap(struct laptop *laptop1, struct laptop *laptop2);
int partition(struct laptop *each_laptop, int low, int high);
void quickSort(struct laptop *each_laptop, int low, int high);

int main(int argc, char *argv[]){
    numArgCheck(argc);

    long desiredOutputNum = strtol(argv[NUM_INDEX], NULL, 10);
    char brandList[MAX_INPUT][MAX_LENGTH];
    float priceList[MAX_INPUT];

    int numOfProducts = fileSetting(argv[FILE_INDEX], brandList, priceList);

    struct laptop *each_laptop = malloc(numOfProducts * sizeof (*each_laptop));
    if(each_laptop == NULL) {
        printf(" No memory is allocated.");
        exit(EXIT_SUCCESS);
    }

    structSetting(numOfProducts, desiredOutputNum, each_laptop, brandList, priceList);

    return 0;
}


/**
 * Checks the number of arguments and terminates the program
 * if it's not equal to the expected number, 3
 * @param argc
 * @param fileName
 */
void numArgCheck(int argc) {
    if (argc != NUM_OF_ARGS) {
        printf("The number of arguments is not the expected number, 3.\n");
        exit(EXIT_SUCCESS);
    }
}

/**
 * Opens the input file and creates a temp file.
 * Terminates the program if either is NULL
 * @param fileName
 */
int fileSetting(char *fileName, char brandList[MAX_INPUT][MAX_LENGTH], float priceList[MAX_INPUT]){
    FILE *readFile = fopen(fileName, "r");

    if (readFile == NULL) {
        printf("\nError! Cannot open file(s)\n");
        exit(EXIT_SUCCESS);
    }

    char eachLine[MAX_LENGTH];
    int index = 0;

    while(fgets(eachLine, MAX_LENGTH, readFile) != NULL){
        sscanf(eachLine, "%s %f", brandList[index], &priceList[index]);
        index++;
    }

    fclose(readFile);

    return index;
}

void structSetting(int numOfProduct, long desiredOutput, struct laptop *each_laptop,
        char brandList[MAX_INPUT][MAX_LENGTH], float priceList[MAX_INPUT]){
    for(int index = 0; index < numOfProduct; index++){
        strcpy(each_laptop[index].brand, brandList[index]);
        each_laptop[index].price = priceList[index];
    }

    int maxIndex = (int) desiredOutput;

    quickSort(each_laptop, 0, --numOfProduct);
    each_laptop = (struct laptop*) realloc(each_laptop, maxIndex * sizeof (*each_laptop));
    display(each_laptop, maxIndex);
    free(each_laptop);
}

void swap(struct laptop *laptop1, struct laptop *laptop2) {
    struct laptop temp = *laptop1;
    *laptop1 = *laptop2;
    *laptop2 = temp;
}

// function to find the partition position
int partition(struct laptop *each_laptop, int low, int high) {

    // select the rightmost element as pivot
    float pivot = each_laptop[high].price;

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (each_laptop[j].price <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&each_laptop[i], &each_laptop[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&each_laptop[i + 1], &each_laptop[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(struct laptop *each_laptop, int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(each_laptop, low, high);

        // recursive call on the left of pivot
        quickSort(each_laptop, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(each_laptop, pi + 1, high);
    }
}

void display(struct laptop *each_laptop, int numOfProducts){
    for (int index = 0; index < numOfProducts; index++) {
        printf("%s %.0f\n", each_laptop[index].brand, each_laptop[index].price);
    }
    printf("\n");
}
