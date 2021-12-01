
CC=gcc
CFLAGS=-g -Wall

LIBFLAGS= -fPIC -shared

SDLINCLU = "-IC:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\include"
SDLLIB=-"LC:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\lib"
SDLFlAGS =-lSDL2main -lSDL2
NOSDLOUTPUT =-mwindows
OPENGLFLAGS =-lGLU -lGL

FILESPATH="/home/x/Code/C/Git/SimpleOBJFileLoader"

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
	$(CC) $(CFLAGS) $(LIB)/libMeshFunctions.c -o $(BUILD)/libMeshFunctions.lib $(LIBFLAGS)
	$(CC) $(CFLAGS) $(LIBS) -o $(BUILD)/libObjLoader.lib -L$(BUILD) -I$(BUILD) $(LIBFLAGS)

FinalFile: buildFinalLib
	$(CC) $(CFLAGS) $(LIBS) $(SRCS) -o $(BUILD)/main -L$(BUILD) -I$(BUILD) $(SDLFlAGS) $(OPENGLFLAGS)

FinalExec: FinalFile
	$(BUILD)/main
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
#	rm *.o
#	rm $(OBJ)/*.o
#	rm $(TEST)/bin/*.o
#	rm $(TEST)/bin/*.a
#	rm $(OBJ)/$(LIB)/*.o
#	rm $(OBJ)/$(LIB)/*.so
#	rm $(OBJ)/$(LIB)/*.a
	rm $(BUILD)/*.exe
	rm $(BUILD)/*.lib

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