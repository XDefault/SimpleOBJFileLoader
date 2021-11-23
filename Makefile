
CC=gcc
CFLAGS=-g -Wall

LIBFLAGS= -fPIC -shared

SDLINCLU = "-IC:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\include"
SDLLIB=-"LC:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\lib"
SDLFlAGS =-lmingw32 -lSDL2main -lSDL2
NOSDLOUTPUT =-mwindows
OPENGLFLAGS = -lopengl32 -lglu32

FILESPATH="E:\Learning Languages\C\4 - LoadOBJModelToSLD"

OBJ=obj
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/*.c, $(OBJ)/%.o, $(SRCS))

LIB=libraries
LIBS=$(wildcard $(LIB)/*.c)
LIBSBIN=$(patsubst $(LIB)/%.c,$(LIB)/%.o,$(wildcard $(LIB)/*.c))
LIBSFILENAMES=$(notdir $(LIBSBIN))

INCLU=include
BUILD=build

TEST=tests
TESTS=$(wildcard $(TEST)/*.c)
TESTBINS=$(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))


all: exec

#---Build Code------------------------------------------------------------
exec: buildFinalLib FinalFile FinalExec

buildFinalLib:
	$(CC) $(CFLAGS) $(LIB)\libMeshFunctions.c -o $(FILESPATH)\$(BUILD)\libMeshFunctions.lib $(LIBFLAGS)
	$(CC) $(CFLAGS) $(LIBS) -o $(FILESPATH)\$(BUILD)\libObjLoader.lib -L$(FILESPATH)\$(TEST)\bin -I$(FILESPATH)\$(TEST) $(LIBFLAGS)

FinalFile: buildFinalLib
	$(CC) $(CFLAGS) $(LIBS) $(SRCS) -o $(BUILD)\main.exe -L$(FILESPATH)\$(TEST)\bin -I$(FILESPATH)\$(TEST) $(SDLINCLU) $(SDLLIB) $(SDLFlAGS) $(OPENGLFLAGS)

FinalExec: FinalFile
	$(BUILD)"\main.exe"
#-------------------------------------------------------------------------

#---Build Libs------------------------------------------------------------

buildTestLib: $(LIBS) $(OBJ)\$(LIB)
	$(CC) $(CFLAGS) $(LIB)\libMeshFunctions.c -o $(FILESPATH)\$(TEST)\bin\libMeshFunctions.a $(LIBFLAGS)
	$(CC) $(CFLAGS) $(LIBS) -o $(FILESPATH)\$(TEST)\bin\libObjLoader.a -L$(FILESPATH)\$(TEST)\bin -I$(FILESPATH)\$(TEST) $(LIBFLAGS)

testlib: buildTestLib
	$(CC) $(CFLAGS) $(LIBS) $(TESTS) -o $(TEST)\bin\libtesting.o -L$(FILESPATH)\$(TEST)\bin -I$(FILESPATH)\$(TEST)
	$(TEST)\bin\libtesting.o

#-------------------------------------------------------------------------

#---Build SRCS Tests------------------------------------------------------
test: buildLib testbuild testexec

buildLib:
	$(CC) $(CFLAGS) $(LIB)\libMeshFunctions.c -o $(FILESPATH)\$(OBJ)\$(LIB)\libMeshFunctions.a $(LIBFLAGS)
	$(CC) $(CFLAGS) $(LIBS) -o $(FILESPATH)\$(OBJ)\$(LIB)\libObjLoader.a -L$(FILESPATH)\$(OBJ)\$(LIB) -I$(FILESPATH)\$(OBJ) $(LIBFLAGS)

testbuild: buildLib
	$(CC) $(CFLAGS) $(LIBS) $(SRCS) -o $(FILESPATH)\$(OBJ)\testSRCs.o -L$(FILESPATH)\$(OBJ)\$(LIB) -I$(FILESPATH)\$(OBJ) $(SDLINCLU) $(SDLLIB) $(SDLFlAGS) $(OPENGLFLAGS)

testexec: $(OBJ) testbuild
	$(FILESPATH)\$(OBJ)\testSRCs.o

#-------------------------------------------------------------------------

clean:
	del *.o
	del $(OBJ)\*.o
	del $(TEST)\bin\*.o
	del $(TEST)\bin\*.a
	del $(OBJ)\$(LIB)\*.o
	del $(OBJ)\$(LIB)\*.so
	del $(OBJ)\$(LIB)\*.a
	del $(BUILD)\*.exe
	del $(BUILD)\*.lib

init:
	mkdir $(SRC)
	mkdir $(TEST)
	mkdir $(TEST)\bin
	mkdir $(OBJ)
	mkdir $(INCLU)
	mkdir $(BUILD)

$(TEST):
	mkdir $@

$(TEST)\bin: $(TEST)
	mkdir $@

$(LIB):
	mkdir $@

$(OBJ)\$(LIB):
	mkdir $@