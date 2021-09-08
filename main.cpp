#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
using std::cout;
using std::endl;

void getInfoAboutProcess();

int main(){
    getInfoAboutProcess();
    
    pid_t c_pid = fork();

    if(c_pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(c_pid > 0){
        getInfoAboutProcess();
        wait(nullptr);
    }else {
        getInfoAboutProcess();
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}

void getInfoAboutProcess(){
    cout << "process id - " << getpid() << "; parent process id - " << getppid() << endl;
}