#==========================================================================
#				Plik Makefile
.SUFFIXES: .c .cpp .o .x .h
DIR = `basename $(CURDIR)`

NAME1 = powielacz
NAME2 = glowny
NAME3 = BIBLIOTEKA

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O -pthread

# Dla programu tworzymy biblioteke statyczna oraz dzielona
LIB_NAME = MojeFunkcje
# Katalog dla bibliotek
LIB_DIR = ./lib
# Biblioteka statyczna (static library)
LIB_STAT = lib$(LIB_NAME).a
# Biblioteka dzielona (shared library)
LIB_SHAR = lib$(LIB_NAME).so
# Pliki objectowe wchodzace do biblioteki
LIB_OBJS = $(OBJS3)
# Pliki naglowkowe
HEADS3 = $(NAME3).h

# Tworzenie bibliteki statycznej dla programu przy pomocy 
# programu archiwizujacego.
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

# Regula zaleznosci dla pliku wykonawczego programu z biblioteka statyczna
$(EXEC2s): $(OBJS2) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(OBJS3): $(HEADS3)

CO = gcc
LD = $(CO)
AR = ar
ARFLAGS = rv

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC2s)

$(EXEC1): $(OBJS1) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^ 
$(EXEC2): $(OBJS2) $(LIBS1) 
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run1

run1: $(EXEC1) $(EXEC2)  $(EXEC2s) 
	./$(EXEC2) $(EXEC1) $(EXEC2s) ${PROC} ${KRYT}


.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )


