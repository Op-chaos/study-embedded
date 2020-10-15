#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

void *thread_function(void *arg);

char message[] = "Hello World";

int main() {
    int res;
    pthread_t a_thread;    // 线程标识符
    void *thread_result;   // 空类型指针
    struct timeval timenow;
    gettimeofday(&timenow, NULL);
    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);    // 子线程进入thread_function函数内部，
    if (res != 0) {                                                             // 主线程继续向下走
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("%ld.%ld Waiting for thread to finish...\n", timenow.tv_sec, timenow.tv_usec);  // 判断线程是否创建成功
    res = pthread_join(a_thread, &thread_result);     // 会阻塞，直到子线程结束
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined, it returned %s\n", (char *)thread_result);
    printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    struct timeval timenow;
    gettimeofday(&timenow, NULL);
    printf("%ld.%ld thread_function is running. Argument was %s\n", timenow.tv_sec, timenow.tv_usec, (char *)arg);
    sleep(3);
    strcpy(message, "Bye!");
    gettimeofday(&timenow, NULL);
    printf("%ld.%ld thread_function over\n", timenow.tv_sec, timenow.tv_usec);
    pthread_exit("Thank you for the CPU time");
}
