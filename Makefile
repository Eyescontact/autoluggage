TARGET = autoluggage

CXX = arm-linux-gcc

all:$(TARGET)

$(TARGET):led.o main.c
	$(CXX) -o $(TARGET) led.o main.c
led.o:led.c led.h
	$(CXX) -c led.c  
clean:
	rm -f *.a *.o $(TARGET) 
