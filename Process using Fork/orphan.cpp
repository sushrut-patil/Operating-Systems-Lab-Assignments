#include <iostream>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid > 0) {
        // Parent process
        std::cout << "\nParent process with PID: " << getpid() << std::endl;
        sleep(2); // Sleep to allow the parent to terminate first
        std::cout << "\nParent process terminating" << std::endl;
    } else if (child_pid == 0) {
        // Child process
        sleep(4); // Sleep to ensure the parent process terminates first
        std::cout << "\nChild process with PID: " << getpid() << std::endl;
        std::cout << "\nChild's parent PID: " << getppid() << std::endl; // Print the parent PID before it exits
    } else {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    return 0;
}
