#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_ARGS (3)
#define FILE_INDEX (1)
#define NUM_INDEX (2)
#define MAX_LENGTH (100)
#define NUM_SPACE (15)

typedef struct laptop {
    char brand[MAX_LENGTH];
    float price;
} Laptop;

void numArgCheck(int argc);

void fileSetting(char *fileName, Laptop *each_laptop, long desiredOutput);

void display(struct laptop *each_laptop, int totalProduct, int numProductPrint);

int comparePrice(const void *p, const void *q);

Laptop *laptop_realloc(Laptop *each_laptop, int numProducts);

int main(int argc, char *argv[]) {
    numArgCheck(argc);
    Laptop *each_laptop = (Laptop *) malloc(sizeof(*each_laptop));
    if (each_laptop == NULL) {
        printf("No memory is allocated.");
        exit(EXIT_SUCCESS);
    }
    long desiredOutputNum = strtol(argv[NUM_INDEX], NULL, 10);

    fileSetting(argv[FILE_INDEX], each_laptop, desiredOutputNum);

    return 0;
}

/**
 * Checks the number of arguments and terminates the program
 * if it's not equal to the expected number, 3
 * @param argc
 */
void numArgCheck(int argc) {
    if (argc != NUM_OF_ARGS) {
        printf("The number of arguments is not the expected number, 3.\n");
        exit(EXIT_SUCCESS);
    }
}

/**
 * Opens the input file, read the input and store them into struct laptop
 * Also sorts the struct data by price using quick sort function
 * Terminates the program if either is NULL
 * @param fileName
 * @param brandList
 * @param priceList
 */

void fileSetting(char *fileName, Laptop *each_laptop, long desiredOutput) {
    FILE *readFile = fopen(fileName, "r");
    if (readFile == NULL) {
        printf("\nError! Cannot open file(s)\n");
        exit(EXIT_SUCCESS);
    }

    int numProducts = 0;
    char eachLine[MAX_LENGTH];

    while (fgets(eachLine, MAX_LENGTH, readFile) != NULL) {
        numProducts++;
        each_laptop = laptop_realloc(each_laptop, numProducts);
        char price[MAX_LENGTH];
        sscanf(eachLine, "%s %s", each_laptop[numProducts - 1].brand, price);
        each_laptop[numProducts - 1].price = strtof(price, NULL);
    }
    //Using quick sort to sort the struct by price
    qsort(each_laptop, numProducts, sizeof(*each_laptop), comparePrice);
    display(each_laptop, numProducts, (int) desiredOutput);
    fclose(readFile);
    free(each_laptop);
}

/**
 * Returns the difference between two prices of struct
 * helper method to support qsort function
 * @param p void*
 * @param q void*
 * @return int
 */
int comparePrice(const void *p, const void *q) {
    float firstPrice = ((struct laptop *) p)->price;
    float secondPrice = ((struct laptop *) q)->price;

    return (int) (firstPrice - secondPrice);
}

/**
 * Reallocates the memory of struct to increase with numProducts
 * @param each_laptop Laptop*
 * @param numProducts int
 * @return Laptop*
 */
Laptop *laptop_realloc(Laptop *each_laptop, int numProducts){
    each_laptop = (Laptop *) realloc(each_laptop, sizeof(*each_laptop) * numProducts);
    if (each_laptop == NULL) {
        printf("No memory is allocated");
        exit(EXIT_SUCCESS);
    }

    return each_laptop;
}

/**
 * display laptop product information for the number of "numProductPrint"
 * @param each_laptop
 * @param numOfProducts
 */
void display(struct laptop *each_laptop, int totalProduct, int numProductPrint) {
    int numProduct = totalProduct < numProductPrint ? totalProduct : numProductPrint;

    printf("Brand");
    for (int tab = 0; tab < NUM_SPACE - strlen("Brand"); tab++) { printf(" "); }
    printf("Price\n");

    for (int index = 0; index < numProduct; index++) {
        printf("%s", each_laptop->brand);
        for (int tab = 0; tab < NUM_SPACE - strlen(each_laptop->brand); tab++) { printf(" "); }
        printf("%.2f\n", each_laptop->price);
        each_laptop++;
    }
    printf("\n");
}
