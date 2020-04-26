// Biblioteka,prostych w uzyciu funkcji do: tworzenia, otwierania,uzyskiwania wartosci, 
// operowania, zamykania i usuwania semafora.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Łukasz Maruszak			CWICZENIE 6                          Krakow, 08.05.2019
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "BIBLIOTEKA.h"

// Inicjuje Semafor Nienazwany - sem_init
int Stworz_SemaforNieNazwany(sem_t *sem, int pshared, unsigned int value)
{
	pshared=0; // Semafor jest wspoldzielony przez watki w ramach procesu

	if ( ( sem_init(sem, pshared, value) ) == -1 )
{
perror("Blad funkcji sem_init przy inicjowaniu semafora nienazwanego\n");
exit(1);
}

}

// Tworzy Semafor Nazwany - sem_open
sem_t* Stworz_SemaforNazwany(const char *name, unsigned int value)
{
sem_t *SEMAFOR;
 	if( (SEMAFOR = sem_open(name, O_CREAT , 0777, value) ) == SEM_FAILED)
	{
		perror("Blad funkcji sem_open podczas tworzenia lub otwierania semafora nazwanego\n");
		exit(2);
	}
return SEMAFOR;
}

// Wykonanie operacji podnoszenia semaforow - sem_post
int Podnies_Semafor(sem_t *sem)
{
if( ( sem_post(sem) ) == -1)
{
perror("Blad funkcji sem_post podczas podnoszenia semafora\n");
exit(3);
}

}

// Wykonanie operacji opuszczania semaforow - sem_wait
int Opusc_Semafor(sem_t *sem)
{

if( (sem_wait(sem) ) == -1)
{
perror("Blad funkcji sem_wait podczas opuszczania semafora\n");
exit(4);
}	

}

// Zamykanie semafora Nazwanego - sem_close
int Zamknij_Nazwany(sem_t *sem)
{

if( (sem_close(sem) ) == -1)
{
perror("Blad funkcji sem_close podczas zamykania semafora nazwanego\n");
exit(5);
}

}

// Usuniecie Semafora Nienazwanego - sem_destroy
int Usun_NieNazwany(sem_t *sem)
{

if( (sem_destroy(sem) ) == -1) 
{
perror("Blad funkcji sem_destroy podczas usuwania semafora nienazwanego\n");
exit(6);
}

}
  
// Usuniecie Semafora Nazwanego - sem_unlink
int Usun_Nazwany(sem_t *sem)	
{

if( (sem_unlink(sem) ) == -1) 
{
perror("Blad funkcji sem_unlink podczas usuwania semafora nazwanego\n");
exit(7);
}

}

// Uzyskanie informacji o wartosci semafora - sem_getvalue
int Wartosc_Semafora(sem_t *sem, int *sval)  
{

if( (sem_getvalue(sem, &sval) ) == -1 )
{
perror("Blad funkcji sem_getvalue podczas uzyskiwania informacji o wartosci semafora\n");
exit(8);
}

}








































