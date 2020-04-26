#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#include <unistd.h>

#define PATH "./obsluga.x"
#define PROGRAM "oblsuga.x"
#define liczba_wywolan 3

int main(int argc, char *argv[])
{
  int w;
  int status;
  int sygnal;
  sygnal = atoi (argv[2]);
  int i;
  pid_t pid;
  char *opcja = argv[1];
  
 

  for(i=0;i<liczba_wywolan;i++)
    {
      switch ( pid=fork() )
	{
	case -1:
	  perror ("Nie udalo sie utworzyc procesu potomnego.");
	  exit (1);
	  break;

	case 0:
 	
	  execl(PATH,PROGRAM,argv[1],argv[2],NULL);
	  perror("execl error");
	  _exit(2);			
	  break;


	}// switch

    } //for
 
  sleep(1);
 
  for(i=0;i<liczba_wywolan;i++) //petla na oczekiwanie "wait"
    {
      w=wait(&status);
      if(w==-1)
	{
	  perror("Bład wait");
	}
      else
	printf("w=%d, status: %d", w, &status);

    }
    
  return 0;
}



