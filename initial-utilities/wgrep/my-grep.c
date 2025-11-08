// Juho Koski 7.11.2025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void readFile(const char *inputFile, size_t *rows, char* searchTerm);
void readStdin(char* searchTerm);

int main(int argc, char *argv[]) {
    size_t rows = 0;
    
    if (argc >=3) {
        
        // i[0]= ./my-grep , i[1]= search term, i[2+n] = files 
        char *searchTerm = argv[1];
        
        for(int i=2; i< argc; i++){
            const char* inputFile=argv[i];
            

            readFile(inputFile, &rows, searchTerm);
            printf("\n");
            printf("File '%s' closed.\n",inputFile);
            printf("\n");
        }
    }
    else if(argc <3 && argc >=2){
        char *searchTerm = argv[1];
        readStdin(searchTerm);

    }
    
    else {
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    printf("Thank you for using the program!\n");
    return(0);
}

//original funtion in reverse.c 
void readFile(const char *inputFile, size_t *rows, char* searchTerm) {

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
        fprintf(stderr, "my-grep: cannot open file\n");
        exit(1);
    }

    printf("File '%s' opened.\n",inputFile);
    printf("\n");

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
        //How strstr works: https://stackoverflow.com/questions/17422217/strstr-to-find-a-word-in-a-string-using-c-returning-true-all-the-time
        //case sensitive, in != In
        if(strstr(aRow,searchTerm) != NULL){
            printf("%s",aRow);
        }
    }

    free(aRow); // free memory
    fclose(File); // close file
    
}

// Used if no files are given
void readStdin(char* searchTerm){
    char *aRow=NULL;
    size_t len= 0;
    __ssize_t read;

    // reading from standard input with getline
     while ((read = getline(&aRow, &len, stdin)) != -1) {
        
        //How strstr works: https://stackoverflow.com/questions/17422217/strstr-to-find-a-word-in-a-string-using-c-returning-true-all-the-time
        //case sensitive, in != In
        if(strstr(aRow,searchTerm) != NULL){
            printf("%s",aRow);
        }
    }

    free(aRow); // free memory
}