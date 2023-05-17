#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
  //Pipes,fork and redirection
  int pid;
  int fd[2];
  int file_desc = open("file1.txt");
  dup2(file_desc,0);
  pipe(fd);
  pid = fork();
  if(pid == 0) {
    //Inside child => write and sort
    dup2(fd[1],1);
    close(fd[0]);
    close(fd[1]);
    
    execl("/usr/bin/sort","sort",NULL);
  }
  else if(pid > 0){
    //Inside parent process
    dup2(fd[0],0);
    close(fd[0]);
    close(fd[1]);
    execl("/usr/bin/uniq","uniq",NULL);
    wait(NULL);
  }
  else {
    cout<<endl<<"Something went wrong"<<endl;
  }
  return 0;
}

