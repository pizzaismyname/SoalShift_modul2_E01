#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <syslog.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

using namespace std;
char cwd[PATH_MAX];

bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
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
    cout << "Penghapus Kenangan Elen v0.1\nMengawasi file " << cwd << endl;

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
        if (is_file_exist(cwd))
        {
            struct stat info;
            stat(cwd, &info); // Error check omitted
            struct passwd *pw = getpwuid(info.st_uid);
            struct group *gr = getgrgid(info.st_gid);

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