#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstring>
#include <fcntl.h>

using namespace std;

void processSystemCalls() {
    pid_t childPid = fork();
    
    if (childPid == -1) {
        cerr << "Fork failed." << endl;
        return;
    } else if (childPid == 0) {
        // Child process
        cout << "Child process with PID: " << getpid() << endl;
        cout << "Parent process's PID (PPID): " << getppid() << endl;
        exit(0);
    } else {
        // Parent process
        cout << "Parent process with PID: " << getpid() << endl;
        wait(NULL);
        cout << "Child process has finished." << endl;
    }
}

void fileSystemCalls() {
    int fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        cerr << "Error opening file." << endl;
        return;
    }
    
    const char *text = "Hello, File System Calls!\n";
    write(fd, text, strlen(text));
    
    lseek(fd, 0, SEEK_SET);
    char buffer[100];
    read(fd, buffer, sizeof(buffer));
    cout << "Read from file: " << buffer;
    
    close(fd);


     if (link("example.txt", "hardlink.txt") == -1) {
        cerr << "Error creating hard link." << endl;
        return;
    }

    unlink("hardlink.txt");
    unlink("example.txt");
}

void communicationSystemCalls() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        cerr << "Pipe creation failed." << endl;
        return;
    }

    pid_t childPid = fork();

    if (childPid == -1) {
        cerr << "Fork failed." << endl;
        return;
    } else if (childPid == 0) {
        // Child process
        close(pipefd[1]); 
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        cout << "Child received (pipe): " << buffer << endl;
        close(pipefd[0]);
        exit(0);
    } else {
        // Parent process
        close(pipefd[0]);
        const char *text = "Hello from parent!";
        write(pipefd[1], text, strlen(text) + 1);
        close(pipefd[1]);
        wait(NULL);
    }

    const char *fifoName = "myfifo";
    mkfifo(fifoName, 0666);

    int fifo_fd = open(fifoName, O_RDWR);

    childPid = fork();

    if (childPid == -1) {
        cerr << "Fork failed." << endl;
        return;
    } else if (childPid == 0) {
        // Child process
        close(fifo_fd);
        char buffer[100];
        read(fifo_fd, buffer, sizeof(buffer));
        cout << "Child received (fifo): " << buffer << endl;
        close(fifo_fd);
        exit(0);
    } else {
        // Parent process
        close(fifo_fd);
        const char *text = "Hello from parent!";
        write(fifo_fd, text, strlen(text) + 1);
        close(fifo_fd);
        wait(NULL);
    }

    unlink(fifoName);
}



void informationSystemCalls() {
    struct stat fileStat;
    if (stat("example.txt", &fileStat) == 0) {
        cout << "File size: " << fileStat.st_size << " bytes" << endl;
        cout << "Owner's User ID: " << fileStat.st_uid << endl;
    } else {
        cerr << "Error getting file information." << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "Menu:\n";
        cout << "1. Process System Calls\n";
        cout << "2. File System Calls\n";
        cout << "3. Communication System Calls\n";
        cout << "4. Information System Calls\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                processSystemCalls();
                break;
            case 2:
                fileSystemCalls();
                break;
            case 3:
                communicationSystemCalls();
                break;
            case 4:
                informationSystemCalls();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 5);

    return 0;
}
