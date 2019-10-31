CC = gcc
OPTIONS = -g -o
OBJECTS = main.o calc_area.o calc_length.o
SOURCES = main.c calc_area.c calc_length.c
HEADERS = 
TARGET = test

$(TARGET):$(OBJECTS)
	$(CC) $(OPTIONS) $(TARGET) $(OBJECTS)
$(OBJECTS):$(SOURCES)
	$(CC) -c $(SOURCES)
all:
	make $(TARGET)
clean:
	rm -rf *.o
	rm -rf $(TARGET)
all.tar:$(SOURCES) makefile
	tar -cvf $(SOURCES) makefile > all.tar
