CXX	= g++
CXXFLAGS	= -std=c++11 -lpthread
SERVER_OBJS	= client_main.o util.o ui.o userInfo.o nodelist.o transmission.o heartbeat.o timestamp.o parser.o gpg.o message.o
CLIENT_OBJS = server_main.o list_check.o ui.o util.o nodelist.o parser.o timestamp.o gpg.o transmission.o userInfo.o message.o hb_server.o
SERVER_PROG	= server
CLIENT_PROG = client

$(SERVER_PROG): $(SERVER_OBJS)
	g++ -o $(SERVER_PROG) $(SERVER_OBJS) -lpthread

$(CLIENT_PROG): $(CLIENT_OBJS)
	g++ -o $(CLIENT_PROG) $(CLIENT_OBJS)
  
cleanall: clean
	$(RM) $(SERVER_PROG) $(CLIENT_PROG)

clean:
	$(RM) *.o
