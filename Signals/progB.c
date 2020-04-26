//Program uruchamia program "progA.c" poprzez funkcję, exec w procesie potomnym innego
// procesu i wysyłać do niego sygnały poprzez funkcję, systemową, kill z procesu macierzystego.
//-----------------------------------------------------------------------------------------------
//Łukasz Maruszak 				ĆWICZENIE 3		       Kraków, 02.04.2019
//-----------------------------------------------------------------------------------------------


#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<errno.h>

#define PATH "./progA.x" 	// Zdefiniowanie sciezki do otwarcia programu 
#define PROGRAM "progA.x"	// Zdefiniowanie nazwy programu

int main(int argc, char *argv[])
{ 

  pid_t pid;
  int syg;
  syg =  atoi (argv[2]);

  if(argc!=3)
    {
      printf("Niepoprawna ilość argumentów, podaj: ./progA.o < wybrana opcja (d,i,p) > < numer sygnału > /n");  //Sprawdzenie czy została podana prawidłowa ilosc danych
      exit(1); 
    }

  
  switch (pid=fork()) // Tworzenie procsu potomnego
    {
    case -1:
      perror("fork error");
      exit(2);
      break;
    case 0:			
      execl(PATH,PROGRAM,argv[1],argv[2],NULL); 
      perror("execl error");
      _exit(3);
      break;
    default:  
      sleep(1);			
      if(kill( pid,0)==-1){	// Sprawdzenie czy proces istnieje
	if(errno == ESRCH ) 	// Obsluga bledu funkcji kill
	  {
	    perror("Proces nie istnieje");
	    exit(4);  
	  }
	else{
	  perror("Blad kill'a");
	  exit(5);
	}
      }
      if(kill(pid, syg) == -1) {	// Wysłanie sygnału poprzez funkcje, kill z procesu macierzystego wraz z obsluga bledu
	perror("Kill nie działa"); 
	exit(6);
      }
   if(wait(NULL) == -1)
	    {
	      perror("wait error");
	      exit(6);
}
    } //SWITCH
	
  return 0;
}
