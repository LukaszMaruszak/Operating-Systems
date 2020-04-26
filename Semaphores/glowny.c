// Program przy pomocy semaforów nazwanych standardu POSIX implementuje zadanie wzajemnego 
// wykluczania dla procesow.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Łukasz Maruszak			CWICZENIE 6                          Krakow, 08.05.2019
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "BIBLIOTEKA.h"

#define MAXTIME 7
int main(int argc, char *argv[])
{

  int i; 			// Do petli for
  int WartoscSemfora; 	// Przechowwuje wartosc semafora, uzywane w funkcji Wartosc_Semafora
  int TIME; 		// Losowy czas dzialania funkcji sleep
  pid_t PID = getpid();
  char LiczbaSekcjiKrytycznych;
  sem_t *sem;			
  char *NazwaSemafora;

  LiczbaSekcjiKrytycznych = atoi(argv[1]);
  NazwaSemafora = argv[2];

  srand(time(NULL));
  TIME=rand()% MAXTIME;

  printf("Rozpoczecie sekcji krytycznej\n");

  printf("Stworzenie Semafora Nazwanego\n");

  sem = Stworz_SemaforNazwany(NazwaSemafora, 0);	// Stworzenie semafora nazwanego

  for(i=1 ; i <= LiczbaSekcjiKrytycznych ; i++)
    {
      // Przed Sekcja Krytyczna
      Wartosc_Semafora(&sem, &WartoscSemfora);
      printf("PID procesu =%d przed %d sekcja krytyczna, wartosc semafora: %d\n", PID, i, WartoscSemfora);

      Opusc_Semafor(sem);
      // W Trakcie Sekcji Krytycznej
      Wartosc_Semafora(&sem, &WartoscSemfora);
      printf("PID procesu =%d w trakcie %d sekcji krytycznej, wartosc semafora: %d\n", PID, i, WartoscSemfora);

      Podnies_Semafor(sem);
      // Po Sekcji Krytycznej
      Wartosc_Semafora(&sem, &WartoscSemfora);
      printf("PID procesu =%d po %d sekcji krytycznej, wartosc semafora: %d\n", PID, i, WartoscSemfora);
   
    }

  printf("Koniec Sekcji krytycznej\n");

  Zamknij_Nazwany(sem); // Usuwa semafor nazwany

  printf("Zamkniecie Semafora Nazwanego\n");


  return 0;
}






































