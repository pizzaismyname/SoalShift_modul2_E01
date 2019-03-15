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
penjelasan
```
source code
```
### Langkah
penjelasan
```
source code
```

## Soal 3
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
### Mendapatkan waktu saat ini
```c
```
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
- 
```c

```
- 
```c

```

### Daemon
- Daemon dijalankan pada directory log-log yang dicopy dari /var/log/syslog
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
