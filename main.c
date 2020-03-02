

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

char* prompt_line(void){
    char* command;
    size_t lenLine = 0;
    printf("Hash>>");
    getline(&command,&lenLine,stdin);
    return command;
}

char **addargs(char **totalArgs, char *remainingCommand,int index) {
    char* curArg = strtok(NULL," ");
    if (curArg!=NULL){
        totalArgs[index] = curArg;
        addargs(totalArgs,remainingCommand,index+1);
    }
    printf("totalarg[%d] is %s\n",index,totalArgs[index]);
    return totalArgs;
}

void cmdExec(char* command, char** args){
    pid_t  childPID;
    childPID = fork();
    int cStatus;

    if(childPID ==0){
        execvp(command,args);
        exit(0);
    } else{
        /* This is run by the parent.  Wait for the child
           to terminate. */

        do {
            pid_t tpid = wait(&cStatus);
            if(tpid != childPID) process_terminated(tpid);
        } while(tpid != childPID);

        return child_status;
    }
}

void hashLoop(){
    int status =1;
    while (status){
        char* tcommand = strtok(prompt_line(),"\n");
        printf("first print -> %s\n",tcommand);
        if (strcmp(tcommand,"quit") ==0){ //Works much like toString in java
            exit(0);
        } else {
            char* mcommand = strtok(tcommand," "); //Begins delimiting string
            printf("%s\n", mcommand);
            char **args = (char**)malloc(sizeof(char**));
            args = addargs(args,mcommand,0);
            cmdExec(mcommand,args);
        }
        free(tcommand); //Free memory when not immediately needed
    }
}

int main(int argc,char *argv[]) {
    hashLoop();
    return 0;
}
