// Juho Koski 6.11.2025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// No dynamic memory allocation  
#define NOTDYNAMIC 250

void readFile(const char *inputFile);

int main(int argc, char *argv[]) {
    
    if (argc >=2) {
        // i is set to 1 because the first parameter is ./my-cat
        // This for-loop makes the readfile function read file contents one file by a time.
        for(int i=1; i< argc; i++){
            const char* inputFile=argv[i];
            readFile(inputFile);
        }
    }
    
    else {
        //no files no error messages?
        exit(0);
    }
 
    printf("\n");
    printf("Thank you for using the program! \n");
    return(0);
}


void readFile(const char *inputFile) {

    //initializing variables

    char row[NOTDYNAMIC] = "";
    FILE *File= NULL;

    // invalid file handling
    if ((File = fopen(inputFile, "r")) == NULL) {
        //perror ads newline \n automatically
        perror("my-cat: cannot open file");
        exit(1);
    }


    printf("File '%s' opened \n",inputFile);
    // reading the file until end of file
    while (fgets(row,NOTDYNAMIC,File) != NULL) {
        printf("%s",row);

    }

    fclose(File); // closing the file
    printf("File '%s' closed\n",inputFile);
    
}