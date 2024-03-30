# Makefile for applying filters

CC = g++
CFLAGS = -lpthread
TARGET = a.out

.PHONY: all clean

all: apply_blur apply_edge apply_sharp papply_blur papply_edge papply_sharp

apply:
	$(CC) $(CFLAGS) apply_filter.cpp -o $(TARGET)
	./$(TARGET) oimage.txt mask.txt output.txt

papply:
	$(CC) $(CFLAGS) papply_filter.cpp -o $(TARGET)
	./$(TARGET) oimage.txt mask.txt output.txt 4
