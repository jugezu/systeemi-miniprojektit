// Juho Koski 7.11.2025
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
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    return(0);
}

//original funtion in reverse.c 
void readFile(const char *inputFile) {

    //initializing variables    
    int currentChar;
    int previousChar;
    int count = 0;

    FILE *File = fopen(inputFile, "r");

    // invalid file handling
    if (!File) {
        fprintf(stderr, "my-zip: cannot open file\n");
        exit(1);
    }

    // EOF = -1 
    previousChar= fgetc(File);
    if(previousChar==EOF){
        fclose(File);
        return;
    }
    count=1;

    // reading the file until end of file, EOF =-1
    while ((currentChar = fgetc(File)) != EOF){
        //checking if previous char is same as the current
        if(previousChar == currentChar){
            count=count+1;
        }
        // if previus is different write it to the file
        // help with fwrite: https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
        else{
            fwrite(&count,sizeof(int),1,stdout);
            fwrite(&previousChar,sizeof(char),1,stdout);

            // reset previous character to current character
            previousChar=currentChar;
            //reset count back to 1
            count=1;
        }
    }
    
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&previousChar, sizeof(char), 1, stdout);
    fclose(File); // close file
    
}