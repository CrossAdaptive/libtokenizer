CFLAGS=-O0
BIN=bin
INC=include
LIB=lib
OBJ=obj
SRC=src

all: dirs c js

dirs:
	mkdir -p $(BIN) $(OBJ) $(LIB)

c: dirs
	mkdir -p $(OBJ)/c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/Runtime.o         $(SRC)/c/Runtime.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/Term.o            $(SRC)/c/Term.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/Array.o           $(SRC)/c/Array.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/File.o            $(SRC)/c/File.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/Queue.o           $(SRC)/c/Queue.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/String.o          $(SRC)/c/String.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/StringBuffer.o    $(SRC)/c/StringBuffer.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/PushbackReader.o  $(SRC)/c/PushbackReader.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/TokenGroup.o      $(SRC)/c/TokenGroup.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/Token.o           $(SRC)/c/Token.c
	cc -c $(CFLAGS) -I$(INC) -o $(OBJ)/c/Tokenizer.o       $(SRC)/c/Tokenizer.c

js:
	mkdir -p $(LIB)/js
	cat $(SRC)/js/*.js > $(LIB)/js/libtokenizer.js

tests:
	cc $(CFLAGS) -I$(INC) -o $(BIN)/testArray          $(SRC)/c/testArray.c          $(OBJ)/c/*.o
	cc $(CFLAGS) -I$(INC) -o $(BIN)/testFile           $(SRC)/c/testFile.c           $(OBJ)/c/*.o
	cc $(CFLAGS) -I$(INC) -o $(BIN)/testQueue          $(SRC)/c/testQueue.c          $(OBJ)/c/*.o
	cc $(CFLAGS) -I$(INC) -o $(BIN)/testString         $(SRC)/c/testString.c         $(OBJ)/c/*.o
	cc $(CFLAGS) -I$(INC) -o $(BIN)/testStringBuffer   $(SRC)/c/testStringBuffer.c   $(OBJ)/c/*.o
	cc $(CFLAGS) -I$(INC) -o $(BIN)/testPushbackReader $(SRC)/c/testPushbackReader.c $(OBJ)/c/*.o
	cc $(CFLAGS) -I$(INC) -o $(BIN)/testToken          $(SRC)/c/testToken.c          $(OBJ)/c/*.o
	cc $(CFLAGS) -I$(INC) -o $(BIN)/testTokenizer      $(SRC)/c/testTokenizer.c      $(OBJ)/c/*.o

.PHONY: test
test:
	$(BIN)/testArray          > /dev/null
	$(BIN)/testFile           > /dev/null
	$(BIN)/testQueue          > /dev/null
	$(BIN)/testString         > /dev/null
	$(BIN)/testStringBuffer   > /dev/null
	$(BIN)/testPushbackReader > /dev/null
	$(BIN)/testToken          > /dev/null
	$(BIN)/testTokenizer      > /dev/null

