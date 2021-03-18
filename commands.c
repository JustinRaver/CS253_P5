//this file defines the function executeCommand(char *str)
//this function takes in a char array and tokenizes it into args so that they can 
//be put into an args array

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "smash.h"
#include "history.h"
#define MAXARRAYSIZE 2800

int exitStatus;

int executeExternalCommand(char **args){
  
  fflush(stdout);
  int pid = fork();

  if(pid==0){// if this is the child process executing 
    if(execvp(args[0],args) == -1){
      clear_history();
      perror("command is not supported");
      fclose(stdout);
    }
    exit(1);
  }else if (pid>0){// this is the parent process executing
    fflush(stdout);
    int retrievedStat;
    wait(&retrievedStat);
    int exitStatus = WEXITSTATUS(retrievedStat);
    if(exitStatus == 2){
      return -1;
    }else{
      return exitStatus;  
    } 
  }else{
  
    perror("Fork failed");

  }
   return  -1;
}

void executeCommand(char *str){
    char argsCpy[MAXARRAYSIZE];		//array for copy of user cmds
    strncpy(argsCpy,str,MAXARRAYSIZE);	//creates copy of the user cmds
    const char s[2] = " ";		//creates delimeter for strtok
    char *token;			//creates char pointer for tokens
    token = strtok(str, s);		//call to strtok
    char *args[MAXARRAYSIZE];		//array for the user arg tokens
    int argTracker = 0;			//int to track the number of tokens
    int exitStatus;			//int to track the number of tokens
    char directory[256];    		//array for the user directory
    while(token != NULL){//while token not null continue tokenize str
          args[argTracker] = token;
	  token = strtok(NULL,s); 
          argTracker++;
    }
    args[argTracker] = NULL;
    if(argTracker == 0){//if no arguments are entered simply exit normally and place $ symbol
        exitStatus = 0;
        return;
    }
    if(strncmp(args[0],"exit",20) == 0){//if arg is 'exit'
        clear_history();//clear the history
        exitStatus = 0; //exit normally
        exit(exitStatus);
    }else if(strncmp(args[0],"cd",20) == 0){//if arg is 'cd'
        if(args[1]!=NULL){// if arg 1 is not null
            if(chdir(args[1])==0){// if chdir is successful
                exitStatus = 0;
                getcwd(directory,sizeof(directory)); 
                puts(directory);   
            }else{//if directory is invalid
                exitStatus = -1;//exit abnormally
                fprintf(stderr,"%s",args[1]);
                fprintf(stderr,": No such file or directory\n");
            }
        }else{//if arg 1 is null
            exitStatus = -1;//exit abnormally
            fprintf(stderr,": No such file or directory\n");
        }
        add_history(argsCpy,exitStatus);//add cmd to history
    }else if(strncmp(args[0],"history",20) == 0){//if arg is "history"
        exitStatus = 0;//exit normally 
        add_history(argsCpy,exitStatus);//add history cmd to history
        print_history(0);//print the history       
    }
    else{//if arg is external
        
        exitStatus = executeExternalCommand(args);
        //exit abnormally to show functionality has not yet been added
        add_history(argsCpy,exitStatus);//add cmd
    }       
}
