#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void showProcessMessage();
void showProcessCreationMessage(pid_t IDOfTheCreatedProcess);
void showProcessTerminationMessage();
pid_t createProcess();

void startCodeForSecondProcess();
void startCodeForThirdProcess();
void startCodeForFourthProcess();

int main(){
    
    showProcessMessage();

    pid_t idOfSecondProcess = createProcess(), idOfThirdProcess;

    if(idOfSecondProcess > 0){
        idOfThirdProcess = createProcess();
        if(idOfThirdProcess == 0){
            startCodeForThirdProcess();
        }else if(idOfThirdProcess < 0){
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
    pid_t idOfFourthProcess = createProcess();
    if(idOfFourthProcess > 0){
        createProcess();
    }else if(idOfFourthProcess == 0){
        startCodeForFourthProcess();
    }else{
        exit(EXIT_FAILURE);
    }
}

void startCodeForThirdProcess(){
    usleep(700);
    createProcess();
}

void startCodeForFourthProcess(){
    usleep(900);
    createProcess();
}