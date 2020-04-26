// Plik nagłowkowy 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Łukasz Maruszak			CWICZENIE 6                          Krakow, 08.05.2019
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _BIBLIOTEKA_H
#define _BIBLIOTEKA_H
#include <semaphore.h>

int Stworz_SemaforNieNazwany();  // Inicjuje Semafor Nienazwany

sem_t* Stworz_SemaforNazwany();  // Tworzy Semafor Nazwany

int Podnies_Semafor();           // Wykonanie operacji podnoszenia semaforow

int Opusc_Semafor();		 // Wykonanie operacji opuszczania semaforow

int Zamknij_Nazwany();    // Zamykanie semafora Nazwanego

int Usun_NieNazwany( );   // Usuniecie Semafora Nienazwanego

int Usun_Nazwany( );	 // Usuniecie Semafora Nazwanego

int Wartosc_Semafora( );    // Uzyskanie informacji o wartosci semafora 


#endif





















































