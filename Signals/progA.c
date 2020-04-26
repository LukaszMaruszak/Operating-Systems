//Program do obsługi sygnałów z możliwościami: (d) wykonanie operacji domyślnej, (i) ignorowanie 
// oraz (p) przechwycenie i własna obsługa sygnału
//-----------------------------------------------------------------------------------------------
//Łukasz Maruszak 				ĆWICZENIE 3		       Kraków, 02.04.2019
//-----------------------------------------------------------------------------------------------

#include<stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void my_sighandler (int sygnal) 		// Funkcja do obsługi własnej sygnału
{
  printf("Zdefiniowana obsługa sygnalu,ktory dotarl: %d \n", sygnal);
}

int main (int argc, char *argv[])
{
  printf("PID procesu: %d\n", getpid());	// Wypisanie PID'u procesu
  char *opcja = argv[1];			// Przekazanie wybranej opcji <d,i,p>
  int sygnal = atoi (argv[2]);			// Przekazanie i zamiana na liczbe wybranego sygnału

  if(argc!=3)
    {
      printf("Niepoprawna ilość argumentów, podaj: ./progA.o < wybrana opcja (d,i,p) > < numer sygnału > /n");  //Sprawdzenie czy została podana prawidłowa ilosc danych
      exit(1); 
    }

  if ( strcmp (opcja , "d" ) == 0 )		//Funkcja sprawdza czy została wybrana opcja d (wykonanie operacji domyslnej)
    {
      if ( signal( sygnal, SIG_DFL) == SIG_ERR)
	{
	  perror("Funkcja signal ma problem z SIGDFL");
	  exit(EXIT_FAILURE);
	}
    }
  else if ( strcmp (opcja , "i" ) == 0 )	//Funkcja sprawdza czy została wybrana opcja i (ignorowanie sygnału)
    {
      if ( signal( sygnal, SIG_IGN) == SIG_ERR)
	{
	  perror("Funkcja signal ma problem z SIGIGN");
	  exit(EXIT_FAILURE);
	}
    }
  else if ( strcmp( opcja , "p") == 0)		//Funkcja sprawdza czy została wybrana opcja p (przechwycenie i własna obsługa sygnału)
    {
      if (signal ( sygnal, my_sighandler) == SIG_ERR)
	{
	  perror("Funkcja signal ma problem z SIGINT");
	  exit(EXIT_FAILURE);
	}
    }

  if(pause() != -1)	// Funkcja pause czeka na sygnal
    {
      perror("Blad pause");	// Obsluga bledow
      exit(2);
    }

  return 0;
}
