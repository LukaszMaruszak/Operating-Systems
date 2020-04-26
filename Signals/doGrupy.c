#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>

#define PATH "./grupa.x"
#define PROGRAM "grupa.x"

int main(int argc , char *argv[])
{

  int i,d;
  int sygnal;
  sygnal = atoi (argv[2]); 
  char *opcja = argv[1];     
  pid_t pid;
 
  if(argc!=3){
    printf("Niepoprawna ilość argumentów");
    exit(1); 
  } 

  switch (pid=fork() )
    {
    case -1:
      perror ("Nie udalo sie utworzyc procesu potomnego.");
      exit (2);
      break;

    case 0:
      setpgid(pid,0);

      execl(PATH,PROGRAM,argv[1],argv[2],NULL);
      perror("execl error");
      _exit(3);			
      break;

    default:

      d=getpgid(pid);

      printf("identyfikator grupy procesow: %d \n",d);

      if(kill(-d,0)==-1){
	perror("grupa nie istnieje");
	exit(4);  
      }

      kill(-d,sygnal); // obsluga bledu
	
      wait(NULL);
      break;
    }// switch
  

  return 0;
}






