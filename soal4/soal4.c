#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main()
{
    pid_t pid, sid;

    pid = fork();

    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/rifqi/Documents/makanan")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int counter = 1;
    while (1)
    {
        struct stat info;
        stat("/home/rifqi/Documents/makanan/makanan_enak.txt", &info);
        time_t file_atime = info.st_atime;
        time_t current = time(NULL);
        if (current - file_atime <= 30)
        {
            char filename[FILENAME_MAX];
            sprintf(filename, "makan_sehat%d.txt", counter);
            FILE *file = fopen(filename, "w");
            fclose(file);
            counter++;
        }
        sleep(5);
    }

    exit(EXIT_SUCCESS);
}