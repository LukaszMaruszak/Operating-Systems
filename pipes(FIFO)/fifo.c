// Problem "Producenta i konsumenta” z cwiczenia 4 zaimplementowany za pomoca potokow nazwanych. 
//-----------------------------------------------------------------------------------------------
//Łukasz Maruszak 				ĆWICZENIE 5a		       Kraków, 14.04.2019
//-----------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
 
#define PATH1 "./producent.x"
#define PROGRAM1 "producent.x" 

#define PATH2 "./konsument.x"
#define PROGRAM2 "konsument.x"

int main()
{
  if( ( mkfifo("potok", 0644) ) == -1)	// Utworzenie potoku FIFO 
    {
      perror("blad fifo");
      exit(1);
    }

  switch( fork() )
    {
    case -1: // Blad w tworzeniu procesu
      perror("Tworzenie procesu");
      exit(1);

    case 0:
      execl(PATH1,PROGRAM1,NULL); // Otwarcie programu producenta 
				
      exit(2);
    default: 
      execl(PATH2,PROGRAM2,NULL); // Otwarcie programu konsumenta

      exit(3);
    }

  return 0;
}
