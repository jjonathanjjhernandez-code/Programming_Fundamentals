#include <stdio.h>
#include <stdlib.h>
int main(){
    //File pointer to store the value by fopen
    FILE *file_ptr;
    //opening the file in read mode...make sure the file
    //you want to open exists in same directory as c file
    file_ptr = fopen("digital_input.txt","r");
    //checking if the file is opened successfully
    if(file_ptr==NULL){
        printf("The file is not opened");
    }else{
        printf("HELO!");
    }
    return 0;
}
/*
FILE* fopen(*file_name, *access_mode);
file_name: name of the file when present in the same directory as the source file. Otherwise, full path.
access_mode: Specifies for what operation the file is being opened.

If the file is opened successfully, returns a file pointer to it.
If the file is not opened, then returns NULL
PLUS multiple opening modes check out{https://www.geeksforgeeks.org/c/basics-file-handling-c/}

*/