#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <syslog.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

char cwd[PATH_MAX];

int is_file_exists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    pid_t pid, sid;

    if (argc >= 2)
        strcpy(cwd, argv[1]);
    else
        strcpy(cwd, "/");
    if (chdir(cwd) < 0)
        exit(EXIT_FAILURE);
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/hatiku/elen.ku");
    printf("Penghapus Kenangan Elen v0.1\n");
    printf("Mengawasu file %s \n", cwd);

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

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1)
    {
        if (is_file_exists(cwd))
        {
            struct stat info;
            stat(cwd, &info); // Error check omitted
            struct passwd *pw = getpwuid(info.st_uid);
            struct group *gr = getgrgid(info.st_gid);
			
			//Chmod 777
			chmod(cwd, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
			
            if (pw != 0)
            {
                if (strcmp(pw->pw_name, "www-data") == 0)
                {
                    if (gr != 0)
                    {
                        if (strcmp(gr->gr_name, "www-data") == 0)
                        {
                            remove(cwd);
                        }
                    }
                }
            }
        }
        sleep(3);
    }

    exit(EXIT_SUCCESS);
}