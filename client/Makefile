CXX	= g++
CXXFLAGS = -std=c++11
CLIENT_OBJS	= client.o ../source_code/transmission.o ../source_code/userInfo.o ../source_code/message.o ../source_code/parser.o ../source_code/nodelist.o ../source_code/timestamp.o ../source_code/util.o ../source_code/gpg.o ../source_code/ui.o ../source_code/msg_ui.o
CLIENT_PROG = client

$(CLIENT_PROG): $(CLIENT_OBJS)
	g++ -o $(CLIENT_PROG) $(CLIENT_OBJS) -lpthread
  
cleanall: clean
	$(RM) $(CLIENT_PROG)

clean:
	$(RM) *.o ../source_code/*.o
