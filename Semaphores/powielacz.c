// Program do powielania procesów realizujacych wzajemne wykluczaniE–w oparciu o funkcje fork i exec.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Łukasz Maruszak			     CWICZENIE 6                           Krakow, 08.05.2019
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include "BIBLIOTEKA.h"

#define PATH "./"

int main(int argc, int *argv[])
{
int i; 	// Do petli for
char PathName[100]; 	// Nazwa sciezki
sem_t *sem;
char *NazwaSemafora = "/sem"; // Nazwa semafora
char LiczbaProcesow;

LiczbaProcesow=atoi(argv[2]);
sem = Stworz_SemaforNazwany(NazwaSemafora,1);  // Stworzenie semafora
sprintf(PathName,"%s%s",PATH,argv[1]);


 for(i=0; i<LiczbaProcesow; i++) // Powielenie procesow
    {
        switch (fork())
        {
            case -1:
            perror("Fork Error\n");
            exit(2);
	    break;

            case  0:  // Otwarcie programu do wzajemnego wykluczania dla procesow.
	    if (execl(PathName,argv[1],argv[3], NazwaSemafora , NULL) == -1)
	    {
	    	perror("Execl error\n");
	        exit(3);
	    }	
            break;  

   
        };
    }

Usun_Nazwany(NazwaSemafora); 	// Usuwa semafor nazwany

    return 0;
}











