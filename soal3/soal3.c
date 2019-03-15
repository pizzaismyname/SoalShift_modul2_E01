#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <dirent.h>

int is_file_exists(const char *filename)
{
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

const char *get_filename_ext(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "job2") == 0)
        {
            //2. Reading File list jadinkan char**, terus exec ke diri sendiri..
            printf("Doing job2\n");
            DIR *d;
            struct dirent *dir;
            d = opendir("./campur2");
            if (d)
            {
                char *filelist = "";
                while ((dir = readdir(d)) != NULL)
                {
                    char *filename = dir->d_name;
                    if (strcmp(get_filename_ext(filename), "txt") == 0)
                    {
                        filelist = concat(filelist, concat(filename, "\n"));
                    }
                }
                closedir(d);
                char *argvexec[4] = {argv[0], "job3", filelist, NULL};
                execv(argv[0], argvexec);
            }
            else
            {
                printf("Cannot open directory!\n");
                return 2;
            }
        }
        else if (strcmp(argv[1], "job3") == 0)
        {
            //3. Write file list ke daftar.txt
            printf("Doing job3\n");
            FILE *fPtr = fopen("./daftar.txt", "w");
            if (fPtr == NULL)
            {
                printf("Cannot open daftar.txt");
                return 5;
            }
            fputs(argv[2], fPtr);
            fclose(fPtr);
            return 0;
        }
        else
        {
            //Normal Routine
            //1. Do fork untuk unzip
            if (is_file_exists(argv[0]))
            {
                pid_t child_id;
                child_id = fork();
                if (child_id > 0)
                {
                    //Parent akan wait sampai forknya exit
                    int returnStatus;
                    waitpid(child_id, &returnStatus, 0);
                    if (returnStatus == 0)
                    {
                        //Exec dan teruskan ke job2
                        char *argvexec[3] = {argv[0], "job2", NULL};
                        execv(argv[0], argvexec);
                    }
                    else
                    {
                        printf("Unzip gagal!\n");
                    }
                }
                else if (child_id < 0)
                {
                    printf("Cannot perform fork()\n");
                }
                else
                {
                    //Fork akan exec unzip filenya
                    char *argvexec[5] = {"-o", argv[1], NULL};
                    execv("/usr/bin/unzip", argvexec);
                    //Next this program will return 0 if unzip is success..
                }
            }
            else
            {
                printf("File not found!\n");
            }
        }
    }
    else
    {
        printf("Invalid command!. Please input zip file!\n");
    }
}