//this file contains the prototypes for the history functions
//init history, add history, clear history, and print history
//
//Define layout of a single entry in the history array
struct Cmd {
    char* cmd; //A saved copy of the users command string
    int exitStatus; //The status from this command
};

#define MAXHISTORY 10

void init_history(void); //Builds the data structures for recording cmd history
void add_history(char *cmd, int exitStatus); //Adds an entry to the history
void clear_history(void); //Frees all malloc'd memeory in the history
void print_history(int firstSequenceNumber); //Prints the history to stdout
