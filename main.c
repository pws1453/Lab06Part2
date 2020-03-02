

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
            execl("/bin/sh","sh","-c",mcommand);
        }
        free(tcommand); //Free memory when not immediately needed
    }
}

int main(int argc,char *argv[]) {
    hashLoop();
    return 0;
}
