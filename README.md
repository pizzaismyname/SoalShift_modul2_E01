# SoalShift_modul2_E01

## Soal 1
### Child process
Membuat directory /home/pristiz/modul2/gambar/ jika belum dibuat
```c
pid_t child_id;
child_id = fork();
struct stat st = {0};
if (child_id == 0) {
  if(stat("/home/pristiz/modul2/gambar", &st) == -1){
    char *argv[4] = {"mkdir", "-p", "/home/pristiz/modul2/gambar", NULL};
    execv("/bin/mkdir", argv);
  }
  else return 0;
}
```
### Parent process
- Membuka directory yang berisi gambar-gambar berekstensi .png
```c
char mydir[100] = "/home/pristiz/modul2/";
DIR *dr = opendir(mydir);
```
- Loop untuk mengecek seluruh file dan directory yang ada pada directory di atas
```c
struct dirent *de;
while ((de = readdir(dr)) != NULL) {
// ...
}
```
- Mencari nama file yang berekstensi .png
```c
char *str = de->d_name;
char *res = strstr(str,".png");
int pos = res - str;
int substrLen = strlen(str) - pos;
```
- Jika file ditemukan
```c
if(substrLen == 4) {
// ...
}
```
- Mengganti nama file lama dengan nama file baru (nama file lama ditambahkan dengan "\_grey") sekaligus memindahkannya pada directory /home/pristiz/modul2/gambar/
```c
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
```
### Daemon
- Daemon dijalankan pada directory yang berisi gambar-gambar berekstensi .png
```c
if ((chdir("/home/pristiz/modul2/")) < 0) {
        exit(EXIT_FAILURE);
}
```
- Menjalankannya secara otomatis (setiap 1 detik)
```c
sleep(1);
```

## Soal 2
### Langkah
Aplikasi ini akan memonitor lokasi file /hatiku/elen.ku.
Cara menggunakannya :
```
$ ./soal2 ~
Penghapus Kenangan Elen v0.1
Mengawasi file /home/rifqi/hatiku/elen.ku
```
Aplikasi ini akan menghapus file elen.ku jika owner dan grup sama dengan "www-data", dan melakukan `chmod(file, 777)` secara otomatis setiap 3 detik.

#### Fungsi untuk memeriksa eksistensi file:
```c
int is_file_exists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}
```
#### Cara mendapatkan owner, dan group file
Jika owner dan grup sama dengan "www-data", maka `remove` file hatiku/elen.ku
```c
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
```

## Soal 3
### Langkah
Untuk mengimplementasikan fork, pipe, dan exec, saya menggunakan saya menggunakan diagram seperti ini:
```
    |Parent| 
        |---> IF (args == ".zip")
        |              |
        |              V
        |            FORK----------------> Wait----> EXEC(self,'job2',args)
        |              |                     ^ 
        |              |                     | 
        |              |--> | exec(unzip) |--| 
        |
        |---> IF (args == "job2") 
        |         |
        |         |--> Reading File list --> exec(self,'job3',"file1.txt\nfile2.txt\n..")
        |
        |----> IF (args == "job3")
                  |
                  |--> fopen("daftar")--> fputs(argv)
```


## Soal 4
### Langkah
penjelasan
```
source code
```
### Langkah
penjelasan
```
source code
```

## Soal 5
### Langkah
penjelasan
```
source code
```
### Langkah
penjelasan
```
source code
```
