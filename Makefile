CC=     g++
LD=     ld
CFLAGS= -g -W -Wall
LDFLAGS=-lGL -lglut
TARGET= gofl
SRC=    main.cpp view.cpp gofl.cpp
OBJ=    $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o

distclean: clean
	rm -rf $(TARGET) 

