// Program wykonujacy zadanie konsumenta 
//-----------------------------------------------------------------------------------------------
//Łukasz Maruszak 				ĆWICZENIE 5a		       Kraków, 14.04.2019
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

  desk = open("./potok", O_RDONLY ,0777);
  if (desk == -1){
    perror("Otwarcie potoku do zapisu");
    exit(1);
  }

  int plik2, dane;
  
  if( ( plik2 = open("./kopia.txt" , O_WRONLY | O_CREAT | O_TRUNC , 0777) ) == -1)  // Otworzenie pliku do czytania, jesli plik nie istnieje to zostaje stworzony, jezeli istnieje zmniejsza sie jego długosc do zera
    {
      perror("Blad open");  // Obsługa błedu
      exit(2);
    }
  int time;
  int koniecpliku = 0;
 
  do {    // Petla zapisujaca porcje danych z pliku

    char *bufor = (char *) calloc(iloscBitow,sizeof(char));
    time = rand() % 10;

    if( ( dane = read(desk,bufor,iloscBitow) ) == -1) 
      {
	perror("Blad read\n");
      }


    if (bufor[dane-1] == '\00') {
      dane-=1;
      koniecpliku = 1;
    }

    if(write(plik2 , bufor , dane ) ==-1)
      {
	perror("Error write");
	exit(3);
      }

    // Wypisanie danych na ekran 
    if( write( 1, "\nKonsument odczytał: " , sizeof("\nKonsument odczytał: "))==-1)
      {
	perror("Error write");
	exit(4);
      }

    if( write(1, bufor, iloscBitow) ==-1)
      {
	perror("Error write");
	exit(5);
      }

    free(bufor);

    sleep(time);  // Symulowanie roznych szybkosci działania programu

  } while(koniecpliku == 0);

  if(close(plik2) == -1)
    {
      perror("Error close");
      exit(6);
    }
  if(  close(desk) == -1 )
    {
      perror("Error close");
      exit(7);
    } 
  
  if( unlink("potok") == -1)
    {
      perror("Error unlink");
      exit(8);
    }
  return 0;
} // koniec konsument
