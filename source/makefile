#--------------------------------------------------------------------
#
# Makefile for HPcalc
#
# Using EMX
#--------------------------------------------------------------------
 
B=/emx/bin/
I=\emx\include
L=/emx/lib/
CC=gcc
#ifdef DEBUG
CFLAGS=-g -Wall
LFLAGS=-g
OBJ=o
#else
CFLAGS=-O -Wall -Zsys -Zomf
LFLAGS=-s -Zsys -Zomf -Zmap -Zlinker /map
OBJ=obj
#endif

A = HPcalc
VER = 098
OBJS = $(A).$(OBJ) interface.$(OBJ) change.$(OBJ) ini.$(OBJ) \
      hex-oct.$(OBJ)
DIST = $(A).exe $(DIST_SRC)
DIST_SRC = ReadMe file_id.diz readme-latest.txt readme-old.txt COPYING
SRC = $(DIST_SRC) interface.c change.c change.h HPclc$(VER).txt\
	$(A).h buttons.h interface.h Makefile $(A).ico $(A).rc \
	ini.c ini.h hex-oct.c hex-oct.h $(A)D.dlg interface-vars.h \
	ReadMe.Int HPcalc.def HPcalc.c


all: $(A).exe $(A)D.res

$(A).res: $(A).rc $(A).h $(A).ico $(A)D.dlg
	rc -r -i $(I) $(A).rc

$(A)D.res: $(A).res
	copy $(A).res $(A)D.res

$(A).exe:  $(OBJS) $(A)D.res
	$(CC) $(LFLAGS) $(OBJS) $(A).def $(A).res
	@if "$(DEBUG)" == "" lxlite -B- $@
	@if not "$(DEBUG)" == "" echo Built debug version

$(A).$(OBJ): $(A).c $(A).h interface.h buttons.h change.h ini.h
	$(CC) $(CFLAGS) -c $(A).c
   
interface.$(OBJ): interface.c interface.h interface-vars.h $(A).h hex-oct.h
	$(CC) $(CFLAGS) -c interface.c

change.$(OBJ): change.c change.h $(A).h interface.h
	$(CC) $(CFLAGS) -c change.c

hex-oct.$(OBJ): hex-oct.c $(A).h interface.h interface-vars.h 
	$(CC) $(CFLAGS) -c hex-oct.c

ini.$(OBJ): ini.c ini.h interface.h interface-vars.h change.h
	$(CC) $(CFLAGS) -c ini.c

clean:
	del *.$(OBJ) core rc0* *.res

zip: HPclc$(VER).zip

HPclc$(VER).zip: $(DIST) source
	zip -ujo9 $@ $(DIST) HPclc$(VER)_src.zip
	unzip -t $@

source: HPclc$(VER)_src.zip

HPclc$(VER)_src.zip: $(SRC)
	zip -ujo9 $@ $(SRC)
	unzip -t $@

