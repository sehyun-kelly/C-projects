#include <stdio.h>

#define MAX_NUMBER_OF_WORDS (85)
#define MAX_WORD_LENGTH (19)

void justifyAndPrintParagraph(char *paragraph, int lineLength);

int numOfWords(char *paragraph, char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int *numChar);

int nextNumOfWords(int *numChar, int processedWords, int totalWords, int lineLength);

void formatLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
                int wordsForNextLine, int processedWords, int lineLength);

void numWhiteSpace(int *whiteSpaces, int totalSpace, int numPositions, double numSpaces);

void printLine(char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
               int* whiteSpaces, int wordsForNextLine, int processedWords);

int main() {
    //commenting out my own test cases
//    int lineLength;
//
//    char test1[] = "I am here to learn C programming. This is my first assignment. Wish me luck!";
//    printf("[Test Case 1 : %s]\n\n", test1);
//
//    lineLength = 30;
//    printf("Line Length: %d\n", lineLength);
//    justifyAndPrintParagraph(test1, lineLength);
//    printf("\n");
//
//    lineLength = 50;
//    printf("Line Length: %d\n", lineLength);
//    justifyAndPrintParagraph(test1, lineLength);
//    printf("\n");
//
//    char test2[] = "Many of failures are people who did not realize how "
//                   "close they were to success when they gave up.";
//    printf("[Test Case 2 : %s]\n\n", test2);
//
//    lineLength = 8;
//    printf("Line Length: %d\n", lineLength);
//    justifyAndPrintParagraph(test2, lineLength);
//    printf("\n");
//
//    lineLength = 100;
//    printf("Line Length: %d\n", lineLength);
//    justifyAndPrintParagraph(test2, lineLength);
//    printf("\n");
//
//    char test3[] = "People who succeed have momentum. The more they succeed, the more they want to succeed, "
//                   "and the more they find a way to succeed. Similarly, when someone is failing, "
//                   "the tendency is to get on a downward spiral that can even become a self-fulfilling prophecy.";
//    printf("[Test Case 3 : %s]\n\n", test3);
//
//    lineLength = 20;
//    printf("Line Length: %d\n", lineLength);
//    justifyAndPrintParagraph(test3, lineLength);
//    printf("\n");
//
//    lineLength = 150;
//    printf("Line Length: %d\n", lineLength);
//    justifyAndPrintParagraph(test3, lineLength);
//    printf("\n");
//
//
//    char test4[] = "    I like C. I live Java. I like programming. What's not to like?    ";
//    lineLength = 12;
//    printf("Line Length: %d\n", lineLength);
//    justifyAndPrintParagraph(test4, lineLength);
//    printf("\n");
//
//    lineLength = 100;
//    printf("Line Length: %d\n", lineLength);
//    justifyAndPrintParagraph(test4, lineLength);
//    printf("\n");

    char paragraph1[] = "            Hi everyone. This is          the 2nd assignment. Please make sure you start early as this is going to take some time!     ";
    char paragraph2[] = "This is a normal sentence with no extra whitespace.";
    char paragraph3[] = "";
    char paragraph4[] = " This is     a sentence  with      random    whitespace.     ";
    char paragraph5[] = "          This is a sentence with only leading whitespace and no ending whitespace.";
    char paragraph6[] = "This is a sentence with only trailing whitespace and no leading whitespace.            ";

    printf("==========================SAMPLE TEST CASES FROM ASSIGNMENT 1==========================\n\n");
    printf("===Input string: '%s'===\n", paragraph1);
    printf("\n");
    justifyAndPrintParagraph(paragraph1, 15);
    printf("\n");
    justifyAndPrintParagraph(paragraph1, 25);
    printf("\n");
    justifyAndPrintParagraph(paragraph1, 35);
    printf("\n");
    justifyAndPrintParagraph(paragraph1, 100);
    printf("\n");
    justifyAndPrintParagraph(paragraph1, 120);

    printf("\n");
    printf("===Input string: '%s'===\n", paragraph2);
    justifyAndPrintParagraph(paragraph2, 15);
    printf("\n");
    justifyAndPrintParagraph(paragraph2, 25);
    printf("\n");
    justifyAndPrintParagraph(paragraph2, 35);
    printf("\n");
    justifyAndPrintParagraph(paragraph2, 100);

    printf("\n");
    printf("===Input string: '%s'===\n", paragraph3);
    printf("\n");
    justifyAndPrintParagraph(paragraph3, 15);

    printf("\n");
    printf("===Input string: '%s'===\n", paragraph4);
    printf("\n");
    justifyAndPrintParagraph(paragraph4, 15);
    printf("\n");
    justifyAndPrintParagraph(paragraph4, 25);
    printf("\n");
    justifyAndPrintParagraph(paragraph4, 35);

    printf("\n");
    printf("===Input string: '%s'===\n", paragraph5);
    printf("\n");
    justifyAndPrintParagraph(paragraph5, 15);
    printf("\n");
    justifyAndPrintParagraph(paragraph5, 25);
    printf("\n");
    justifyAndPrintParagraph(paragraph5, 35);
    printf("\n");
    justifyAndPrintParagraph(paragraph5, 50);

    printf("\n");
    printf("===Input string: '%s'===\n", paragraph6);
    printf("\n");
    justifyAndPrintParagraph(paragraph6, 15);
    printf("\n");
    justifyAndPrintParagraph(paragraph6, 25);
    printf("\n");
    justifyAndPrintParagraph(paragraph6, 35);
    printf("\n");
    justifyAndPrintParagraph(paragraph6, 50);

    printf("==========================SAMPLE TEST CASES FROM ASSIGNMENT 1_ver2==========================\n\n");
    char paragraph[] = "Hi everyone. This is the 2nd assignment. "
                       "Please make sure you start early as this is going to take some time!";

    char paragraphLeadingSpaces[] = "   Hi everyone. This is the 2nd assignment. "
                                    "Please make sure you start early as this is going to take some time!";

    char paragraphTrailingSpaces[] = "Hi everyone. This is the 2nd assignment. "
                                     "Please make sure you start early as this is going to take some time!    ";

    char paragraphTrailingAndLeadingSpaces[] = "      Hi everyone. This is the 2nd assignment. "
                                               "Please make sure you start early as this is going to take some time!    ";

    char paragraphMiddleSpaces[] = "Hi everyone. This is the           2nd assignment. "
                                   "Please make sure you start early as this is going to take some time!    ";

    char singleLetters[] = " s i n g l e  l e t t e r s .";

    /* The following variables are used for the error unit tests on lines 220 - 224 */
    char wordExceedsMAX_WORD_LENGTH[] = "Hieveryone.Thisisthe2nd assignment.";

    char paragraphExceedsMAX_NUMBER_OF_WORDS[] = "Hi everyone. This is the 2nd assignment. "
                                                 "Please make sure you start early as this is going to take some time!"
                                                 "Hi everyone. This is the 2nd assignment. "
                                                 "Please make sure you start early as this is going to take some time!"
                                                 "Hi everyone. This is the 2nd assignment. "
                                                 "Please make sure you start early as this is going to take some time!"
                                                 "Hi everyone. This is the 2nd assignment. "
                                                 "Please make sure you start early as this is going to take some time!"
                                                 "Hi everyone. This is the 2nd assignment. "
                                                 "Please make sure you start early as this is going to take some time!"
                                                 "Hi everyone. This is the 2nd assignment. "
                                                 "Please make sure you start early as this is going to take some time!"
                                                 "Hi everyone. This is the 2nd assignment. "
                                                 "Please make sure you start early as this is going to take some time!"
                                                 "Hi everyone. This is the 2nd assignment. "
                                                 "Please make sure you start early as this is going to take some time!";

    char tokenExceedsLineLength[] = "Hi everyone. This is the 2nd assignment.";

    /* Unit Tests */
    justifyAndPrintParagraph(paragraph, 11);
    printf("\n");
    justifyAndPrintParagraph(paragraph, 25);
    printf("\n");
    justifyAndPrintParagraph(paragraph, 35);
    printf("\n");
    justifyAndPrintParagraph(paragraph, 100);
    printf("\n");
    justifyAndPrintParagraph(paragraph, 120);
    printf("\n");
    justifyAndPrintParagraph(paragraphLeadingSpaces, 35);
    printf("\n");
    justifyAndPrintParagraph(paragraphTrailingSpaces, 35);
    printf("\n");
    justifyAndPrintParagraph(paragraphMiddleSpaces, 35);
    printf("\n");
    justifyAndPrintParagraph(paragraphTrailingAndLeadingSpaces, 35);
    printf("\n");
    justifyAndPrintParagraph(singleLetters, 35);
    printf("\n");

    printf("==========================SAMPLE TEST CASES FROM RUBRIC FOR ASSIGNMENT 1==========================\n\n");
    char testParagraph[] = "         I am here to learn C programming. This is my first assignment.   It took longer than I expected.   Wish me luck!!     ";
    char testParagraph2[] = "Reading short stories in English is a great way to improve your language level. You will improve your reading fluency and comprehension and develop your vocabulary.";
    char testParagraph3[] = "          This is a sentence with only leading whitespace and no ending whitespace.";
    char testParagraph4[] = "This is a sentence with only trailing whitespace and no leading whitespace.            ";

    printf("===Input: '%s'===\n", testParagraph);
    printf("\n");

    justifyAndPrintParagraph(testParagraph, 30);
    printf("\n");
    justifyAndPrintParagraph(testParagraph, 50);
    printf("\n");
    justifyAndPrintParagraph(testParagraph, 85);
    printf("\n");
    justifyAndPrintParagraph(testParagraph, 120);

    printf("\n");
    printf("===Input: '%s'===\n", testParagraph2);
    justifyAndPrintParagraph(testParagraph2, 15);
    printf("\n");
    justifyAndPrintParagraph(testParagraph2, 25);
    printf("\n");
    justifyAndPrintParagraph(testParagraph2, 100);

    printf("\n");
    printf("===Input: '%s'===\n", testParagraph3);
    printf("\n");
    justifyAndPrintParagraph(testParagraph3, 15);

    printf("\n");
    printf("===Input string: '%s'===\n", testParagraph4);
    printf("\n");
    justifyAndPrintParagraph(testParagraph4, 25);
    printf("\n");
    justifyAndPrintParagraph(testParagraph4, 95);

    return 0;
}

// stores the paragraph into 2d array and formats each line to print
void justifyAndPrintParagraph(char *paragraph, int lineLength) {
    char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH];
    int numChar[MAX_NUMBER_OF_WORDS];
    int totalWords = numOfWords(paragraph, words, numChar);
    int processedWords = 0;

    while (processedWords < totalWords) {
        int wordsForNextLine = nextNumOfWords(numChar, processedWords, totalWords, lineLength);
        formatLine(words, wordsForNextLine, processedWords, lineLength);
        processedWords += wordsForNextLine;
    }
}

// stores every word from paragraph in words array and returns the number of total words
int numOfWords(char *paragraph, char words[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH], int* numChar) {
    int indexWords = 0;
    int numOfChar = 0;
    const char *ptr = paragraph;

    while (*ptr != '\0') {
        while(*ptr == ' '){
            ptr ++;
        }
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

        while (*ptr == ' ') {
            ptr ++;
        }
    }

    return indexWords;
}

// returns the total number of words to be printed on the next line
int nextNumOfWords(int *numChar, int processedWords, int totalWords, int lineLength) {
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
// and executes two functions that compute the white spaces to be inserted in between words and print accordingly
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

