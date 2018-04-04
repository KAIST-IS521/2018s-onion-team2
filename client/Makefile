CXX	= g++
CXXFLAGS = -std=c++11
CLIENT_OBJS	= client.o
CLIENT_PROG = client

$(CLIENT_PROG): $(CLIENT_OBJS)
	g++ -o $(CLIENT_PROG) $(CLIENT_OBJS)
  
cleanall: clean
	$(RM) $(CLIENT_PROG)

clean:
	$(RM) *.o
