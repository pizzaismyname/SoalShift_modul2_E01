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
#include <dirent.h>

int main() {
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

    if ((chdir("/home/pristiz/modul2/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1) {
        pid_t child_id;
        int status;

        child_id = fork();

        struct stat st = {0};

        if (child_id == 0) {
            if(stat("/home/pristiz/modul2/gambar", &st) == -1){
                char *argv[4] = {"mkdir", "-p", "/home/pristiz/modul2/gambar", NULL};
                execv("/bin/mkdir", argv);
            }
            else return 0;
        }
        else {
            while ((wait(&status)) > 0);
            struct dirent *de;
            
            char mydir[100] = "/home/pristiz/modul2/";
            DIR *dr = opendir(mydir);

            while ((de = readdir(dr)) != NULL){

                char *str = de->d_name;
                char *res = strstr(str,".png");
                int pos = res - str;
                int substrLen = strlen(str) - pos;
                
                if(substrLen == 4) {
                    int len = strlen(str)-4;
                    char filename[len];
                    
                    memcpy(filename,&str[0],len);
                    filename[len] = '\0';
                    
                    char *grey = strcat(filename,"_grey.png");
                    
                    char tmpold[100]="/home/pristiz/modul2/";
                    char tmpnew[100]="/home/pristiz/modul2/gambar/";
                    
                    char *oldname = strcat(tmpold,str);
                    char *newname = strcat(tmpnew,grey);
                    
                    int stat;
                    stat = rename(oldname, newname);
                }
            }
            closedir(dr);
            
            sleep(1);
        }
    }
    exit(EXIT_SUCCESS);
}
