#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


void showProcessMessage();
void showProcessCreationMessage(pid_t IDOfTheCreatedProcess);
void showProcessTerminationMessage();
pid_t createProcess();

void startCodeForSecondProcess();
void startCodeForThirdProcess();
void startCodeForFourthProcess();

int main(){
    
    int status;

    showProcessMessage();

    pid_t idOfSecondProcess = createProcess(), idOfThirdProcess;

    if(idOfSecondProcess > 0){
        wait(&status);
        idOfThirdProcess = createProcess();
        if(idOfThirdProcess > 0){
            wait(&status);
        }else if(idOfThirdProcess == 0){
            startCodeForThirdProcess();
        }else{
            exit(EXIT_FAILURE);
        }
    }
    else if(idOfSecondProcess == 0){
        startCodeForSecondProcess();
    }else{
        exit(EXIT_FAILURE);
    }

    showProcessTerminationMessage();

    return(0);
}

void showProcessMessage(){
    printf("ID родительского процесса - %d, ID процесса - %d\n",getppid(),getpid());
}

void showProcessCreationMessage(pid_t IDOfTheCreatedProcess){
    printf("процесс с ID-%d породил процесс с ID-%d\n",getpid(),IDOfTheCreatedProcess);
}

void showProcessTerminationMessage(){
    printf("процесс с ID-%d и ID-%d родителя завершает работу\n",getpid(),getppid());
}

pid_t createProcess(){
    pid_t id = fork();
    if(id > 0){
        showProcessCreationMessage(id);
    }
    return id;
}

void startCodeForSecondProcess(){
    int status;
    pid_t idOfFourthProcess = createProcess();
    if(idOfFourthProcess > 0){
        wait(&status);
        createProcess();
    }else if(idOfFourthProcess == 0){
        startCodeForFourthProcess();
    }else{
        exit(EXIT_FAILURE);
    }
}

void startCodeForThirdProcess(){
    int status;
    pid_t id = createProcess();
    if(id > 0){
        wait(&status);
    }else if(id < 0){
        exit(EXIT_FAILURE);
    }
}

void startCodeForFourthProcess(){
    int status;
    pid_t id = createProcess();
    if(id > 0){
        wait(&status);
        char *args[2] = {"/bin/ls", "-m", NULL};
        execv(args[0], args);
    }else if(id < 0){
        exit(EXIT_FAILURE);
    }
}