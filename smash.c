// this file build the basics of the smash shell and prints $ sign to stderr
#include <stdio.h>
#include <string.h>
#include "smash.h"
#include "history.h"
#define MAXLINE 4096

int main(void){  
    setvbuf(stdout,NULL,_IONBF,0);
    setvbuf(stderr,NULL,_IONBF,0);
    char bfr[MAXLINE];
    char *bfrPointer = bfr;
    fputs("$ ",stderr); //Output the first prompt
    //initializes the history 
    init_history();
    //Loop reading commands until EOF or error
    while(fgets(bfr, MAXLINE,stdin) != NULL){
        bfr[strlen(bfr)-1] = '\0';
        executeCommand(bfrPointer);
        fputs("$ ",stderr);
    }
    return 0;
}
