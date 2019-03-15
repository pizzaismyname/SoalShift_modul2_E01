# SoalShift_modul2_E01

## Soal 1
### Child process
Membuat folder /home/pristiz/modul2/gambar/ jika belum dibuat
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
```
char mydir[100] = "/home/pristiz/modul2/";
DIR *dr = opendir(mydir);
```
- Loop untuk mengecek seluruh file dan directory yang ada pada directory di atas
```
while ((de = readdir(dr)) != NULL) {
...
}
```
- 

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
