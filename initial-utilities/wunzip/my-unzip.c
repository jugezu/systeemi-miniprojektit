// Juho Koski 8.11.2025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(const char *inputFile);

int main(int argc, char *argv[]) {
    
    if (argc >=2) {
        
        // i[0]= ./my-zip , i[1]= inpput file i[2]= input file ...         
        for(int i=1; i< argc; i++){
            
            const char* inputFile=argv[i];
            
            readFile(inputFile);
        }
    }

    // no files are given    
    else {
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    return(0);
}

//This modifies zipped file to back to normal.
void readFile(const char *inputFile) {

    //initializing variables    
    char currentChar;
    int count = 0;

    // read mode changed to rb (read binary)
    FILE *File = fopen(inputFile, "rb");

    // invalid file handling
    if (!File) {
        fprintf(stderr, "my-zip: cannot open file\n");
        exit(1);
    }

    // help with while loop structure: https://stackoverflow.com/questions/66970935/understanding-zip-function-in-python-and-adapting-it-for-c 
    while (fread(&count, sizeof(int), 1, File) == 1 &&
       fread(&currentChar, sizeof(char), 1, File) == 1) {

    for (int i = 0; i < count; i++) {
        printf("%c", currentChar);
    }
}
    //printf("\n");
    fclose(File); // close file
}