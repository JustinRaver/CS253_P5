//this file builds the history for the smash shell
//it utilizes the prototypes defined in smash.h to track the history of the shell
//
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

struct Cmd *history[MAXHISTORY];
int currentCmd;
int oldestCmd;
int cmdCapacity;
int totalArgs;
char overWriteSeq[] = "this memory has been overwritten for safety";

void init_history(void){
    currentCmd = 0; //keep track of the current cmd number 
    oldestCmd = 0;  //keep track of the index of the oldest cmd
    cmdCapacity = 0;//keep track of cmdCapacity 
    totalArgs = 0;
    int i;
    for(i=0; i<MAXHISTORY; i++){//initialize the structs for the ten cdms stored in history
        history[i] = malloc(sizeof(struct Cmd));
    }
}

void add_history(char *cmd, int exitStatus){
    if(currentCmd > MAXHISTORY){//if there are more then 10 cmds then keep track of oldest cmd
        oldestCmd = (currentCmd % MAXHISTORY) +1;
    }
    if(currentCmd >= MAXHISTORY){
        free(history[currentCmd % MAXHISTORY] -> cmd);
    }
    if(currentCmd < MAXHISTORY){//increment cmdCapacity up to 10 which means capacity is full
       cmdCapacity++;
    }
 
    history[currentCmd % MAXHISTORY] -> cmd = strdup(cmd);	//add the cmd to the cmd struct
    history[currentCmd % MAXHISTORY] -> exitStatus = exitStatus;//add the exit status to the cmd struct
    currentCmd++;//increment the current arg number
}

void clear_history(void){
    int i;
    for(i=0; i < MAXHISTORY; i++){
        free(history[i] -> cmd);
        history[i] -> cmd = overWriteSeq;//overwrite the cmd and exitStatus attribute
        history[i] -> exitStatus = 0;
        free(history[i]);	//free malloced memory
    }
}

void print_history(int firstSequenceNumber){
    int i;
    for(i=0; i < cmdCapacity; i++){
        if(currentCmd <MAXHISTORY){
            printf("%d",i+1);     //prints the cmd number from 1-10
            printf("[%d]", history[i] -> exitStatus);
            printf("%s\n", history[i] -> cmd);
        }else{
            printf("%d",i+(currentCmd-9));     //prints the cmd number from 1-10
            printf("[%d]", history[(oldestCmd+i)%MAXHISTORY] -> exitStatus); 
            printf("%s\n", history[(oldestCmd+i)%MAXHISTORY] -> cmd);
        }
    }
}
