SRC = is.c
FLAGS = -g -Wall
TARGET = is

$(TARGET):
	cc $(FLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
