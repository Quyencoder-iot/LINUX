#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void child_process(int id) {
    printf("Child process %d with PID %d\n", id, getpid());
    for (int i = 0; i < 100000000; i++) { // Vòng lặp để tiêu tốn thời gian CPU
        if (i % 10000000 == 0) {
            printf("Child process %d is working (i = %d)\n", id, i);
        }
    }
    printf("Child process %d completed\n", id);
}

int main() {
    pid_t pid1, pid2;

    // Tạo tiến trình con thứ nhất
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid1 == 0) {
        // Tiến trình con thứ nhất
        child_process(1);
        exit(0);
    }

    // Tạo tiến trình con thứ hai
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid2 == 0) {
        // Tiến trình con thứ hai
        child_process(2);
        exit(0);
    }

    // Chờ các tiến trình con kết thúc
    wait(NULL);
    wait(NULL);

    printf("Main process completed\n");
    return 0;
}