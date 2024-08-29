在 Linux/Unix 系统中，当一个子进程结束时，父进程通常需要回收它的资源。这种回收操作被称为“等待”子进程的结束。主要有两种方式来等待子进程结束并回收其资源：阻塞方式 wait() 和 非阻塞方式 waitpid()。
```C
1. 阻塞方式：wait()
原型：pid_t wait(int *status);

作用：wait() 函数用于阻塞父进程，直到任意一个子进程结束。结束后，父进程可以获取该子进程的退出状态。

使用示例：


#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // 子进程
        printf("Child process\n");
        sleep(2); // 模拟子进程的工作
        return 0;
    } else if (pid > 0) {
        // 父进程
        int status;
        wait(&status);  // 阻塞父进程，等待子进程结束
        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    } else {
        // fork 失败
        perror("fork");
    }

    return 0;
}
解释：

wait()：在父进程中调用 wait()，父进程会阻塞，直到有一个子进程结束。status 参数用于保存子进程的退出状态。
WIFEXITED(status)：检查子进程是否正常退出。
WEXITSTATUS(status)：获取子进程的退出状态码。
2. 非阻塞方式：waitpid()
原型：pid_t waitpid(pid_t pid, int *status, int options);

作用：waitpid() 函数允许父进程以非阻塞的方式等待特定的子进程结束。通过 options 参数，还可以设置不同的等待方式。

使用示例：


#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() 
{
    pid_t pid = fork();

    if (pid == 0) 
    {
        // 子进程
        printf("Child process\n");
        sleep(2); // 模拟子进程的工作
        return 0;
    } 
    else if (pid > 0) 
    {
        // 父进程
        int status;
        pid_t result;

        // 非阻塞方式，轮询检查子进程是否结束
        do 
        {
            result = waitpid(pid, &status, WNOHANG);
            if (result == 0) 
            {
                printf("Child process still running\n");
                sleep(1);  // 模拟父进程的其他工作
            }
        } while (result == 0);

        if (result > 0 && WIFEXITED(status)) 
        {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    } 
    else 
    {
        // fork 失败
        perror("fork");
    }

    return 0;
}
解释：

waitpid()：可以用于等待特定的子进程。pid 参数指定要等待的子进程的 PID。如果 pid 为 -1，则等待任意子进程。options 参数可以设置为 WNOHANG，使 waitpid() 以非阻塞方式工作。
WNOHANG：如果没有子进程结束，waitpid() 将立即返回 0，不会阻塞父进程。可以用来让父进程执行其他任务，同时定期检查子进程的状态。
总结
wait()：适用于父进程只需要等待任意一个子进程结束，并且不介意阻塞的场景。
waitpid()：提供了更多的灵活性，允许父进程等待特定的子进程，并且可以选择是否阻塞。如果你需要在等待子进程的同时继续执行其他任务，waitpid() 更加合适。



