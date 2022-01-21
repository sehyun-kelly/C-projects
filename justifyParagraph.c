//
// Assignment 1
// Name: Sehyun Park
// Student ID: A01278596
//
#include <stdio.h>

#define MAX_NUMBER_OF_WORDS (85)
#define MAX_WORD_LENGTH (19)

void justifyAndPrintParagraph(char *paragraph, int lineLength);

int numOfWords(char *paragraph, char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], char numChar[MAX_NUMBER_OF_WORDS]);

int nextNumOfWords(char numChar[MAX_NUMBER_OF_WORDS], int processedWords, int totalWords, int lineLength);

void formatLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
                int wordsForNextLine, int processedWords, int lineLength);

void numWhiteSpace(int *whiteSpaces, int totalSpace, int numPositions, double numSpaces);

void printLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
               int* whiteSpaces, int wordsForNextLine, int processedWords);

int main() {
    char paragraph[] = "I am here to learn C programming. This is my first assignment. Wish me luck!";
    char paragraph2[] = "Hi everyone. This is the 2nd assignment. Please make sure you start early as this is going to take some time!";

    justifyAndPrintParagraph(paragraph, 30);
    justifyAndPrintParagraph(paragraph, 50);
    justifyAndPrintParagraph(paragraph2, 25);
    justifyAndPrintParagraph(paragraph2, 40);

    return 0;
}

// stores the paragraph into 2d array and formats each line to print
void justifyAndPrintParagraph(char *paragraph, int lineLength) {
    char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH];
    char numChar[MAX_NUMBER_OF_WORDS];
    int totalWords = numOfWords(paragraph, words, numChar);
    int processedWords = 0;

    while (processedWords < totalWords) {
        int wordsForNextLine = nextNumOfWords(numChar, processedWords, totalWords, lineLength);
        formatLine(words, wordsForNextLine, processedWords, lineLength);
        processedWords += wordsForNextLine;
    }
}

// stores every word from paragraph in words array and returns the number of total words
int numOfWords(char *paragraph, char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], char numChar[MAX_NUMBER_OF_WORDS]) {
    int indexWords = 0;
    int numOfChar = 0;
    const char *ptr = paragraph;

    while (*ptr != '\0') {
        numOfChar = 0;
        while (*ptr != ' ' && *ptr != '\0') {
            words[indexWords][numOfChar] = *ptr;
            numOfChar++;
            ptr++;
        }
        words[indexWords][numOfChar] = '\0';

        //stores the number of characters in each word in numChar array
        numChar[indexWords] = numOfChar;
        indexWords++;

        if (*ptr != '\0') {
            ptr++;
        }
    }

    return indexWords;
}

// returns the total number of words to be printed on the next line
int nextNumOfWords(char numChar[MAX_NUMBER_OF_WORDS], int processedWords, int totalWords, int lineLength) {
    int index = processedWords;
    int count = 0;
    int result;

    while (count < lineLength && index < totalWords) {
        count += numChar[index];
        count++;
        index++;
    }

    if (lineLength >= (count-1)){
        result = index - processedWords;
    } else {
        result = index - 1 - processedWords;
    }

    return result;
}

// calculates the total number of spaces needed in one line
// and executes two functions that compute the white spaces needed in between words and print accordingly
void formatLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
                int wordsForNextLine, int processedWords, int lineLength) {
    int rowNum = processedWords;
    int count = 0;

    for (int i = 0; i < wordsForNextLine; i++) {
        int colNum = 0;
        while (words[rowNum][colNum] != '\0') {
            count++;
            colNum++;
        }
        rowNum++;
    }

    int totalSpace = lineLength - count;
    int numPositions = wordsForNextLine - 1;
    int whiteSpaces[numPositions];
    double numSpaces = totalSpace / numPositions;

    numWhiteSpace(whiteSpaces, totalSpace, numPositions, numSpaces);
    printLine(words, whiteSpaces, wordsForNextLine, processedWords);
}

// Calculates the number of white spaces needed in between words
void numWhiteSpace(int *whiteSpaces, int totalSpace, int numPositions, double numSpaces) {
    int lastIndex = numPositions - 1;
    int totalWhiteSpaces = totalSpace;
    int positionIndex = numPositions;

    while (totalWhiteSpaces > 0 && lastIndex > 0) {
        if (totalWhiteSpaces % positionIndex == 0) {
            for (int i = 0; i < positionIndex; i++) {
                whiteSpaces[i] = (int) numSpaces;
            }
            totalWhiteSpaces = 0;
            lastIndex = 0;
        } else {
            whiteSpaces[lastIndex] = (int) numSpaces;
            totalWhiteSpaces -= whiteSpaces[lastIndex];
            lastIndex--;
            positionIndex--;
        }
    }

    whiteSpaces[0] = totalSpace;
    for (int i = 1; i < numPositions; i++) {
        whiteSpaces[0] -= whiteSpaces[i];
    }
}

// prints each line
void printLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
               int* whiteSpaces, int wordsForNextLine, int processedWords){
    int rowNum = processedWords;

    for (int i = 0; i < wordsForNextLine; i++) {
        printf("%s", words[rowNum]);
        if (i != wordsForNextLine - 1) {
            for (int j = 0; j < whiteSpaces[i]; j++) {
                printf(" ");
            }
        }
        rowNum++;
    }
    printf("\n");
}

