// Problem "Producenta i konsumenta” zaimplementowany za pomoca potokow nienazwanych. Producent	
// pobiera "surowiec” z pliku tekstowego i wstawia go jako towar do potoku, a Konsument umieszcza 
// pobrany z potoku towar w innym pliku tekstowym.
//-----------------------------------------------------------------------------------------------
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

#define iloscBitow 5 	// Zdefiniowana ilosc pobieranych bitow

void producent(int * filedes) // Funkcja wykonujaca zadnie producenta
{
  if( close(filedes[0]) == -1)
    {
      perror("Error close");
      exit(1);
    }

  int plik1, dane;

  if( ( plik1 = open("./towar.txt", O_RDONLY, 0777) ) == -1)  // Otwarcie pliku z towarem i utworzenie deskryptora przy pomocy funkcji open
    {
      perror("\Error open\n");		// Obsługa błedu
      exit(2);
    }

  int time;
 
  do{  	// Petla pobierajaca porcje danych z pliku

    char *bufor = (char*) calloc(iloscBitow+1, sizeof(char*));

    time = rand() % 10;

    if( ( dane = read(plik1, bufor , iloscBitow) ) == -1)
      {
	perror("Error read\n");
	exit(3);
      }

    if (dane == 0) {     // Sprawdzenie czy plik sie nie skonczył

      bufor[dane] = '\00'; 
      
      if( write(filedes[1], bufor, 1) == -1 )
	{
	  perror("Error write");
	  exit(4);
	}

      exit(5);

    }

    if( write(filedes[1], bufor, dane) ==-1 )
      {
	perror("Error write");
	exit(6);
      }


    // Wypisanie danych na ekran 
    if( write(1,"\nProducent odczytał: ", sizeof("\nProducent odczytał: ")) ==-1)
      {
	perror("Error write");
	exit(7);
      }
    if( write(1, bufor, iloscBitow) ==-1)
      {
	perror("Error write");
	exit(8);
      }

    free(bufor);

    sleep(time);  // Symulowanie roznych szybkosci działania programu
  
  } while(dane > 0);

  if( close(plik1) ==-1)
    {
      perror("Error close");
      exit(9);
    } 

 if( wait(0) == -1)
{
   perror("Error wait");
   exit(10);
}

  if( close(filedes[1]) ==-1)
    {
      perror("Error close");
      exit(11);
    }
  

} // Koniec funkcji producent


void konsument(int * filedes) // Funkcja wykonujaca zadnie konsumenta
{ 
  if( close(filedes[1])==-1)
    {
      perror("Error close");
      exit(12);
    }


  int plik2, dane;

  if( ( plik2 = open("./kopia.txt" , O_WRONLY | O_CREAT | O_TRUNC , 0777) ) == -1)  // Otworzenie pliku do czytania, jesli plik nie istnieje to zostaje stworzony, jezeli istnieje zmniejsza sie jego długosc do zera
    {
      perror("Error open");		// Obsługa błedu
      exit(13);
    }
  int time;
  int koniecpliku = 0;
 
  do{	// Petla zapisujaca porcje danych z pliku

    char *bufor = (char *) calloc(iloscBitow+1,sizeof(char));

    time = rand() % 10;

    if( ( dane = read(filedes[0],bufor,iloscBitow) ) == -1) 
      {
	perror("Error read\n");
      }

    if (bufor[dane-1] == '\00')
      {
	dane -= 1;
	koniecpliku = 1;
      }
    if(write(plik2 , bufor , dane ) ==-1)
      {
	perror("Error write");
	exit(14);
      }
    

    // Wypisanie danych na ekran 
    if( write( 1, "\nKonsument odczytał: " , sizeof("\nKonsument odczytał: "))==-1)
      {
	perror("Error write");
	exit(15);
      }

    if( write(1, bufor, iloscBitow) ==-1)
      {
	perror("Error write");
	exit(16);
      }


    free(bufor);

    sleep(time); // Symulowanie roznych szybkosci działania programu

  } while(koniecpliku == 0);

  if(close(plik2) == -1)
    {
      perror("Error close");
      exit(17);
    }
  if( close(filedes[0]) == -1 )
    {
      perror("Error close");
      exit(18);
    } 
 

} // Koniecfunkcji konsument


int main() 
{

  time_t t;
  srand((unsigned) time(&t));
  int filedes[2];
 
  if( pipe(filedes) == -1 ) 
    {  
      perror("Blad funkcji pipe\n");  // Obsluga bledów dla potoku
      exit(19);
    }


  switch (fork() )
    {
    case -1:
      perror("fork error");
      exit(20);
    case 0:
      producent(filedes);
      break;
    default:  
      konsument(filedes);
      break;
    } //SWITCH

  return 0;
}
