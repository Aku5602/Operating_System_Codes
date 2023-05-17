//Assignment No. 1

/*In child:
  cp=>copy
  grep=>
  ls=>

  fork()
  execl()
  getpid()
  getppid()
  exit()

In Parent:
  wait() */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  
  int cid=fork();

  if(cid==0) {

    printf("\nI am child with process id: %d, and my parents process id is: %d\n",getpid(),getppid());
    int choice;
    printf("\nEnter Choice: 0=>cp, 1=>grep, 2=>ls\n");
    scanf("%d", &choice);
    
    switch(choice) {

      case 0: execl("usr/bin/cp","cp","/home/pccoe/Desktop/TYCOB115/file1.txt","/home/pccoe/Desktop/TYCOB115/file2.txt",NULL);
              break;

      case 1: execl("usr/bin/grep","grep","try","/home/pccoe/Desktop/TYCOB115/file1.txt",NULL);
              break;

      case 2: execl("usr/bin/ls","ls",NULL);
              break;

    }
    
    exit();
     
  }
  else {

    printf("\nI am parent with process id: %d, and my childs process id is: %d\n",getpid(),pid);
    wait(pid);
    
  }


  printf("Hello World");
  return 0;
}//end of main
