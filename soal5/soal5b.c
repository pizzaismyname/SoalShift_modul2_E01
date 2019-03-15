#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>

int main() {
    char line[100];
    FILE *command = popen("pidof soal5","r");

    fgets(line,100,command);

    pid_t pid = strtoul(line,NULL,10);
    pclose(command);
    
    kill(pid,SIGKILL);

    return 0;
}
