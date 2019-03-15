#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
    while(1) {
        pid_t child_id;
        int status;

        child_id = fork();

        time_t now;
        
        time(&now);

        struct tm *local = localtime(&now);
        
        char dirname[100];
        strftime(dirname,100,"%d:%m:%Y-%H:%M/", local);    

        struct stat st = {0};
        
        char tmplog[100] = "/home/pristiz/log/";
        char *tlogdir = strcat(tmplog,dirname);
        
        if (child_id == 0) {
            
            if(stat(tlogdir, &st) == -1){
                char *argv[4] = {"mkdir", "-p", tlogdir, NULL};
                execv("/bin/mkdir", argv);
            }
            else return 0;
        }
        
        else {
            while ((wait(&status)) > 0);
            
            int i;
            
            for(i=1; i<=30; i++) {
                printf("i: %d\n",i);
                char log[100] = "/home/pristiz/log/";
                char *logdir = strcat(log,dirname);

                char num[10];
                sprintf(num,"log%d",i);
                char *lognum = strcat(logdir,num);

                char *logfile = strcat(lognum,".log");
                
                char *argv[4] = {"cp", "/var/log/syslog", logfile, NULL};
                execv("/bin/cp", argv);
                
                sleep(1);
            }
            
        }
    }
    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/pristiz/log/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    
    exit(EXIT_SUCCESS);
}
