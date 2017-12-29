/*
Name: Donovan Troshynski
Assignment #: 4
Instructor: Raj Dasgupta
Due Date: 28 April 2016 @ 11:59 PM
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmpWords(const void *, const void*);

struct sortedWords
{
    char *string;
    int count;
};

int main(int argc, char *argv[])
{
    int space, fileNameLength, numWords, i, n;
    FILE *inFilePtr;
    FILE *outFilePtr;
    FILE *wordFilePtr;
    char *fileName = argv[2];

    struct sortedWords **wordList = (struct sortedWords **) malloc(sizeof(struct sortedWords *));
    if(wordList == NULL)
    {
        printf("No more memory\n");
        return 1;
    }
    n = 0;

    /*Checks the number of arguments entered == 3*/
    if(argc != 3)
    {
        printf("Usage: a.exe <int> <filename>\n");
        return 1;
    }

    /*Checks that the amount of space desired is [25,100]*/
    if(atoi(argv[1]) < 25 || atoi(argv[1]) > 100)
    {
        puts("Number of characters should be between 25 and 100");
        return 1;
    }

    /*Initializes a variable for the amount of space and for the length of the file name given*/
    space = atoi(argv[1]);
    fileNameLength = (int)strlen(argv[2]);

    /*Opens and given file and reads from it*/
    if((inFilePtr = fopen(argv[2], "r")) != NULL)
    {
        /*input: where word read in from file is stored*/
        char input[20];
        char output[100] = {'\0'};
        char *word;
        int wordLength, outLength, flag;
        int same;
        char *outFileName;

        same = -1;

        /*Creates and opens the word count file using the name of the input file + ".words"*/
        wordFilePtr = fopen(strcat(fileName, ".words"), "w");
        if(wordFilePtr == NULL)
        {
            printf("Error creating \"%s\" file\n", fileName);
            return 1;
        }
        argv[2][fileNameLength] = '\0';
        outFileName = strcat(fileName, ".out");

        /*Starts reading from the file, putting a space at the end of each word*/
        fscanf(inFilePtr, "%s", input);
        word = strtok(input, " ");
        strcat(word, " ");

        /*Creates and opens the output file using the name of the input file + ".out"*/
        outFilePtr = fopen(outFileName, "w");
        if(outFilePtr == NULL)
        {
            printf("Error creating \"%s\" file\n", outFileName);
            return 1;
        }

        /*flag is to know if the current word is the first word or not*/
        flag = 0;
        numWords = 0;
        while(!feof(inFilePtr))
        {
            /*Gets the name of the input file*/
            argv[2][fileNameLength] = '\0';

            /*Finds the length of the current word and the current length of output[]*/
            wordLength = (int)strlen(word);
            outLength = (int)strlen(output);

            if(flag == 0)
            {
                wordList = (struct sortedWords **) realloc(wordList, (n + 1) * sizeof(struct sortedWords *));
                wordList[n] = malloc(sizeof(struct sortedWords));
                wordList[n] -> string = (char *) malloc(strlen(word) + 1);
                strcpy(wordList[n] -> string, word);
                wordList[n] -> count = 1;
                n++;
            }

            /*Compares current word with words in wordList, if same word found don't add it to wordList*/
            numWords++;
            for(i = 0; i < n; i++)
            {
                if((strcmp(word, wordList[i] -> string) == 0) && (flag != 0))
                {
                    same = i;
                    wordList[i] -> count++;
                }
            }

            if((same < 0) && (flag != 0))
            {
                wordList = (struct sortedWords **) realloc(wordList, (n + 1) * sizeof(struct sortedWords **));
                wordList[n] = malloc(sizeof(struct sortedWords));
                wordList[n] -> string = (char *) malloc(strlen(word) + 1);

                strcpy(wordList[n] -> string, word);

                wordList[n] -> count = 1;
                n++;
            }
            same = -1;

            /*If this is the first word, merely copies it into output, otherwise appends it*/
            if((wordLength + outLength) < space + 1)
            {
                if(flag == 0)
                {
                    memcpy(output, word, 20);
                    flag = 1;
                }
                else
                {
                    strcat(output, word);
                }
            }
            else
            {
                /*Removes the space at the end of each line*/
                if(output[outLength - 1] == ' ')
                {
                    output[outLength - 1] = '\0';
                }
                /*Prints the words in output to the output file then clears output and writes the current word to it*/
                fprintf(outFilePtr, "%s\n", output);
                memset(output, '\0', 100);
                memcpy(output, word, space);
            }
            /*Gets the next word and appends a space to it*/
            fscanf(inFilePtr, "%s", input);
            word = strtok(input, " ");
            strcat(word, " ");
        }
        /*Prints any remaining contents of output to the output file, then closes both the input and output files*/
        fprintf(outFilePtr, "%s\n", output);
        fclose(inFilePtr);
        fclose(outFilePtr);
    }
    else
    {
        printf("File \"%s\" could not be opened\n", fileName);
        return 1;
    }

    qsort(wordList, n, sizeof(struct sortedWords *), cmpWords);
    for(i = 0; i < n; i++)
        fprintf(wordFilePtr, "%s- %d\n", wordList[i] -> string, wordList[i] -> count);
    fclose(wordFilePtr);

    return 0;
}

int cmpWords(const void *a, const void *b)
{
    const char *x = (*(struct sortedWords **)a) -> string;
    const char *y = (*(struct sortedWords **)b) -> string;

    return strcmp(x, y);
}
