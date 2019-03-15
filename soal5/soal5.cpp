#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

int main() {
    int hours, minutes, day, month, year;

    time_t now;
    
    time(&now);

    struct tm *local = localtime(&now);

    hours = local->tm_hour;
    minutes = local->tm_min;
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;

//    printf("%02d:%02d:%d-%02d:%02d\n", day, month, year, hours, minutes);
/*
    while(1) {
        int i=1;
        for(i=1; i<=30; i++){
            char tmplog[100]="/home/pristiz/logs/";
            char *logdir= strcat(tmplog,);
            char *logfile = strcat(logdir,i);
            
            char *argv[] = {"cp", "/var/log/syslog", NULL};
            execv("/bin/cp", argv);            
        }
        sleep(60);
    }
===============================================================================
    pid_t child_id;
    int status;

    child_id = fork();

    struct stat st = {0};

    if (child_id == 0) {
        if(stat("/home/pristiz/log", &st) == -1){
            char *argv[4] = {"mkdir", "-p", "/home/pristiz/log", NULL};
            execv("/bin/mkdir", argv);
        }
        else return 0;
    }
    else {
        while ((wait(&status)) > 0);
        
    }
*/
    
    return 0;
}
