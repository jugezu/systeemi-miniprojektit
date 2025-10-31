#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// help with getline: https://c-for-dummies.com/blog/?p=1112

char **readFile(const char *inputFile, size_t *rows);
void writeFile(const char *outputFile, char **data, size_t rows);
void printStdout(char **data, size_t rows);

int main(int argc, char *argv[]) {
    size_t rows = 0;
    int args=0;
    
    if (argc == 2) {
        // Only input file is provided
        const char* inputFile=argv[1];
        char **data = readFile(inputFile, &rows);
        printStdout(data,rows);

         // releasing allocated memory
        for (size_t i = 0; i < rows; i++) {
            free(data[i]);
        }
        free(data);

    
    } else if (argc == 3) {
        // Input and output file
        const char* inputFile=argv[1];
        const char* outputFile=argv[2];

        //Input is the same as output
        if(*inputFile==*outputFile){
            fprintf(stderr,"Input and output file must differ \n");
            exit(1);
        }

        char **data = readFile(inputFile, &rows);

        writeFile(outputFile, data, rows);
        

        // releasing allocated memory
        for (size_t i = 0; i < rows; i++) {
            free(data[i]);
        }
        free(data);
        

    
    }
    else {
        fprintf(stderr,"usage: reverse <input> <output>\n");
        exit(1);
    }
    printf("\n");
    printf("Thank you for using the program! \n");
}

char **readFile(const char *inputFile, size_t *rows) {

    //initializing variables
    char **data=NULL;
    char *aRow=NULL;
    size_t len= 0;
    __ssize_t read;
    // keeping data how many rows are in the file
    *rows = 0;

    FILE *File = fopen(inputFile, "r");

    // invalid file handling
    if (!File) {
        fprintf(stderr, "error: cannot open file '%s'\n",inputFile);
        exit(1);
    }


    // reading the file until end of file
    while ((read = getline(&aRow, &len, File)) != -1) {
        //increasing the size of the data array to hold one more lines
        data = realloc(data, (*rows+1)*sizeof(char*));

        if (!data) {
            fprintf(stderr,"realloc failed \n");
            exit(1);
        }

        // now allocating memory for the line we read
        data[*rows]=malloc(read+1);
        if (!data[*rows]) {

            fprintf(stderr,"malloc failed \n");
            exit(1);

        }
        // copy the line read by getline into allocated memory
        strcpy(data[*rows], aRow);
        (*rows)++;
    }

    free(aRow); // free memory
    fclose(File); // close file
    return data;
}


// used if 2 arguments
void writeFile(const char *outputFile, char **data, size_t rows) {
    FILE *File = fopen(outputFile, "w");

    // invalid file handling 
    if (!File) {
        fprintf(stderr, "error: cannot open file '%s'\n", outputFile);
        exit(1);
    }

    // writing file in reverse 
    for (__ssize_t i=rows - 1; i >= 0; i--) {
        fprintf(File, "%s", data[i]);
    }

    fclose(File);

}


// used if 1 argument
void printStdout(char **data, size_t rows) {
    for (__ssize_t i = rows - 1; i >= 0; i--) {
        fprintf(stdout, "%s", data[i]);
    }
    
}
