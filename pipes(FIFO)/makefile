#==========================================================================
#				Plik Makefile
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = producent
NAME2 = konsument
NAME3 = fifo

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

LIBS1  = 
HEADS1 = 
CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O
LDLIBS = -lm
CO = gcc
LD = $(CO)
AR = ar
ARFLAGS = rv
%.o: %.c
	$(CO) $(CFLAGS) -c $<
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) 
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^ 
$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^


.PHONY: runA runB
  
runA: $(EXEC1) $(EXEC2) $(EXEC3) 
	./$(EXEC3) 
	diff -s ./towar.txt ./kopia.txt

runB:  $(EXEC1) $(EXEC2)
	mkfifo -m 0644 potok
	xterm -hold -title okno_konsumenta -e ./konsument.x &
	xterm -hold -title onko_producenta -e ./producent.x 
	diff -s ./towar.txt ./kopia.txt
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


