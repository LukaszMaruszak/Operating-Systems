#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void my_sighandler (int sygnal)
{
  printf("Zdefiniowana obsługa sygnalu,ktory dotarl: %d \n", sygnal);
}

int main (int argc, char *argv[])
{
  int sygnal;
  printf("PID procesu: %d\n", getpid());
  char *opcja = argv[1];
  sygnal = atoi (argv[2]);

  if (argc == 2) 
    {
      printf("Blad! \n");
    }


  if ( strcmp (opcja , "d" ) == 0 )
    {
      if ( signal( sygnal, SIG_DFL) == SIG_ERR)
	{
	  perror("Funkcja signal ma problem z SIGDFL");
	  exit(EXIT_FAILURE);
	}
    }
  else if ( strcmp (opcja , "i" ) == 0 )
    {
      if ( signal( sygnal, SIG_IGN) == SIG_ERR)
	{
	  perror("Funkcja signal ma problem z SIGIGN");
	  exit(EXIT_FAILURE);
	}
    }
  else if ( strcmp( opcja , "p") == 0)
    {
      if (signal ( sygnal, my_sighandler) == SIG_ERR)
	{
	  perror("Funkcja signal ma problem z SIGINT");
	  exit(EXIT_FAILURE);
	}
    }
  pause();

  return 0;
}
