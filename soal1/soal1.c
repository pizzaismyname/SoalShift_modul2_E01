#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main() {
    struct dirent *de;
    
    char mydir[100] = "/home/pristiz/modul2/gambar/";
    DIR *dr = opendir(mydir);

    if (dr == NULL) {
        printf("Could not open directory.");
        return 0;
    }

    while ((de = readdir(dr)) != NULL){

        char *str = de->d_name;
        char *res = strstr(str,".png");
        int pos = res - str;
        int substrLen = strlen(str) - pos;
        
        if(substrLen == 4) {
            //printf("%s\n", str);
            int len = strlen(str)-4;
            char filename[len];
            
            memcpy(filename,&str[0],len);
            filename[len] = '\0';
            
            char *tmpfile = filename;
            
            char *grey = strcat(tmpfile,"_grey.png");
            
            char tmpold[100]="/home/pristiz/modul2/gambar/";
            char tmpnew[100]="/home/pristiz/modul2/gambar/";
                        
            char *oldname = strcat(tmpold,str);
            char *newname = strcat(tmpnew,grey);
            
//             printf("oldname: %s\n",oldname);
//             printf("newname: %s\n",newname);
            
            int stat;
            stat = rename(oldname, newname);
            
//             if(stat == 0) printf("File renamed successfully.\n");
//             else printf("Error: unable to rename the file.\n");

        }
    }
    
    closedir(dr);
    
    return 0;
}
