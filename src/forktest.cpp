#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::cout << "Forktest" << std::endl;
    
    int * somevar = new int();
    *somevar = rand();
    
    std::cout << "randvar=" << *somevar << std::endl;

    pid_t pid = fork();
    if (pid == -1) {
        std::cout << "fork failed" << std::endl;
    } else if (pid > 0) {
        std::cout << "[parent] my PID " << getpid() << std::endl;
        std::cout << "[parent] child PID " << pid << std::endl;
        waitpid(pid, 0, 0);
        std::cout << "[parent] randvar location " << somevar << " and value " << *somevar << std::endl;
    } else {
        std::cout << "[child] my PID " << getpid() << std::endl;
        std::cout << "[child] my parent PID " << getppid() << std::endl;
        *somevar = rand();
        std::cout << "[child] randvar location " << somevar << " and value " << *somevar << std::endl;
    }
    return 0;
}
