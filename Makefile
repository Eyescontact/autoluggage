TARGET = autoluggage

INCLUDE_DIRS = -I ~/github/autoluggage/include
INCLUDE = ~/github/autoluggage/include/
SRC = ~/github/autoluggage/src/

CCC = gcc
CXX = arm-linux-gcc

CXXFLAGS += $(INCLUDE_DIRS) 
LFLAGS += -lpthread -lm
DEPEND += led.o get_location_msg.o blue_serial.o get_weight.o autoFollow.o 
#blue_buzzer.o
DEPAND += blue_serial.o

all:$(TARGET)

$(TARGET):$(DEPEND) main.c
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(DEPEND) main.c $(LFLAGS)
led.o:$(SRC)led.c $(INCLUDE)led.h
	$(CXX) $(CXXFLAGS) -c $(SRC)led.c

get_location_msg.o:$(SRC)get_location_msg.c $(INCLUDE)get_location_msg.h
	$(CXX) $(CXXFLAGS) -c $(SRC)get_location_msg.c

autoFollow.o:$(SRC)autoFollow.c $(INCLUDE)autoFollow.h
	$(CXX) $(CXXFLAGS) -c $(SRC)autoFollow.c

blue_serial.o:$(SRC)blue_serial.c $(INCLUDE)blue_serial.h
	$(CXX) $(CXXFLAGS) -c $(SRC)blue_serial.c

#blue_buzzer.o:$(SRC)blue_buzzer.c $(INCLUDE)blue_buzzer.h
#	$(CXX) $(CXXFLAGS) -c $(SRC)blue_buzzer.c

get_weight.o:$(SRC)get_weight.c $(INCLUDE)get_weight.h
	$(CXX) $(CXXFLAGS) -c $(SRC)get_weight.c

serial.o: $(SRC)blue_serial.c $(SRC)blue_serial.h
	$(CCC) $(CXXFLAGS) -o serial $(SRC)blue_serial.c

serial:$(SRC)Serial.c $(INCLUDE)Serial.h
	$(CCC) $(CXXFLAGS) -o serial $(SRC)Serial.c 


clean:
	rm -f *.a *.o $(TARGET) serial
