/*
opendir() and readdir()
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
  int exists; 
  DIR *dirp;
  struct dirent *dr;
  struct stat buff;

  dirp=opendir(".");
  if(dirp==NULL) {
    printf("Error opening File");
    exit(1);

  }
  else {
    while((dr=readdir(dirp))!=NULL) {
      exists=stat(dr->d_name,&buff);
      if(exists<0) { printf("File is empty"); }
      else { printf("%s   %ld\n",dr->d_name,buff.st_size); }
      

    }
  
  }
  return 0;
}