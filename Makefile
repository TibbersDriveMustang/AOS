#for server.cpp & communication.cpp
LFLAGS = -I -t
CXX = g++
CXXFLAGS = -O0 -g -Wall
OBJS = server.o client.o CSokt.o 
	
server : server.o 
	$(CXX) $(CXXFLAGS) server.o -o server -pthread

communication : communication.o
	$(CXX) $(CXXFLAGS) communication.o -o communication -pthread
	
	
server.o : server.cpp
	$(CXX) $(CXXFLAGS) -c server.cpp
	
communication.o : communication.cpp
	$(CXX) $(CXXFLAGS) -c communication.cpp

clean:
	-rm -f *.o
	-rm -f server
	-rm -f client
