TARGET = autoluggage

INCLUDE_DIRS = -I ~/autoluggage/include
INCLUDE = ~/autoluggage/include/
SRC = ~/autoluggage/src/

CXX = gcc
CCC = arm-linux-gcc
CXXFLAGS += $(INCLUDE_DIRS) 
LFLAGS += -lpthread  
DEPEND += led.o get_location_msg.o blue_serial.o get_weight.o 

all:$(TARGET)

$(TARGET):$(DEPEND) main.c
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(DEPEND) main.c $(LFLAGS)
led.o:$(SRC)led.c $(INCLUDE)led.h
	$(CXX) $(CXXFLAGS) -c $(SRC)led.c

get_location_msg.o:$(SRC)get_location_msg.c $(INCLUDE)get_location_msg.h
	$(CXX) $(CXXFLAGS) -c $(SRC)get_location_msg.c

blue_serial.o:$(SRC)blue_serial.c $(INCLUDE)blue_serial.h
	$(CXX) $(CXXFLAGS) -c $(SRC)blue_serial.c

get_weight.o:$(SRC)get_weight.c $(INCLUDE)get_weight.h
	$(CXX) $(CXXFLAGS) -c $(SRC)get_weight.c

serial:$(SRC)blue_serial.c $(INCLUDE)blue_serial.h
	$(CCC) $(CXXFLAGS) -o serial $(SRC)blue_serial.c

clean:
	rm -f *.a *.o $(TARGET) serial
