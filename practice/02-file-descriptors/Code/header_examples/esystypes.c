#include <sys/types.h>
#include <unistd.h>
#include <stdio.h> 
int main() { 
    pid_t pid = getpid();
    printf("Process ID: %d\n", pid);
    return 0;
}
