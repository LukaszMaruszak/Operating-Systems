// Program wykonujacy zadanie producenta. -------------------------------------------------------------------------------------------------
//Łukasz Maruszak 				ĆWICZENIE 4		       Kraków, 14.04.2019
//-----------------------------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define iloscBitow 5

int main()
{

  int desk;

  desk = open("./potok", O_WRONLY ,0777);
  if (desk == -1){
    perror("Otwarcie potoku do zapisu");
    exit(1);
  }
 
  int plik1, dane;

  if( ( plik1 = open("./towar.txt", O_RDONLY, 0777) ) == -1)   // Otwarcie pliku z towarem i utworzenie deskryptora przy pomocy funkcji open
    {  
      perror("\Error open\n");  // Obsługa błedu
      exit(2);
    }
  int time;
 
  do {   // Petla pobierajaca porcje danych z pliku

    char *bufor = (char*) calloc(iloscBitow, sizeof(char*));
    time = rand() % 10;

    if( ( dane = read(plik1, bufor , iloscBitow) ) == -1)
      {
	perror("Blad read!\n");
	exit(3);
      }

    if (dane == 0) { // Sprawdzenie czy plik sie nie skonczył

      bufor[dane] = '\00';
      write(desk, bufor, 1);
      exit(4);

    }
    if(write(desk, bufor, dane) ==-1 )
      {
	perror("Error write");
	exit(5);
      }
    

    // Wypisanie danych na ekran 
    if( write(1,"\nProducent odczytał: ", sizeof("\nProducent odczytał: ")) ==-1)
      {
	perror("Error write");
	exit(6);
      }
    if( write(1, bufor, iloscBitow) ==-1)
      {
	perror("Error write");
	exit(7);
      }

    free(bufor);
    sleep(time); // Symulowanie roznych szybkosci działania programu
  
  } while(dane > 0);

  if( close(plik1) ==-1)
    {
      perror("Error close");
      exit(8);
    } 

  if( wait(0) == -1)
    {
      perror("Error wait");
      exit(9);
    }

  if( close(desk) ==-1)
    {
      perror("Error close");
      exit(10);
    } 
  

  return 0;
} // koniec producent
