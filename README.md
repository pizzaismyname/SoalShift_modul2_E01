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
- Menunggu child process selesai
```c
while ((wait(&status)) > 0);

```
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
- Menginisialisasi counter nama file
```c
int counter = 1;
while (1) {
    //...
}
```
- Mendapatkan waktu terakhir file makan_enak.txt diakses
```c
struct stat info;
stat("/home/rifqi/Documents/makanan/makan_enak.txt", &info);
time_t file_atime = info.st_atime;
```
- Mendapatkan waktu saat ini
```c
time_t current = time(NULL);
```
- Mengecek jika waktu saat ini sudah lewat 30 menit dari waktu terakhir file diakses 
```c
if (current - file_atime <= 30)
{
    //...
}
```
- Membuat file makan_sehat# (# sesuai counter) dan menambah counter
```c
char filename[FILENAME_MAX];
sprintf(filename, "makan_sehat%d.txt", counter);
FILE *file = fopen(filename, "w");
fclose(file);
counter++;
```

### Daemon
- Daemon dijalankan pada directory dimana file makan_sehat#.txt dibuat
```c
if ((chdir("/home/rifqi/Documents/makanan")) < 0) {
        exit(EXIT_FAILURE);
}
```
- Menjalankannya secara otomatis (setiap 5 detik)
```c
sleep(5);
```

## Soal 5a
### Child process
Membuat directory dengan nama format nama waktu saat ini jika belum dibuat
```c
pid_t child_id;
child_id = fork();

time_t now;
time(&now);
struct tm *local = localtime(&now);
char dirname[100];
strftime(dirname,100,"%d:%m:%Y-%H:%M/", local);

char tmplog[100] = "/home/pristiz/log/";
char *tlogdir = strcat(tmplog,dirname);

struct stat st = {0};

if (child_id == 0) {
    if(stat(tlogdir, &st) == -1){
        char *argv[4] = {"mkdir", "-p", tlogdir, NULL};
        execv("/bin/mkdir", argv);
    }
    else return 0;
}

```
### Parent process
- Menunggu child process selesai
```c
while ((wait(&status)) > 0);

```
- Meng-copy isi file /var/log/syslog ke file baru sesuai kriteria pada soal
```c
for(i=1; i<=30; i++) {
    char log[100] = "/home/pristiz/log/";
    char *logdir = strcat(log,dirname);

    char num[10];
    sprintf(num,"log%d",i);
    char *lognum = strcat(logdir,num);
    char *logfile = strcat(lognum,".log");

    char ch;
    FILE *source, *target;
    source = fopen("/var/log/syslog", "r");
    target = fopen(logfile, "w+");

    while ((ch = fgetc(source)) != EOF) fputc(ch, target);

    fclose(source);
    fclose(target);
}
```

### Daemon
- Daemon dijalankan pada directory dimana file log#.log dibuat
```c
if ((chdir("/home/pristiz/log/")) < 0) {
        exit(EXIT_FAILURE);
}
```
- Menjalankan peng-copy-an file setiap 1 menit (diletakkan pada loop bagian dalam sehingga setiap setengah jam membuat directory baru)
```c
for(i=1; i<=30; i++) {
    // ...
    sleep(60);
}
```

## Soal 5b
- Mencari pid yang sesuai dengan nama proses hasil compile soal5a.c
```c
char line[100];
FILE *command = popen("pidof soal5","r");

fgets(line,100,command);

pid_t pid = strtoul(line,NULL,10);
pclose(command);
```
- Membunuh proses dengan pid tersebut
```c
kill(pid,SIGKILL);
```
