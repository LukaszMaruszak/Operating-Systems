#==========================================================
#		Plik Makefile
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`
NAME1 = progA
NAME2 = progB
NAME3 = obsluga
NAME4 = grupa
NAME5 = doGrupy
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x
OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o
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
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^ 
$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC3): $(OBJS3) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC4): $(OBJS4) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^
$(EXEC5): $(OBJS5) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^


.PHONY: runA runB runC 
runA: $(EXEC1)  
	./$(EXEC1) ${O} ${S} 
runB: $(EXEC2) 
	./$(EXEC2) ${O} ${S}   
runC: $(EXEC3) $(EXEC4) $(EXEC5) 
	./$(EXEC3) ${O} ${S} $(EXEC4) $(EXEC5) 







.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


