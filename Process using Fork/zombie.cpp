#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid > 0) {
        // Parent process
        std::cout << "Parent process with PID: " << getpid() << std::endl;
        // Sleep to allow the child to finish before the parent exits
        sleep(10);
    } else if (child_pid == 0) {
        // Child process
        std::cout << "Child process with PID: " << getpid() << std::endl;
        // Child exits immediately without waiting for any operation
        exit(0);
    } else {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    // The parent process waits for any child process termination
    // This is to ensure the parent waits for the child to become a zombie
    int status;
    pid_t wait_result = wait(&status);

    if (wait_result > 0) {
        if (WIFEXITED(status)) {
            std::cout << "Child with PID " << wait_result << " exited with status: " << WEXITSTATUS(status) << std::endl;
        }
    }

    return 0;
}
