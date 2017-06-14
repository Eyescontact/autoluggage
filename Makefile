TARGET = autoluggage

INCLUDE_DIRS = -I ~/github/autoluggage/include
INCLUDE = ~/github/autoluggage/include/
SRC = ~/github/autoluggage/src/

CCC = gcc
CXX = arm-linux-gcc
CXXFLAGS += $(INCLUDE_DIRS) 
LFLAGS += -lpthread  
DEPEND += led.o get_location_msg.o 

all:$(TARGET)

$(TARGET):$(DEPEND) main.c
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(DEPEND) main.c $(LFLAGS)
led.o:$(SRC)led.c $(INCLUDE)led.h
	$(CXX) $(CXXFLAGS) -c $(SRC)led.c  

get_location_msg.o:$(SRC)get_location_msg.c $(INCLUDE)get_location_msg.h
	$(CXX) $(CXXFLAGS) -c $(SRC)get_location_msg.c

serial:$(SRC)Serial.c $(INCLUDE)Serial.h
	$(CCC) $(CXXFLAGS) -o serial $(SRC)Serial.c 

clean:
	rm -f *.a *.o $(TARGET) serial
